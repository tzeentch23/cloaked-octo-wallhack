#include "stdafx.h"
#include "../stdafx.h" // for intellisense

#include "AudioDecoder.h"

// not for Win7
#if _WIN32_WINNT > _WIN32_WINNT_WIN7

#include "Propvarutil.h"
#pragma comment(lib, "Propsys.lib")

#pragma comment(lib, "XAudio2.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

//-----------------------------------------------------------------
// AudioDecoder methods
//-----------------------------------------------------------------
AudioDecoder::AudioDecoder(const std::string& filenameRef, XAUDIO2_BUFFER& bufferRef, WAVEFORMATEXTENSIBLE* pWfx)
{
	std::wstring wFileName(filenameRef.begin(), filenameRef.end());

	HRESULT hr = Open(wFileName, bufferRef, pWfx);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "Error Loading sound", "GameEngine says NO", MB_OK);
		exit(-1);
	}
}


AudioDecoder::~AudioDecoder()
{
}

HRESULT AudioDecoder::Open(const std::wstring& wFilenameRef, XAUDIO2_BUFFER& bufferRef, WAVEFORMATEXTENSIBLE* pWfx)
{
	HRESULT hr = S_OK;

	IMFSourceReader *pReader = NULL;
	HANDLE hFile = INVALID_HANDLE_VALUE;

	// Initialize the COM library.
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	// Initialize the Media Foundation platform.
	if (SUCCEEDED(hr))
	{
		hr = MFStartup(MF_VERSION);
	}

	// Create the source reader to read the input file.
	if (SUCCEEDED(hr))
	{
		hr = MFCreateSourceReaderFromURL(wFilenameRef.c_str(), NULL, &pReader);
		if (FAILED(hr))
		{
			printf("Error opening input file: %S\n", wFilenameRef.c_str(), hr);
			return hr;
		}
	}

	DWORD cbHeader = 0;         // Size of the WAVE file header, in bytes.
	DWORD cbAudioData = 0;      // Total bytes of PCM audio data written to the file.
	DWORD cbMaxAudioData = 0;

	IMFMediaType *pAudioType = nullptr;    // Represents the PCM audio format.

	// Configure the source reader to get uncompressed PCM audio from the source file.
	hr = ConfigureAudioStream(pReader, &pAudioType);
	if (SUCCEEDED(hr))
	{
		// Get wave header WAVEFORMATEX
		HRESULT hr = S_OK;
		UINT32 cbFormat = 0;

		WAVEFORMATEX *pWav = NULL;

		// Convert the PCM audio format into a WAVEFORMATEX structure.
		hr = MFCreateWaveFormatExFromMFMediaType(pAudioType, &pWav, &cbFormat);
		if (FAILED(hr))
		{
			printf("Error converting the PCM audio format into a WAVEFORMATEX structure: %S\n", wFilenameRef.c_str(), hr);
			return hr;
		}
		pWfx->Format = *pWav;

		// Get the length of the source in nanoseconds
		LONGLONG durationInNanoSecs = 0;
		hr = GetDuration(pReader, &durationInNanoSecs);
		if (FAILED(hr))
		{
			printf("Error Getting the duration of : %S\n", wFilenameRef.c_str(), hr);
			return hr;
		}
		// The number of samples does not match the duration: can be a little larger
		// Workaround: round time to greater round number
		DWORD cbMaxAudioData = (DWORD)((durationInNanoSecs / 10000000 + 1) * pWav->nSamplesPerSec * pWav->wBitsPerSample / 8 * pWav->nChannels);

		// Size of the audio data, in bytes. Must be no larger than XAUDIO2_MAX_BUFFER_BYTES
		// Corresponds with 4 hours
		if (cbMaxAudioData > XAUDIO2_MAX_BUFFER_BYTES)
		{
			cbMaxAudioData = XAUDIO2_MAX_BUFFER_BYTES;
			OutputDebugStringA("\nWARNING: Audio data exceeds maximum. Audio will be cropped.\n\n");
		}

		// Get wave data
		DWORD cbDataWritten = 0;
		hr = WriteWaveData(bufferRef, pReader, cbMaxAudioData, &cbDataWritten);
		if (FAILED(hr))
		{
			printf("Error Converting to PCM of: %S\n", wFilenameRef.c_str(), hr);
			return hr;
		}
	}
	return S_OK;
}

//-------------------------------------------------------------------
// ConfigureAudioStream
//
// Selects an audio stream from the source file, and configures the
// stream to deliver decoded PCM audio.
//-------------------------------------------------------------------

HRESULT AudioDecoder::ConfigureAudioStream(
	IMFSourceReader *pReader,   // Pointer to the source reader.
	IMFMediaType **ppPCMAudio   // Receives the audio format.
	)
{
	HRESULT hr = S_OK;

	IMFMediaType *pUncompressedAudioType = NULL;
	IMFMediaType *pPartialType = NULL;

	// Create a partial media type that specifies uncompressed PCM audio.

	hr = MFCreateMediaType(&pPartialType);

	if (SUCCEEDED(hr))
	{
		hr = pPartialType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	}

	if (SUCCEEDED(hr))
	{
		hr = pPartialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
	}

	// Set this type on the source reader. The source reader will
	// load the necessary decoder.
	if (SUCCEEDED(hr))
	{
		hr = pReader->SetCurrentMediaType(
			(DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM,
			NULL,
			pPartialType
			);
	}

	// Get the complete uncompressed format.
	if (SUCCEEDED(hr))
	{
		hr = pReader->GetCurrentMediaType(
			(DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM,
			&pUncompressedAudioType
			);
	}

	// Ensure the stream is selected.
	if (SUCCEEDED(hr))
	{
		hr = pReader->SetStreamSelection(
			(DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM,
			TRUE
			);
	}

	// Return the PCM format to the caller.
	if (SUCCEEDED(hr))
	{
		*ppPCMAudio = pUncompressedAudioType;
		(*ppPCMAudio)->AddRef();
	}

	SafeRelease(&pUncompressedAudioType);
	SafeRelease(&pPartialType);
	return hr;
}

//-------------------------------------------------------------------
// WriteWaveData
//
// Decodes PCM audio data from the source file and writes it to
// the WAVE file.
//-------------------------------------------------------------------

HRESULT AudioDecoder::WriteWaveData(
	XAUDIO2_BUFFER& bufferRef,  // Output 
	IMFSourceReader *pReader,   // Source reader.
	DWORD cbMaxAudioData,       // Maximum amount of audio data (bytes).
	DWORD *pcbDataWritten       // Receives the amount of data written.
	)
{
	HRESULT hr = S_OK;
	DWORD cbAudioData = 0;
	DWORD cbBuffer = 0;
	BYTE *pAudioData = NULL;

	IMFSample *pSample = NULL;
	IMFMediaBuffer *pBuffer = NULL;

	//Bart: store samples
	BYTE* pXAudioData = new BYTE[cbMaxAudioData];

	// Get audio samples from the source reader.
	while (true)
	{
		DWORD dwFlags = 0;

		// Read the next sample.
		hr = pReader->ReadSample(
			(DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM,
			0,
			NULL,
			&dwFlags,
			NULL,
			&pSample
			);

		if (FAILED(hr)) { break; }

		if (dwFlags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
		{
			printf("Type change - not supported by WAVE file format.\n");
			break;
		}
		if (dwFlags & MF_SOURCE_READERF_ENDOFSTREAM)
		{
			//printf("End of input file.\n");
			break;
		}

		if (pSample == NULL)
		{
			printf("No sample\n");
			continue;
		}

		// Get a pointer to the audio data in the sample.

		hr = pSample->ConvertToContiguousBuffer(&pBuffer);

		if (FAILED(hr)) { break; }


		hr = pBuffer->Lock(&pAudioData, NULL, &cbBuffer);

		if (FAILED(hr)) { break; }


		// Make sure not to exceed the specified maximum size.
		if (cbMaxAudioData - cbAudioData < cbBuffer)
		{
			cbBuffer = cbMaxAudioData - cbAudioData;
		}

		// Append the data to the sample buffer
		// memcpy_s(&pXAudioData[cbAudioData], cbMaxAudioData - cbAudioData, pAudioData, cbBuffer);
		// memcpy is NOT faster than a for loop!!
		for (size_t i = 0; i < cbBuffer; i++)
		{
			pXAudioData[i + cbAudioData] = pAudioData[i];
		}

		// Unlock the buffer.
		hr = pBuffer->Unlock();
		pAudioData = NULL;

		if (FAILED(hr)) { break; }

		// Update running total of audio data.
		cbAudioData += cbBuffer;

		if (cbAudioData >= cbMaxAudioData)
		{
			break;
		}

		SafeRelease(&pSample);
		SafeRelease(&pBuffer);
	}

	if (SUCCEEDED(hr))
	{
		// printf("Wrote %d bytes of audio data.\n", cbAudioData);

		*pcbDataWritten = cbAudioData;
	}

	if (pAudioData)
	{
		pBuffer->Unlock();
	}

	SafeRelease(&pBuffer);
	SafeRelease(&pSample);

	// Populate an XAUDIO2_BUFFER structure.
	bufferRef.AudioBytes = cbAudioData;  //buffer containing audio data
	bufferRef.pAudioData = pXAudioData;  //size of the audio buffer in bytes
	bufferRef.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

	return hr;
}

HRESULT AudioDecoder::GetDuration(IMFSourceReader *pReader, LONGLONG *phnsDuration) const
{
	PROPVARIANT var;
	HRESULT hr = pReader->GetPresentationAttribute(MF_SOURCE_READER_MEDIASOURCE,
		MF_PD_DURATION, &var);
	if (SUCCEEDED(hr))
	{
		hr = PropVariantToInt64(var, phnsDuration);
		PropVariantClear(&var);
	}
	return hr;
}

#endif