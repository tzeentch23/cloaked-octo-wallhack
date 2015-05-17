//-----------------------------------------------------
// Name:
// First name:
// Group: 1DAE.
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
	m_BmpBannerPtr = new Bitmap(String("./resources/banner.png"));

}

StartScreen::~StartScreen()
{
	delete m_BmpBannerPtr;
	m_BmpBannerPtr = nullptr;
}
void StartScreen::Paint()
{
	//ami tuk i a vryshtas.. ili ne znam iaaza
	DOUBLE2 bannerPos = DOUBLE2(GAME_ENGINE->GetWidth() / 2 - m_BmpBannerPtr->GetWidth() / 2,
		GAME_ENGINE->GetHeight() / 2 - m_BmpBannerPtr->GetHeight() / 2);
	matTranslate.SetAsTranslate(bannerPos);
	matRotate.SetAsRotate(m_Angle);
	matRotate.SetAsScale(m_Scale);
	matWorldTransform = matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);

	GAME_ENGINE->DrawBitmap(m_BmpBannerPtr);
}

void StartScreen::Tick(double deltaTime)
{
	if (GAME_ENGINE->IsKeyboardKeyPressed(VK_RETURN))
	{
		Roguelight::GAME->Start(); //shtoto tuk se samoiztivame..  no moje i da e ok..
		//ok daj da opitame.. nyc, ne si syzdala takyva obekt huh? ami koj shte ti napravi new    
		return;
	}
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
//void StartScreen::BeginContact(PhStartScreensicsActor *actThisPtr, PhStartScreensicsActor *actOtherPtr)
//{
//
//}
//
//void StartScreen::EndContact(PhStartScreensicsActor *actThisPtr, PhStartScreensicsActor *actOtherPtr)
//{
//
//}
//
//void StartScreen::ContactImpulse(PhStartScreensicsActor *actThisPtr, double impulse)
//{
//
//}


