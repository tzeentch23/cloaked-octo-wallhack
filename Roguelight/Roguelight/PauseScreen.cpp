//-----------------------------------------------------
// Name: Kirkorova
// First name: Angelika 
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "PauseScreen.h"
#include "Roguelight.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
PauseScreen::PauseScreen()
{
	m_BmpBannerPtr = new Bitmap(String("./resources/banner.png"));

}

PauseScreen::~PauseScreen()
{
	delete m_BmpBannerPtr;
	m_BmpBannerPtr = nullptr;
}
void PauseScreen::Paint()
{
	DOUBLE2 bannerPos = DOUBLE2(GAME_ENGINE->GetWidth() / 2 - m_BmpBannerPtr->GetWidth() / 2,
		GAME_ENGINE->GetHeight() / 2 - m_BmpBannerPtr->GetHeight() / 2);
	DOUBLE2 originChange = DOUBLE2(Roguelight::GAME->GetCameraOrigin().x - GAME_ENGINE->GetWidth() / 2, 
		Roguelight::GAME->GetCameraOrigin().y - GAME_ENGINE->GetHeight() / 2);
	matTranslate.SetAsTranslate(originChange);
	matRotate.SetAsRotate(m_Angle);
	matRotate.SetAsScale(m_Scale);
	matPivot.SetAsTranslate(bannerPos);
	matWorldTransform = matPivot * matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);
	GAME_ENGINE->DrawSolidBackground(COLOR(0, 0, 0));
	GAME_ENGINE->DrawBitmap(m_BmpBannerPtr);
}

void PauseScreen::Tick(double deltaTime)
{
		if (GAME_ENGINE->IsKeyboardKeyPressed(VK_ESCAPE))
		{
			m_IsActive = false;
			return;
		}	
}

void PauseScreen::SetActive(bool isActive)
{
	m_IsActive = isActive;
}

bool PauseScreen::IsActive()
{
	return m_IsActive;
}