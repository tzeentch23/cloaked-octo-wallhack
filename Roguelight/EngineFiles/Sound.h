//-----------------------------------------------------------------
// Game Engine Object
// C++ Header - version v2_16 jan 2015 
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------
#pragma once

// not for Win7
#if _WIN32_WINNT > _WIN32_WINNT_WIN7


#include <Xaudio2.h>
#pragma comment(lib, "XAudio2.lib")

//-----------------------------------------------------------------
// VoiceCallback Class: used by XSound to receive notifications from playing sounds
//-----------------------------------------------------------------
class Sound;
class VoiceCallback final : public IXAudio2VoiceCallback
{
public:
	HANDLE hBufferEndEvent;
	VoiceCallback() : hBufferEndEvent(CreateEvent(NULL, FALSE, FALSE, NULL)){}
	~VoiceCallback(){ CloseHandle(hBufferEndEvent); }

	//Called when the voice has just finished playing a contiguous audio stream.
	void __stdcall OnStreamEnd();

	//Unused methods are stubs
	void __stdcall OnVoiceProcessingPassEnd() { }
	void __stdcall OnVoiceProcessingPassStart(UINT32 SamplesRequired) { }
	void __stdcall OnBufferEnd(void * pBufferContext)    { }
	void __stdcall OnBufferStart(void * pBufferContext) { }
	void __stdcall OnLoopEnd(void * pBufferContext) { }
	void __stdcall OnVoiceError(void * pBufferContext, HRESULT Error) { }

	void SetVoice(Sound *pXSound);

private:
	Sound* m_pXSound = nullptr;
};

//-----------------------------------------------------------------
// XSound Class: represents a playable sound (including mp3, no mid)
//-----------------------------------------------------------------
class Sound final
{
public:
	//! creates a playable sound.
	//! @param filenameRef is the file to be loaded
	Sound(const String &filenameRef);
	//! creates a playable sound.
	//! @param resourceID is the resource to be loaded
	Sound(int resourceID);

	virtual ~Sound();

	// C++11 make the class non-copyable
	Sound(const Sound&) = delete;
	Sound& operator=(const Sound&) = delete;

	//! Playstate enumeration
	enum class PlayState
	{
		Playing,
		Paused,
		Stopped
	};

	//! Playback control. Returns false if the Sound could not be played
	bool Play();
	//! Playback control. Returns false if the Sound could not be Stopped
	bool Stop();
	//! Playback control. Returns false if the Sound could not be Paused
	bool Pause();

	// Sound Settings
	//! A volume level of 1.0 means there is no attenuation or gain and 0 means silence. 
	bool SetVolume(double volume);
	//! Returns the volume, value is between 0 and 1 or more if gain is enabled
	double GetVolume() const;

	//! Set the repeat flag
	void SetRepeat(bool repeat);

	//! Is the repeat flag set?
	bool GetRepeat() const;

	//! Pitches are expressed as input rate / output rate ratios between 1 / 1, 024 and 1, 024 / 1, 
	//! inclusive.A ratio of 1 / 1, 024 lowers pitch by 10 octaves, while a ratio of 1, 024 / 1 raises it by 10 octaves.
	//! You can only use the IXAudio2SourceVoice::SetFrequencyRatio method to apply pitch adjustments to source voices, 
	//! and only if they were not created with the XAUDIO2_VOICE_NOPITCH flag.
	//! The default frequency ratio is 1 / 1: that is, no pitch change.
	void SetPitch(double ratio);
	//! returns the pitch
	double GetPitch() const;


	//! returns the total duration of the sound in seconds
	double GetDuration() const;

	// Internal use only
	friend void __stdcall VoiceCallback::OnStreamEnd();


private:
	PlayState GetPlayState() const;
	void SetPlayState(PlayState playState);
	void Create(const String& sFilename);
	void Extract(int resourceID, const String& typeRef, String &resultingFilenameRef);
	VoiceCallback m_VoiceCallback;
	XAUDIO2_BUFFER m_Buffer;
	WAVEFORMATEXTENSIBLE m_Wfx;
	IXAudio2SourceVoice* m_pSourceVoice;
	PlayState m_PlayState = PlayState::Stopped;
};

#endif