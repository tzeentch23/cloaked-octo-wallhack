//-----------------------------------------------------------------
// Game Engine Object
// C++ Header - version v2_16 jan 2015 
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

#pragma once

class GameSettings
{
public:
	GameSettings(void);
	virtual ~GameSettings(void);

	// C++11 make the class non-copyable
	GameSettings(const GameSettings&) = delete;
	GameSettings& operator=(const GameSettings&) = delete;

	//! Defines the title that will appear in the window
	void SetWindowTitle(const String& titleRef);
	//! Defines the width of the client area of the window (without borders)
	void SetWindowWidth(int width);
	//! Defines the height of the client area of the window (without borders)
	void SetWindowHeight(int height);
	//! Do you want a console?
	void EnableConsole(bool state);
	//! True locks the framerate to the display vertical frequency (60Hz in most cases)
	void EnableVSync(bool state);
	//! True enable smooth drawing and filling of shapes
	void EnableAntiAliasing(bool state);
	//! Enable PhysicsDebugRendering
	//void EnablePhysicsDebugRendering(bool state);

	// Not intended to be used by students
	String GetWindowTitle();
	// Not intended to be used by students
	int GetWindowWidth();
	// Not intended to be used by students
	int GetWindowHeight();
	// Not intended to be used by students
	bool IsConsoleEnabled();
	// Not intended to be used by students
	bool IsVSync();
	// Not intended to be used by students
	bool IsAntiAliasingEnabled();
	// Not intended to be used by students
	// bool IsDebugRenderingEnabled();

private:
	String	m_WindowTitle;
	int		m_WindowWidth;
	int		m_WindowHeight;
	bool	m_bEnableConsole;
	bool	m_bVSync;
	bool	m_bEnableAntiAliasing;
	//bool	m_EnableDebugRendering = false;
};
