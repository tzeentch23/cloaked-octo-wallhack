//-----------------------------------------------------------------
// Game Engine Object
// C++ Header - version v2_16 jan 2015 
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

#pragma once

class Font;
//-----------------------------------------------------
// GUIBase Class									
//-----------------------------------------------------

class GUIBase
{
public:
	GUIBase();							// Default Constructor
	GUIBase(const String& textRef);				// Constructor
	//GUIBase(const std::string& textRef);		// Constructor
	virtual ~GUIBase();					// Destructor

	// C++11 make the class non-copyable
	GUIBase(const GUIBase&) = delete;
	GUIBase& operator=(const GUIBase&) = delete;

	friend class GameEngine;			//hide ConsumeEvent

	//-------------------------------------------------
	// Methods - Member functions							
	//-------------------------------------------------

	//! Replaces the current GUI text by the String text. 
	//! Example: myGuiPtr->SetText(String("new Text"));
	void SetText(const String& textRef);
	//! Returns a copy of the text that is currently in the GUI
	//! Example: String str = myGUIPtr->GetText();
	String GetText() const;
	//! Defines the position, width and height of the GUI  
	void SetBounds(int left, int top, int width, int height);
	//! Sets the font that wil be used for this GUI
	//! Example: myGUIPtr->SetFont(String("Consolas"),24);
	void SetFont(const String& typeRef, int height);


	//! enable/disable the textbox 
	//! Example: myGUIPtr->SetEnabled(false);
	void SetEnabled(bool bEnable);

	//! Sets the color of the background of the GUI
	//! Example: myGUIPtr->SetBackColor(COLOR(255,0,124));
	void SetBackColor(COLOR backColor);

	//! Sets the color of the foreground (text) of the GUI
	//! Example: myGUIPtr->SetForeColor(COLOR(255,255,10));
	void SetForeColor(COLOR foreColor);

	//! Sets the back color back default
	void SetDefaultBackColor();

	//! Sets the fore color back default
	void SetDefaultForeColor();

protected:
	bool PointInRect(RECT r, POINT pt) const;
	bool PointInRect(RECT r, DOUBLE2 pt) const;
	void LimitTextLengthToClientArea();
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	// dimension of bounding box of GUI
	RECT m_BoundingRect;

	// used to fit text in  box
	RECT m_ClientRect;

	// m_Text is used to draw, and is created by the LinitTextTo....
	// m_OriginalText is used to hold the original text
	String m_Text, m_OriginalText;
	Font *m_FontPtr;
	bool m_bTriggered;
	// True if the textbox is working as expected, false if disbled
	bool m_bEnabled;
	COLOR m_ForeColor, m_BackColor;
	COLOR m_DefaultForeColor, m_DefaultBackColor;

private:
	virtual void Paint() = 0;
	virtual void Tick(double deltaTime) = 0;
	// initializes members for all constructors 
	virtual void HandleKeyInput(TCHAR character){};
	virtual void ConsumeEvent() = 0;
	void Initialize();
};