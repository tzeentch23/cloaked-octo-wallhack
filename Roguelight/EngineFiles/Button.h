//-----------------------------------------------------------------
// Game Engine Object
// C++ Header - version v2_16 jan 2015 
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

#pragma once

#include "GUIBase.h"

class Bitmap;
//-----------------------------------------------------------------
// Button Class
//-----------------------------------------------------------------
class Button : public GUIBase
{
public:
	//! Default Constructor: no text will appear on the Button
	Button();
	//! Constructor: Example: m_BtnPtr = new Button(String("Some Text"));
	Button(const String& textRef);
	//! Constructor: Example: m_BtnPtr = new Button(string("Some Text"));
	//Button(const std::string& text);	
	virtual ~Button();		// Destructor

	// C++11 make the class non-copyable
	Button(const Button&) = delete;
	Button& operator=(const Button&) = delete;

	//-------------------------------------------------
	// Methods - Member functions							
	//-------------------------------------------------

	//! returns true if the button is pressed
	bool IsPressed() const;
	//! Name of the bitmap to be showed when the button is pressed
	void SetPressedBitmap(const String& filenameRef);
	//! Resource Id of the bitmap to be showed when the button is pressed
	void SetPressedBitmap(int resourceID);

	//! Name of the bitmap to be showed when the button is not pressed
	void SetReleasedBitmap(const String& filenameRef);
	//! Resource Id of the bitmap to be showed when the button is not pressed
	void SetReleasedBitmap(int resourceID);

	//! if true, the bitmaps will be used to visualize the button
	void SetImageMode(bool bImageMode);

protected:

private:
	// Internal use only
	virtual void ConsumeEvent();
	virtual void Paint();
	virtual void Tick(double deltaTime);
	void DrawClassicButton();
	void DrawImageButton();

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	bool m_bArmed, m_bImageMode;
	Bitmap* m_BmpReleasedPtr, *m_BmpPressedPtr;
};