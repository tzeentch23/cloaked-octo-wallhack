//-----------------------------------------------------------------
// Game Engine Object
// C++ Header - version v2_16 jan 2015 
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

#pragma once

#include "GUIBase.h"

//-----------------------------------------------------------------
// TextBox Class
//-----------------------------------------------------------------
class TextBox : public GUIBase
{
public:
	//! Default Constructor: No text will appear in the TextBox
	TextBox();
	//! Constructor: Example: m_TxtPtr = new TextBox(String("Some Text"));
	TextBox(const String& textRef);	//! Constructor
	//Constructor: Example: m_TxtPtr = new TextBox(string("Some Text"));
	//TextBox(const std::string& text);	// Constructor
	// Destructor
	virtual ~TextBox();

	// C++11 make the class non-copyable
	TextBox(const TextBox&) = delete;
	TextBox& operator=(const TextBox&) = delete;

	//-------------------------------------------------
	// Methods - Member functions							
	//-------------------------------------------------
	//! returns true if the the enter key was pressed while the textbox was active
	bool IsEntered() const;
	//! overridden, client area is smaller
	void SetBounds(int left, int top, int width, int height);
protected:

private:
	// Internal use only
	virtual void ConsumeEvent();
	// Internal use only
	virtual void Paint();
	// Internal use only
	virtual void Tick(double deltaTime);
	// Internal use only
	void DrawCaret();
	// Internal use only
	virtual void HandleKeyInput(TCHAR character);

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	// Has focus
	bool m_bArmed;
	// Frequency at wich the caret blinks
	double m_BlinkFrequency;
	// Used for blinking
	double m_AccumulatedTime;
	// caret blinks: draw or not? 
	bool m_bCaretBlinkState;
	// Client area inset: how many pixels from the bounds to the characters
	const int m_ClientInset = 2;
};