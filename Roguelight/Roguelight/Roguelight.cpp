//-----------------------------------------------------------------
// Game File
// C++ Source - Roguelight.cpp - version v2_16 jan 2015
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------
#include "stdafx.h"	
using namespace std;
//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Roguelight.h"					
#include "Elf.h"
#include "Enemy.h"
#include "Shadyguy.h"
#include "Skelethon.h"
#include "Moss.h"
#include "Spike.h"
#include "Collectible.h"
#include "HUD.h"
#include <fstream>
#include <string>
//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//-----------------------------------------------------------------
// Roguelight methods																				
//-----------------------------------------------------------------
Roguelight * Roguelight::GAME = nullptr;

Roguelight::Roguelight()
{
	GAME = this;
}

Roguelight::~Roguelight()
{

}

void Roguelight::GameInitialize(GameSettings &gameSettings)
{
	gameSettings.SetWindowTitle(String("Roguelight"));
	gameSettings.SetWindowWidth((int)(m_Width));
	gameSettings.SetWindowHeight((int)(m_Height));
	gameSettings.EnableConsole(false);
	gameSettings.EnableAntiAliasing(true);
}

void Roguelight::GameStart()
{
	m_BmpLvlPtr = new Bitmap(String("./resources/levelmap.png"));

	m_BmpShadyGuyPtr = new Bitmap(String("./resources/enemy_shadyguy.png"));
	m_BmpSkelethonPtr = new Bitmap(String("./resources/enemy_skelethon.png"));

	m_HudArr.push_back(new HUD(HUD::Type::HEALTH, this));
	m_HudArr.push_back(new HUD(HUD::Type::COINS, this));
	m_HudArr.push_back(new HUD(HUD::Type::AMMO, this));

	DOUBLE2 elfSpawn(1925.57, 533.34);
	m_ElfPtr = new Elf(elfSpawn);

	m_ActLevelPtr = new PhysicsActor(DOUBLE2(0, 0), 0, BodyType::STATIC);
	m_ActLevelPtr->AddSVGShape(String("./resources/LevelSVG.svg"), 0, 0.2, 0);

	m_CameraDimension.topLeft.x = m_Width / 2;
	m_CameraDimension.topLeft.y = m_Height / 2;
	m_CameraDimension.bottomRight.x = m_BmpLvlPtr->GetWidth() - m_Width / 2;
	m_CameraDimension.bottomRight.y = m_BmpLvlPtr->GetHeight() - m_Height / 2;
	m_CameraSize = DOUBLE2(m_Width, m_Height);
	InitGame();

	matTranslate.SetAsTranslate(m_Translate);
	matRotate.SetAsRotate(m_Angle);
	matScale.SetAsScale(m_Scale);
	matWorldTransform = matRotate*matScale*matTranslate;
}

void Roguelight::GameEnd()
{
	delete m_ActLevelPtr;
	m_ActLevelPtr = nullptr;
	delete m_BmpLvlPtr;
	m_BmpLvlPtr = nullptr;
	delete m_ElfPtr;
	m_ElfPtr = nullptr;
	delete m_BmpShadyGuyPtr;
	m_BmpShadyGuyPtr;
	delete m_BmpSkelethonPtr;
	m_BmpSkelethonPtr = nullptr;

	for (size_t i = 0; i < m_MossArr.size(); i++)
	{
		delete m_MossArr[i];
		m_MossArr[i] = nullptr;
	}

	for (size_t i = 0; i < m_SpikeArr.size(); i++)
	{
		delete m_SpikeArr[i];
		m_SpikeArr[i] = nullptr;
	}

	for (size_t i = 0; i < m_HeartArr.size(); i++)
	{
		delete m_HeartArr[i];
		m_HeartArr[i] = nullptr;
	}

	for (size_t i = 0; i < m_ArrowArr.size(); i++)
	{
		delete m_ArrowArr[i];
		m_ArrowArr[i] = nullptr;
	}

	for (size_t i = 0; i < m_CoinArr.size(); i++)
	{
		delete m_CoinArr[i];
		m_CoinArr[i] = nullptr;
	}

	for (size_t i = 0; i < m_ShadyguyArr.size(); i++)
	{
		delete m_ShadyguyArr[i];
		m_ShadyguyArr[i] = nullptr;
	}
	for (size_t i = 0; i < m_SkelethonArr.size(); i++)
	{
		delete m_SkelethonArr[i];
		m_SkelethonArr[i] = nullptr;
	}

	for (size_t i = 0; i < m_HudArr.size(); i++)
	{
		delete m_HudArr[i];
		m_HudArr[i] = nullptr;
	}

	m_HudArr.clear();
	m_SkelethonArr.clear();
	m_ShadyguyArr.clear();
	m_MossArr.clear();
	m_SpikeArr.clear();
	m_ArrowArr.clear();
	m_CoinArr.clear();
	m_HeartArr.clear();
}


void Roguelight::GameTick(double deltaTime)
{
	m_ElfPtr->Tick(deltaTime);
	m_ElfPos = m_ElfPtr->GetPosition();

	if (GAME_ENGINE->IsKeyboardKeyPressed('P'))
	{
		m_IsPhysicsDebudRendering = !m_IsPhysicsDebudRendering;
		GAME_ENGINE->EnablePhysicsDebugRendering(m_IsPhysicsDebudRendering);
	}
	if (m_CameraScale >= 0.3)
	{
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_PRIOR))
		{
			m_CameraScale -= 0.02;
			m_CameraSize = DOUBLE2(m_Width, m_Height) * m_CameraScale;
		}
	}
	if (m_CameraScale <= 0.8)
	{
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_NEXT))
		{
			m_CameraScale += 0.02;
			m_CameraSize = DOUBLE2(m_Width, m_Height) * m_CameraScale;
			OutputDebugString(String("m_CameraSize : ") + String(m_CameraScale) + String(" ") + String(m_CameraSize.y) + String(" ") + String(m_CameraScale) + String('\n'));
		}
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

	m_CameraPos.y = m_ElfPos.y;

	if (0 && m_CameraSize.y / m_CameraScale < m_Height)
	{
		m_CameraSize.y = m_Height;
		m_CameraScale = m_CameraSize.y / m_Height;
	}

	if (1 && m_CameraPos.y < m_Height - m_CameraSize.y / 2)
	{
		m_CameraPos.y = m_CameraSize.y / 2;
	}
	if (1 && m_CameraPos.y + m_CameraSize.y / 2 > m_BmpLvlPtr->GetHeight())
	{
		m_CameraPos.y = m_CameraSize.y / 2;
	}

	if (m_CameraPos.x < m_CameraSize.x / 2)
	{
		m_CameraPos.x = m_CameraSize.x / 2;
	}

	if (m_CameraPos.x > m_BmpLvlPtr->GetWidth() - m_CameraSize.x / 2)
	{
		m_CameraPos.x = m_BmpLvlPtr->GetWidth() - m_CameraSize.x / 2;
	}

	if (0 && m_CameraPos.y > m_BmpLvlPtr->GetHeight() - m_CameraSize.y / 2)
	{
		m_CameraPos.y = m_BmpLvlPtr->GetHeight() - m_CameraSize.y / 2;
	}



	for (size_t i = 0; i < m_ArrowArr.size(); i++)
	{

		if (!m_ArrowArr[i]->IsConsumed())
		{
			m_ArrowArr[i]->Tick(deltaTime);
		}
	}
	for (size_t i = 0; i < m_CoinArr.size(); i++)
	{

		if (!m_CoinArr[i]->IsConsumed())
		{
			m_CoinArr[i]->Tick(deltaTime);
		}
	}
	for (size_t i = 0; i < m_HeartArr.size(); i++)
	{
		if (!m_HeartArr[i]->IsConsumed())
		{
			m_HeartArr[i]->Tick(deltaTime);
		}
	}
	for (size_t i = 0; i < m_ShadyguyArr.size(); i++)
	{
		m_ShadyguyArr[i]->Tick(deltaTime);
	}
	for (size_t i = 0; i < m_SkelethonArr.size(); i++)
	{
		m_SkelethonArr[i]->Tick(deltaTime);
	}

}

void Roguelight::GamePaint(RECT rect)
{
	matTranslate.SetAsTranslate(m_Translate);
	matRotate.SetAsRotate(0);
	matRotate.SetAsScale(1);
	matWorldTransform = matRotate * matScale * matTranslate;

	GAME_ENGINE->DrawBitmap(m_BmpLvlPtr);

	m_ElfPtr->Paint();

	for (size_t i = 0; i < m_MossArr.size(); i++)
	{
		m_MossArr[i]->Paint();
	}

	for (size_t i = 0; i < m_SpikeArr.size(); i++)
	{
		m_SpikeArr[i]->Paint();
	}

	for (size_t i = 0; i < m_ArrowArr.size(); i++)
	{
		if (!m_ArrowArr[i]->IsConsumed())
			m_ArrowArr[i]->Paint();
	}

	for (size_t i = 0; i < m_CoinArr.size(); i++)
	{
		if (!m_CoinArr[i]->IsConsumed())
			m_CoinArr[i]->Paint();
	}

	for (size_t i = 0; i < m_HeartArr.size(); i++)
	{
		if (!m_HeartArr[i]->IsConsumed())
			m_HeartArr[i]->Paint();
	}
	for (size_t i = 0; i < m_ShadyguyArr.size(); i++)
	{
		m_ShadyguyArr[i]->Paint();
	}
	for (size_t i = 0; i < m_SkelethonArr.size(); i++)
	{
		m_SkelethonArr[i]->Paint();
	}
	for (size_t i = 0; i < m_HudArr.size(); i++)
	{
		m_HudArr[i]->Paint();
	}

	Camera();
}

void Roguelight::Camera()
{
	matCamRotate.SetAsRotate(m_CameraAngle);
	matCamTranslate.SetAsTranslate(m_CameraPos);
	matCamScale.SetAsScale(m_CameraScale);
	matPivot.SetAsTranslate(-GAME_ENGINE->GetWidth() / 2, -GAME_ENGINE->GetHeight() / 2);
	matCamera = matPivot* matCamScale * matCamRotate * matCamTranslate;
	matCamWorldTransform = matCamera.Inverse();
	GAME_ENGINE->SetViewMatrix(matCamWorldTransform);
}
DOUBLE2 Roguelight::GetCameraOrigin()
{
	return m_CameraPos;
}

void Roguelight::InitGame()
{
	wstring extractedLine;
	wifstream txt;
	wstring last;

	txt.open("./resources/GameInit.txt");
	if (!txt.is_open())
	{
		cout << "propblem opening file" << endl;
		return;
	}

	while (!txt.eof()) {
		getline(txt, extractedLine);

		if (extractedLine.find(L"//") == 0) {
			continue;
		}
		int start = extractedLine.find(L'<');
		if (start == 0)
		{
			last = L"";
			last += extractedLine;
			continue;
		}

		int end = extractedLine.rfind(L"/>");
		if (end == 0)
		{
			last += extractedLine;
			ParseItem(last);
			continue;
		}
		last += extractedLine;
	}
}

DOUBLE2 Roguelight::ParsePosition(std::wstring & item)
{
	int firstIdx = item.find(L"x=\"");
	firstIdx += 3;
	int lastIdx = item.find('"', firstIdx);
	DOUBLE2 pos;
	pos.x = stod(item.substr(firstIdx, lastIdx - firstIdx));

	firstIdx = item.find(L"y=\"");
	firstIdx += 3;
	lastIdx = item.find('"', firstIdx);
	pos.y = stod(item.substr(firstIdx, lastIdx - firstIdx));
	return pos;
}

void Roguelight::ParseItem(wstring & item)
{
	if (item.find(L"Shadyguy") == 1)
	{
		ParseShadyguy(item);
	}
	else if (item.find(L"Moss") == 1)
	{
		ParseMoss(item);
	}
	else if (item.find(L"Spike") == 1)
	{
		ParseSpike(item);
	}
	else if (item.find(L"Heart") == 1)
	{
		ParseHeart(Collectible::HEARTS, item, m_HeartArr);
	}
	else if (item.find(L"Coin") == 1)
	{
		ParseCoin(Collectible::COINS, item, m_CoinArr);
	}
	else if (item.find(L"Arrow") == 1)
	{
		ParseArrow(Collectible::ARROWS, item, m_ArrowArr);
	}
	else if (item.find(L"Skelethon") == 1)
	{
		ParseSkelethon(item);
	}

}

void Roguelight::ParseMoss(std::wstring & item)
{
	DOUBLE2 pos = ParsePosition(item);
	pos.y += 30;
	m_MossArr.push_back(new Moss(pos));
}

void Roguelight::ParseSpike(std::wstring & item)
{
	DOUBLE2 pos = ParsePosition(item);
	pos.y += 15;
	m_SpikeArr.push_back(new Spike(pos));
}

void Roguelight::ParseHeart(Collectible::Type type, std::wstring & item, std::vector<Collectible *> & arrayPtr)
{
	DOUBLE2 pos = ParsePosition(item);
	arrayPtr.push_back(new Collectible(pos, type));

}

void Roguelight::ParseArrow(Collectible::Type type, std::wstring & item, std::vector<Collectible *> & arrayPtr)
{
	DOUBLE2 pos = ParsePosition(item);
	arrayPtr.push_back(new Collectible(pos, type));

}

void Roguelight::ParseCoin(Collectible::Type type, std::wstring & item, std::vector<Collectible *> & arrayPtr)
{
	DOUBLE2 pos = ParsePosition(item);
	arrayPtr.push_back(new Collectible(pos, type));

}

void Roguelight::ParseShadyguy(std::wstring & item)
{
	DOUBLE2 pos = ParsePosition(item);
	m_ShadyguyArr.push_back(new Shadyguy(pos, m_BmpShadyGuyPtr));
}

void Roguelight::ParseSkelethon(std::wstring & item)
{
	DOUBLE2 pos = ParsePosition(item);
	m_SkelethonArr.push_back(new Skelethon(pos, m_BmpSkelethonPtr));
}

PhysicsActor * Roguelight::GetLevelActor()
{
	return m_ActLevelPtr;
}

DOUBLE2 Roguelight::GetCameraSize()
{
	return m_CameraSize;
}