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
#include "Moss.h"
#include "Spikes.h"
#include <fstream>
#include <string>
//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//-----------------------------------------------------------------
// Roguelight methods																				
//-----------------------------------------------------------------

Roguelight::Roguelight()
{
}

Roguelight::~Roguelight()																						
{
}

void Roguelight::GameInitialize(GameSettings &gameSettings)
{
	gameSettings.SetWindowTitle(String("Roguelight - Kirkorova Angelika, 1DAE2"));
	gameSettings.SetWindowWidth((int)(m_Width));
	gameSettings.SetWindowHeight((int)(m_Height));
	gameSettings.EnableConsole(false);
	gameSettings.EnableAntiAliasing(true);
}

void Roguelight::GameStart()
{
	m_MossArr.push_back(new Moss(DOUBLE2(2121.79, 615.72)));
	
	m_BmpLvlPtr = new Bitmap(String("./resources/levelmap.png"));

	DOUBLE2 elfSpawn(m_BmpLvlPtr->GetWidth()/2+200, 20);
	m_ElfPtr = new Elf(elfSpawn);

	m_ActLevelPtr = new PhysicsActor(DOUBLE2(0, 0), 0, BodyType::STATIC);	
	m_ActLevelPtr->AddSVGShape(String("./resources/LevelSVG.svg"), 0 ,0.2, 0);

	m_CameraDimension.topLeft.x = m_Width / 2;
	m_CameraDimension.topLeft.y = m_Height / 2;
	m_CameraDimension.bottomRight.x = m_BmpLvlPtr->GetWidth() - m_Width / 2;
	m_CameraDimension.bottomRight.y = m_BmpLvlPtr->GetHeight() - m_Height / 2;
	cameraSize = DOUBLE2(m_Width, m_Height);
	LoadMoss();
	LoadSpikes();
}

void Roguelight::GameEnd()
{
	delete m_ActLevelPtr;
	m_ActLevelPtr = nullptr;
	delete m_BmpLvlPtr;
	m_BmpLvlPtr = nullptr;
	delete m_ElfPtr;
	m_ElfPtr = nullptr;
	m_MossArr.clear();
	m_SpikesArr.clear();
}

void Roguelight::GameTick(double deltaTime)
{
	m_ElfPtr->Tick(deltaTime);
	if (GAME_ENGINE->IsKeyboardKeyDown('P'))
	{
		m_IsPhysicsDebudRendering = !m_IsPhysicsDebudRendering;
		GAME_ENGINE->EnablePhysicsDebugRendering(m_IsPhysicsDebudRendering);
	}

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

	
	if (((m_ElfPos.x + MAX_RIGHT) < m_BmpLvlPtr->GetWidth()) && ((m_ElfPos.x - MIN_LEFT) >= 0))
	{
		m_CameraPos.x = m_ElfPos.x;
	}

	if (1 && (m_ElfPos.y < m_Height - cameraSize.y)) {
		m_CameraPos.y = m_ElfPos.y;
	}

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
	m_ElfPos = m_ElfPtr->GetPosition();


}

void Roguelight::GamePaint(RECT rect)
{
	String Pos = String(m_ElfPos.x) + String(" ") + String(m_ElfPos.y);
	GAME_ENGINE->DrawBitmap(m_BmpLvlPtr, 0, 0);
	m_ElfPtr->Paint();
	Camera();
	for (size_t i = 0; i < m_MossArr.size(); i++)
	{
		m_MossArr[i]->Paint();
	}
	for (size_t i = 0; i < m_SpikesArr.size(); i++)
	{
		m_SpikesArr[i]->Paint();
	}

}

void Roguelight::Camera() 
{
	matCamRotate.SetAsRotate(m_CameraAngle);
	matCamTranslate.SetAsTranslate(m_ElfPos);
	matCamScale.SetAsScale(m_CameraScale);
	matPivot.SetAsTranslate(-GAME_ENGINE->GetWidth() / 2, -GAME_ENGINE->GetHeight() / 2);
	matCamera = matPivot* matCamScale * matCamRotate * matCamTranslate;
	matCamWorldTransform = matCamera.Inverse();
	GAME_ENGINE->SetViewMatrix(matCamWorldTransform);
	}


void Roguelight::LoadMoss() 
{
	std::wifstream ifileMoss;
	ifileMoss.open("./resources/Moss_Positions.txt");
	std::wstring extractedLine;
	while (ifileMoss.eof() == false)
	{
		std::getline(ifileMoss, extractedLine);
		int splitPos = extractedLine.find(',');
		if (splitPos == -1) 
		{

			OutputDebugString(String("Invalid coords:") + String(extractedLine.c_str()));
			continue;
		}
		double x = stod(extractedLine.substr(0, splitPos)); 
		double y = stod(extractedLine.substr(splitPos+1, extractedLine.length()));
		m_MossArr.push_back(new Moss(DOUBLE2(x, y)));

	}
}

void Roguelight::LoadSpikes()
{
	std::wifstream ifileSpikes;
	ifileSpikes.open("./resources/Spikes_Positions.txt");
	std::wstring extractedLine;
	while (ifileSpikes.eof() == false)
	{
		std::getline(ifileSpikes, extractedLine);
		int splitPos = extractedLine.find(',');
		if (splitPos == -1)
		{
			OutputDebugString(String("Invalid coords:") + String(extractedLine.c_str()));
			continue;
		}
		double x = stod(extractedLine.substr(0, splitPos));
		double y = stod(extractedLine.substr(splitPos + 1, extractedLine.length()));
		m_SpikesArr.push_back(new Spikes(DOUBLE2(x, y)));

	}

}