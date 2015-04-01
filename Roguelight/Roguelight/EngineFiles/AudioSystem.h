//-----------------------------------------------------------------
// Game Engine Object
// C++ Header - version v2_16 jan 2015 
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

#pragma once

// not for Win7
#ifndef WINDOWS7


#include <Xaudio2.h>
#pragma comment(lib, "XAudio2.lib")

class AudioSystem final
{

public:
	AudioSystem();
	virtual ~AudioSystem(void);
	HRESULT Initialize();
	IXAudio2* GetIXAudio(){ return m_pXAudio2; }
private:
	IXAudio2* m_pXAudio2;

	IXAudio2MasteringVoice* m_pMasterVoice;
	void Cleanup();

	AudioSystem(const AudioSystem& t);
	AudioSystem& operator=(const AudioSystem& t);
};

#endif