//-----------------------------------------------------
// Name: Kirkorova
// First name: Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "StartScreen.h"
#include "Roguelight.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
StartScreen::StartScreen()
{
	m_BmpBannerPtr = new Bitmap(String("./resources/start_background.png"));
	m_BmpTextPtr = new Bitmap(String("./resources/pressentertostart.png"));
}

StartScreen::~StartScreen()
{
	delete m_BmpBannerPtr;
	m_BmpBannerPtr = nullptr;
	delete m_BmpTextPtr;
	m_BmpTextPtr = nullptr;
}
void StartScreen::Paint()
{
	DOUBLE2 bannerPos = DOUBLE2(GAME_ENGINE->GetWidth() / 2 - m_BmpBannerPtr->GetWidth() / 2,
		GAME_ENGINE->GetHeight() / 2 - m_BmpBannerPtr->GetHeight() / 2);
	matTranslate.SetAsTranslate(bannerPos);
	matRotate.SetAsRotate(m_Angle);
	matRotate.SetAsScale(m_Scale);
	matWorldTransform = matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);
	GAME_ENGINE->DrawSolidBackground(COLOR(20, 26, 84));
	GAME_ENGINE->DrawBitmap(m_BmpBannerPtr);
	
	if (m_PrintText)
	{ 
		DOUBLE2 textPos = DOUBLE2((GAME_ENGINE->GetWidth()  - m_BmpTextPtr->GetWidth())/2,
			2 * (GAME_ENGINE->GetHeight() / 3) - m_BmpTextPtr->GetHeight() / 2);
		matTranslate.SetAsTranslate(textPos);
		GAME_ENGINE->SetWorldMatrix(matTranslate);
		GAME_ENGINE->DrawBitmap(m_BmpTextPtr);
	}
}

void StartScreen::Tick(double deltaTime)
{
	m_Time += deltaTime;
	if (m_Time >= 1)
	{
		m_PrintText = !m_PrintText;
		m_Time = 0;
	}
	if (GAME_ENGINE->IsKeyboardKeyPressed(VK_RETURN))
	{
		Roguelight::GAME->Start(); 
	}
}
