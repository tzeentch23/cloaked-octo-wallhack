#include "stdafx.h"    // for compiler
#include "../stdafx.h" // for intellisense

#include "Button.h"

//-----------------------------------------------------------------
// Button methods
//-----------------------------------------------------------------
Button::Button() :
GUIBase(),
m_bArmed(false),
m_BmpReleasedPtr(nullptr),
m_BmpPressedPtr(nullptr),
m_bImageMode(false)
{
	m_DefaultBackColor = m_BackColor = COLOR(227, 227, 227);
}

Button::Button(const String& text) :
GUIBase(text),
m_bArmed(false),
m_BmpReleasedPtr(nullptr),
m_BmpPressedPtr(nullptr),
m_bImageMode(false)
{
	m_DefaultBackColor = m_BackColor = COLOR(227, 227, 227);
}

//Button::Button(const string& text) :
//	GUIBase(text),
//	m_bArmed(false),
//	m_BmpReleasedPtr(nullptr),
//	m_BmpPressedPtr(nullptr),
//	m_bImageMode(false)
//{
//	m_DefaultBackColor = m_BackColor = COLOR(227, 227, 227);
//}


Button::~Button()
{
	delete m_BmpPressedPtr;
	delete m_BmpReleasedPtr;
}

//---------------------------
// Methods - Member functions
//---------------------------
void Button::Paint()
{
	if (m_BoundingRect.bottom - m_BoundingRect.top <= 0 ||
		m_BoundingRect.right - m_BoundingRect.left <= 0)
	{
		MessageBoxA(NULL, "Impossible to draw the Button, it has no valid bounds!", "GameEngine says NO", MB_OK);
		exit(-1);
	}
	// store original font
	Font *originalFont = GameEngine::GetSingleton()->GetFont();

	//automatically enable bitmapmode when the pointers are not nullptr
	if (m_BmpPressedPtr != nullptr && m_BmpReleasedPtr != nullptr) m_bImageMode = true;
	else m_bImageMode = false;

	if (!m_bImageMode) DrawClassicButton();
	else DrawImageButton();

	//restore font
	GameEngine::GetSingleton()->SetFont(originalFont);
}

void Button::DrawClassicButton()
{
	// Draw the borders
	RECT r = m_BoundingRect;
	GameEngine::GetSingleton()->SetColor(COLOR(101, 101, 101));
	GameEngine::GetSingleton()->FillRect(r.left, r.top, r.right, r.bottom);

	++r.left; ++r.top; --r.right; --r.bottom;
	if (!m_bArmed) GameEngine::GetSingleton()->SetColor(COLOR(254, 254, 254));
	else GameEngine::GetSingleton()->SetColor(COLOR(101, 101, 101));
	GameEngine::GetSingleton()->FillRect(r.left, r.top, r.right, r.bottom);

	// Fill interior
	++r.left; ++r.top; --r.right; --r.bottom;
	GameEngine::GetSingleton()->SetColor(m_BackColor);
	GameEngine::GetSingleton()->FillRect(r.left, r.top, r.right, r.bottom);

	// Set the Font
	GameEngine::GetSingleton()->SetFont(m_FontPtr);

	if (!m_bArmed)
	{

		GameEngine::GetSingleton()->SetColor(COLOR(101, 101, 101));
		GameEngine::GetSingleton()->DrawLine(m_BoundingRect.right - 1, m_BoundingRect.top + 1, m_BoundingRect.right - 1, m_BoundingRect.bottom - 1);
		GameEngine::GetSingleton()->DrawLine(m_BoundingRect.left + 1, m_BoundingRect.bottom - 1, m_BoundingRect.right - 1, m_BoundingRect.bottom - 1);

		GameEngine::GetSingleton()->SetColor(COLOR(160, 160, 160));
		GameEngine::GetSingleton()->DrawLine(m_BoundingRect.right - 2, m_BoundingRect.top + 2, m_BoundingRect.right - 2, m_BoundingRect.bottom - 2);
		GameEngine::GetSingleton()->DrawLine(m_BoundingRect.left + 2, m_BoundingRect.bottom - 2, m_BoundingRect.right - 2, m_BoundingRect.bottom - 2);

		// Draw fore color when this is enabled
		if (m_bEnabled)GameEngine::GetSingleton()->SetColor(m_ForeColor);

		// gray when disabled
		else GameEngine::GetSingleton()->SetColor(COLOR(187, 187, 187));

		GameEngine::GetSingleton()->DrawString(m_Text, m_BoundingRect);
	}
	else
	{
		GameEngine::GetSingleton()->SetColor(COLOR(101, 101, 101));
		GameEngine::GetSingleton()->DrawLine(m_BoundingRect.left + 2, m_BoundingRect.top + 2, m_BoundingRect.right - 2, m_BoundingRect.top + 2);
		GameEngine::GetSingleton()->DrawLine(m_BoundingRect.left + 2, m_BoundingRect.top + 2, m_BoundingRect.left + 2, m_BoundingRect.bottom - 2);

		GameEngine::GetSingleton()->SetColor(COLOR(160, 160, 160));
		GameEngine::GetSingleton()->DrawLine(m_BoundingRect.left + 2, m_BoundingRect.top + 3, m_BoundingRect.right - 3, m_BoundingRect.top + 3);
		GameEngine::GetSingleton()->DrawLine(m_BoundingRect.left + 3, m_BoundingRect.top + 3, m_BoundingRect.left + 3, m_BoundingRect.bottom - 3);

		//++r.left; ++r.top; --r.right; --r.bottom;
		//if (!m_bArmed) GameEngine::GetSingleton()->SetColor(COLOR(240, 240, 240));
		//else GameEngine::GetSingleton()->SetColor(COLOR(180, 180, 180));
		////GameEngine::GetSingleton()->SetColor(COLOR(240, 240, 240));
		//GameEngine::GetSingleton()->FillRect(r.left, r.top, r.right, r.bottom);
		GameEngine::GetSingleton()->SetColor(m_ForeColor);
		GameEngine::GetSingleton()->DrawString(m_Text, m_BoundingRect.left + 2, m_BoundingRect.top + 2, m_BoundingRect.right + 2, m_BoundingRect.bottom + 2);
	}
}

void Button::DrawImageButton()
{
	if (m_bArmed)
	{
		GameEngine::GetSingleton()->DrawBitmap(m_BmpPressedPtr, m_BoundingRect.left, m_BoundingRect.top);
	}
	else
	{
		GameEngine::GetSingleton()->DrawBitmap(m_BmpReleasedPtr, m_BoundingRect.left, m_BoundingRect.top);
	}
}

void Button::Tick(double deltaTime)
{
	if (!m_bEnabled)
	{
		m_bArmed = false;
		return;
	}

	MATRIX3X2 matInverse = (GameEngine::GetSingleton()->GetWorldMatrix() * GameEngine::GetSingleton()->GetViewMatrix()).Inverse();

	DOUBLE2 mouseScreenSpace(GameEngine::GetSingleton()->GetMousePosition().x, GameEngine::GetSingleton()->GetMousePosition().y);
	DOUBLE2 mouseViewSpace = matInverse.TransformPoint(mouseScreenSpace);

	//RMB in button rect armes the button and paint will draw the pressed button
	if (GameEngine::GetSingleton()->IsMouseButtonDown(VK_LBUTTON) && PointInRect(m_BoundingRect, mouseViewSpace))
	{
		m_bArmed = true;
	}
	else
	{
		//if mouse button is released while in rect, then pressed is true
		if (m_bArmed && !GameEngine::GetSingleton()->IsMouseButtonDown(VK_LBUTTON) && PointInRect(m_BoundingRect, mouseViewSpace))
		{
			m_bTriggered = true;
			m_bArmed = false;
		}
		//while armed the RMB is released or outside the rect, then armed is false
		else if (m_bArmed && (!GameEngine::GetSingleton()->IsMouseButtonDown(VK_LBUTTON) || !PointInRect(m_BoundingRect, mouseViewSpace)))
		{
			m_bArmed = false;
		}
	}
}

bool Button::IsPressed() const
{
	if (this == nullptr) MessageBoxA(NULL, "TextBox::IsPressed() called from a pointer that is a nullptr\nThe MessageBox that will appear after you close this MessageBox is the default error message from visual studio.", "GameEngine says NO", MB_OK);

	return m_bTriggered;
}

void Button::ConsumeEvent()
{
	m_bTriggered = false;
}

void Button::SetPressedBitmap(const String& filenameRef)
{
	m_BmpPressedPtr = new Bitmap(filenameRef);
}

void Button::SetPressedBitmap(int resourceID)
{
	m_BmpPressedPtr = new Bitmap(resourceID);
}

void Button::SetReleasedBitmap(const String& filenameRef)
{
	m_BmpReleasedPtr = new Bitmap(filenameRef);
}

void Button::SetReleasedBitmap(int resourceID)
{
	m_BmpReleasedPtr = new Bitmap(resourceID);
}

void Button::SetImageMode(bool bImageMode)
{
	m_bImageMode = bImageMode;
}