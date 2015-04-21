//-----------------------------------------------------------------
// Game File
// C++ Source - Roguelight.cpp - version v2_16 jan 2015
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------
#include "stdafx.h"		// this include must be the first include line of every cpp file (due to using precompiled header)
#include "Elf.h"
#include "Enemies.h"
//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Roguelight.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//-----------------------------------------------------------------
// Roguelight methods																				
//-----------------------------------------------------------------

Roguelight::Roguelight()
{
	// nothing to create
}

Roguelight::~Roguelight()																						
{
	// nothing to destroy
}

void Roguelight::GameInitialize(GameSettings &gameSettings)
{
	gameSettings.SetWindowTitle(String("Roguelight - Kirkorova Angelika, 1DAE2"));
	gameSettings.SetWindowWidth(m_Width*3);
	gameSettings.SetWindowHeight(m_Height*2);
	gameSettings.EnableConsole(false);
	gameSettings.EnableAntiAliasing(false);
}

void Roguelight::GameStart()
{
	
	m_BmpLvlPtr = new Bitmap(String("./resources/levelmap.png"));

	DOUBLE2 elfSpawn(m_BmpLvlPtr->GetWidth()/2+200, 20);
	m_ElfPtr = new Elf(elfSpawn);
	
	
	m_ActLevelPtr = new PhysicsActor(DOUBLE2(0, 0), 0, BodyType::STATIC);	
	m_ActLevelPtr->AddSVGShape(String("./resources/LevelSVG.svg"), 0 ,0.2, 1.0);

	m_CameraDimension.topLeft.x = m_Width / 2;
	m_CameraDimension.topLeft.y = m_Height / 2;
	m_CameraDimension.bottomRight.x = m_BmpLvlPtr->GetWidth() - m_Width / 2;
	m_CameraDimension.bottomRight.y = m_BmpLvlPtr->GetHeight() - m_Height / 2;
	cameraSize = DOUBLE2(m_Width, m_Height);
	
}

void Roguelight::GameEnd()
{
	delete m_ActLevelPtr;
	m_ActLevelPtr = nullptr;
	delete m_BmpLvlPtr;
	m_BmpLvlPtr = nullptr;
	delete m_ElfPtr;
	m_ElfPtr = nullptr;
}

void Roguelight::GameTick(double deltaTime)
{
	m_ElfPtr->Tick(deltaTime);
	GAME_ENGINE->EnablePhysicsDebugRendering(true);

	if (GAME_ENGINE->IsKeyboardKeyDown(VK_PRIOR))
	{
		m_CameraScale -= 0.05;
	}

	if (GAME_ENGINE->IsKeyboardKeyDown(VK_NEXT))
	{
		m_CameraScale += 0.05;
	}

	if (GAME_ENGINE->IsKeyboardKeyDown(VK_UP)) 
	{
		m_CameraPos.y -= 5;
	}

	if (GAME_ENGINE->IsKeyboardKeyDown(VK_DOWN)) 
	{
		m_CameraPos.y += 5;
	}

	if (GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT)) 
	{
		m_CameraPos.x -= 5;
	}

	if (GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT)) 
	{
		m_CameraPos.x += 5;
	}
	if (GAME_ENGINE->IsKeyboardKeyDown('R')) 
	{
		m_CameraAngle += 0.2;
	}
	if (GAME_ENGINE->IsKeyboardKeyDown('T')) 
	{
		m_CameraAngle -= 0.2;
	}

	DOUBLE2 elfPos = m_ElfPtr->GetPosition();

	if (((elfPos.x + MAX_RIGHT) < m_BmpLvlPtr->GetWidth()) && ((elfPos.x - MIN_LEFT) >= 0))
	{
		m_CameraPos.x = elfPos.x;
	}

	if (1 && (elfPos.y < m_Height - cameraSize.y)) {
		m_CameraPos.y = elfPos.y;
	}

	//if (1 && (cameraSize.y / m_CameraScale < m_Height)) {
	//	cameraSize.y = m_Height;
	//	m_CameraScale = cameraSize.y / m_Height;
	//}

	cameraSize *= m_CameraScale;

	if (m_CameraPos.y < m_Height - cameraSize.y / 2)
	{
		m_CameraPos.y = cameraSize.y / 2;
	}	
	if (m_CameraPos.y > cameraSize.y / 2)
	{
		m_CameraPos.y = cameraSize.y / 2;
	}	
	if (m_CameraPos.x < cameraSize.x / 2)
	{
		m_CameraPos.x = cameraSize.x / 2;
	}
	if (m_CameraPos.x > m_BmpLvlPtr->GetWidth() - cameraSize.x / 2)
	{
		m_CameraPos.x = m_BmpLvlPtr->GetWidth() - cameraSize.x / 2;
	}
		
}

void Roguelight::GamePaint(RECT rect)
{
	GAME_ENGINE->DrawBitmap(m_BmpLvlPtr, 0, 0);
	m_ElfPtr->Paint();
	Camera();
}

void Roguelight::Camera() 
{
	DOUBLE2 elfPos = m_ElfPtr->GetPosition();
	matCamRotate.SetAsRotate(m_CameraAngle);
	matCamTranslate.SetAsTranslate(elfPos);
	matCamScale.SetAsScale(m_CameraScale);
	matPivot.SetAsTranslate(-GAME_ENGINE->GetWidth() / 2, -GAME_ENGINE->GetHeight() / 2);
	matCamera = matPivot* matCamScale * matCamRotate * matCamTranslate;
	matCamWorldTransform = matCamera.Inverse();
	GAME_ENGINE->SetViewMatrix(matCamWorldTransform);
}


