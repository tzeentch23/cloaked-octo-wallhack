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
#include "Camera.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
PauseScreen::PauseScreen()
{
	m_BmpBackgroundPtr = new Bitmap(String("./resources/pause_background.png"));
	m_BmpMenuPtr = new Bitmap(String("./resources/pause_menu.png"));
	m_BmpControlsPtr = new Bitmap(String("./resources/pause_controls.png"));

}

PauseScreen::~PauseScreen()
{
	delete m_BmpBackgroundPtr;
	m_BmpBackgroundPtr = nullptr;

	delete m_BmpMenuPtr;
	m_BmpMenuPtr = nullptr;

	delete m_BmpControlsPtr;
	m_BmpControlsPtr = nullptr;
}
void PauseScreen::Paint()
{
	DOUBLE2 controlPos = DOUBLE2(GAME_ENGINE->GetWidth() / 2 - m_BmpControlsPtr->GetWidth() / 2,
		GAME_ENGINE->GetHeight() / 2 - m_BmpControlsPtr->GetHeight() / 2);
	DOUBLE2 menuPos = DOUBLE2(GAME_ENGINE->GetWidth() / 2 - m_BmpMenuPtr->GetWidth() / 2,
							GAME_ENGINE->GetHeight() / 2 - m_BmpMenuPtr->GetHeight() / 2);
	DOUBLE2 backgroundPos = DOUBLE2(GAME_ENGINE->GetWidth() / 2 - m_BmpBackgroundPtr->GetWidth() / 2,
							GAME_ENGINE->GetHeight() / 2 - m_BmpBackgroundPtr->GetHeight() / 2);
	DOUBLE2 origin = Roguelight::GAME->GetCamera()->GetCameraOrigin();
	DOUBLE2 originChange = DOUBLE2(origin.x - GAME_ENGINE->GetWidth() / 2, 
								   origin.y - GAME_ENGINE->GetHeight() / 2);
	matTranslate.SetAsTranslate(originChange);
	matRotate.SetAsRotate(m_Angle);
	matScale.SetAsScale(m_Scale);
	matPivot.SetAsTranslate(backgroundPos);
	matWorldTransform = matPivot * matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);
	GAME_ENGINE->DrawSolidBackground(COLOR(20, 26, 84));
	GAME_ENGINE->DrawBitmap(m_BmpBackgroundPtr);
	
	matTranslate.SetAsTranslate(originChange);
	matRotate.SetAsRotate(m_Angle);
	matScale.SetAsScale(m_Scale);
	matPivot.SetAsTranslate(menuPos);
	matWorldTransform = matPivot * matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);
	GAME_ENGINE->DrawBitmap(m_BmpMenuPtr);

	RECT2 Return, Quit, Controls;
	double rectHeight = m_BmpMenuPtr->GetHeight() / 3;
	Return.top = menuPos.y + 5;
	Return.bottom = menuPos.y + rectHeight;
	Controls.top = menuPos.y + rectHeight + 5;
	Controls.bottom = menuPos.y + rectHeight * 2;
	
	Quit.top = menuPos.y + rectHeight * 2;
	Quit.bottom = menuPos.y + rectHeight * 3;

	Return.left = Quit.left = Controls.left = menuPos.x;
	Return.right = Quit.right = Controls.right = menuPos.x + (m_BmpMenuPtr->GetWidth());

	matTranslate.SetAsTranslate(originChange);
	matRotate.SetAsRotate(m_Angle);
	matScale.SetAsScale(m_Scale);
	matWorldTransform = matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);
	GAME_ENGINE->SetColor(COLOR(31, 39, 209));
		switch (m_Choice)
		{
		case Choice::RETURN:
			GAME_ENGINE->DrawRect(Return, 5.0);
			break;
		case Choice::QUIT:
			GAME_ENGINE->DrawRect(Quit, 5.0);
			break;
		case Choice::CONTROLS:
			GAME_ENGINE->DrawRect(Controls, 5.0);
			break;
		}


		if (m_DrawControls)
		{
			matTranslate.SetAsTranslate(originChange);
			matRotate.SetAsRotate(m_Angle);
			matScale.SetAsScale(m_Scale);
			matPivot.SetAsTranslate(controlPos);
			matWorldTransform = matPivot * matRotate * matScale * matTranslate;
			GAME_ENGINE->SetWorldMatrix(matWorldTransform);
			GAME_ENGINE->DrawBitmap(m_BmpControlsPtr);
		}


	}

void PauseScreen::Tick(double deltaTime)
{
	if (GAME_ENGINE->IsKeyboardKeyPressed(VK_ESCAPE))
	{
		m_IsActive = false;
		return;
	}


	if (GAME_ENGINE->IsKeyboardKeyPressed(VK_UP))
	{
		switch (m_Choice)
		{
		case Choice::RETURN:
			m_Choice = Choice::QUIT;
			break;
		case Choice::QUIT:
			m_Choice = Choice::CONTROLS;
			break;
		case Choice::CONTROLS:
			m_Choice = Choice::RETURN;
			break;
		}

	}

	if (GAME_ENGINE->IsKeyboardKeyPressed(VK_DOWN))
	{
		switch (m_Choice)
		{
		case Choice::CONTROLS:
			m_Choice = Choice::QUIT;
			break;
		case Choice::QUIT:
			m_Choice = Choice::RETURN;
			break;
		case Choice::RETURN:
			m_Choice = Choice::CONTROLS;
			break;
		}

	}
	if (GAME_ENGINE->IsKeyboardKeyPressed(VK_RETURN))
	{
		switch (m_Choice)
		{
		case Choice::CONTROLS:
			m_DrawControls = true;
			break;
		case Choice::RETURN:
			m_IsActive = false;
			break;
		case Choice::QUIT:
			Roguelight::GAME->Quit();
			break;
		}

	}
				
}

void PauseScreen::SetActive(bool isActive)
{
	m_IsActive = isActive;
	m_DrawControls = false;
}

bool PauseScreen::IsActive()
{
	return m_IsActive;
}