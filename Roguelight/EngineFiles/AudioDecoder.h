//-----------------------------------------------------------------
// Game Engine Object
// C++ Header - version v2_16 jan 2015 
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

#pragma once
// not for Win7
#if _WIN32_WINNT > _WIN32_WINNT_WIN7


//-----------------------------------------------------------------
// AudioDecoder Class: decodes music files (including mp3, no mid)
//-----------------------------------------------------------------
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <stdio.h>
#include <mferror.h>
#include <Xaudio2.h>
#include <string>

class AudioDecoder final
{
public:
	AudioDecoder(const std::string& filenameRef, XAUDIO2_BUFFER& bufferRef, WAVEFORMATEXTENSIBLE* pWfx);
	virtual ~AudioDecoder();

	HRESULT Open(const std::wstring& wFilenameRef, XAUDIO2_BUFFER& bufferRef, WAVEFORMATEXTENSIBLE* pWfx);
	// Pointer to the source reader.
	// Receives the audio format

	HRESULT ConfigureAudioStream(IMFSourceReader *pReader, IMFMediaType **ppPCMAudio);

	HRESULT WriteWaveData(
		XAUDIO2_BUFFER& bufferRef,  // Output 
		IMFSourceReader *pReader,   // Source reader.
		DWORD cbMaxAudioData,       // Maximum amount of audio data (bytes).
		DWORD *pcbDataWritten       // Receives the amount of data written.
		);

	HRESULT GetDuration(IMFSourceReader *pReader, LONGLONG *phnsDuration) const;

private:
	AudioDecoder(const AudioDecoder& t);
	AudioDecoder& operator=(const AudioDecoder& t);
};

#endif