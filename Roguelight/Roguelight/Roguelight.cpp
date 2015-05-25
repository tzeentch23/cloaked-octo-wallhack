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
#include "Camera.h"
#include "Elf.h"
#include "Enemy.h"
#include "Shadyguy.h"
#include "Skelethon.h"
#include "Cthulhu.h"
#include "Moss.h"
#include "Spike.h"
#include "Collectible.h"
#include "HUD.h"
#include "Bullet.h"
#include "Lamp.h"
#include "StartScreen.h"
#include "PauseScreen.h"
#include "Session.h"
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
	m_Session = new Session();
}

Roguelight::~Roguelight()
{

}

void Roguelight::GameInitialize(GameSettings &gameSettings)
{
	gameSettings.SetWindowTitle(String("Roguelight"));
	gameSettings.SetWindowWidth((int)(Camera::GAME_WIDTH));
	gameSettings.SetWindowHeight((int)(Camera::GAME_HEIGHT));
	gameSettings.EnableConsole(false);
	gameSettings.EnableAntiAliasing(true);
}

void Roguelight::GameStart()
{
	m_StartScrPtr = new StartScreen();
	m_PauseScrPtr = new PauseScreen();

	m_BmpLvlPtr = new Bitmap(String("./resources/levelmap.png"));
	m_BmpShadyGuyPtr = new Bitmap(String("./resources/enemy_shadyguy.png"));
	m_BmpSkelethonPtr = new Bitmap(String("./resources/enemy_skelethon.png"));
	m_BmpCthulhuPtr = new Bitmap(String("./resources/enemy_cthulhu.png"));

	m_CameraPtr = new Camera(m_BmpLvlPtr->GetWidth(), m_BmpLvlPtr->GetHeight());

	InitGame();

	m_Session->Start(m_ElfPtr->GetHealth(), m_ElfPtr->GetAmmo());

	//temp:
	DOUBLE2 elfSpawn = m_ElfPtr->GetPosition();

	m_LampArr.push_back(new Lamp(DOUBLE2(elfSpawn.x, elfSpawn.y-100)));

	m_HudArr.push_back(new HUD(HUD::Type::HEALTH, this));
	m_HudArr.push_back(new HUD(HUD::Type::COINS, this));
	m_HudArr.push_back(new HUD(HUD::Type::AMMO, this));
	
	m_ActLevelPtr = new PhysicsActor(DOUBLE2(5, 7), 0, BodyType::STATIC);
	m_ActLevelPtr->AddSVGShape(String("./resources/LevelSVG.svg"), 0, 0.2, 0);
	
	matTranslate.SetAsTranslate(m_Translate);
	matRotate.SetAsRotate(m_Angle);
	matScale.SetAsScale(m_Scale);
	matWorldTransform = matRotate*matScale*matTranslate;
}

void Roguelight::GameEnd()
{

	m_Session->Stop(m_ElfPtr->GetHealth(), m_ElfPtr->GetCoins(), m_ElfPtr->GetAmmo());

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
	delete m_BmpCthulhuPtr;
	m_BmpCthulhuPtr = nullptr;
	delete m_PauseScrPtr;
	m_PauseScrPtr = nullptr;
	delete m_StartScrPtr;
	m_StartScrPtr = nullptr;
	delete m_CameraPtr;
	m_CameraPtr = nullptr;
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

	for (size_t i = 0; i < m_AmmoArr.size(); i++)
	{
		delete m_AmmoArr[i];
		m_AmmoArr[i] = nullptr;
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

	for (size_t i = 0; i < m_BulletArr.size(); i++)
	{
		delete m_BulletArr[i];
		m_BulletArr[i] = nullptr;
	}

	for (size_t i = 0; i < m_LootArr.size(); i++)
	{
		delete m_LootArr[i];
		m_LootArr[i] = nullptr;
	}
	for (size_t i = 0; i < m_LampArr.size(); i++)
	{
		delete m_LampArr[i];
		m_LampArr[i] = nullptr;
	}
	
	delete m_CthulhuPtr;
	m_CthulhuPtr = nullptr;
	m_LootArr.clear();
	m_LampArr.clear();
	m_HudArr.clear();
	m_SkelethonArr.clear();
	m_ShadyguyArr.clear();
	m_MossArr.clear();
	m_SpikeArr.clear();
	m_AmmoArr.clear();
	m_HeartArr.clear();
	delete m_Session;
	m_Session = nullptr;
}


void Roguelight::GameTick(double deltaTime)
{
	if (m_StartScrPtr != nullptr)
	{
		m_StartScrPtr->Tick(deltaTime);
		return;
	}
	if (m_PauseScrPtr->IsActive())
	{
		m_PauseScrPtr->Tick(deltaTime);
		return;
	}

	m_ElfPtr->Tick(deltaTime);
	m_ElfPos = m_ElfPtr->GetPosition();

	m_CameraPtr->Tick(deltaTime, m_ElfPos);

	m_CthulhuPtr->Tick(deltaTime);


	m_ShootTime += deltaTime;

	if (GAME_ENGINE->IsKeyboardKeyPressed(VK_ESCAPE))
	{
		m_PauseScrPtr->SetActive(true);
		return;
	}
	if (GAME_ENGINE->IsKeyboardKeyPressed('P'))
	{
		m_IsPhysicsDebudRendering = !m_IsPhysicsDebudRendering;
		GAME_ENGINE->EnablePhysicsDebugRendering(m_IsPhysicsDebudRendering);
	}
	
	if (GAME_ENGINE->IsKeyboardKeyPressed('R'))
	{
		ResetPos();
	}

	if (GAME_ENGINE->IsKeyboardKeyPressed('X'))
	{
		m_ShootTime = 0;	
	}

	if (GAME_ENGINE->IsKeyboardKeyReleased('X'))
	{
		OutputDebugString(String(m_ShootTime) + String('\n'));
		DOUBLE2 bulletSpeed = DOUBLE2(350,0);
		if (m_ShootTime > 0.2)
		{
			bulletSpeed.y = m_ShootTime * -1500;
		}
		int direction = m_ElfPtr->GetDirection();
		bulletSpeed.x *= direction;
		DOUBLE2 bulletPos = m_ElfPos;
		bulletPos.x += 10 * direction; //paddding
		Bullet * bullet = new Bullet(bulletPos, bulletSpeed);

		for (size_t i = 0; i < m_BulletArr.size(); i++)
		{
			if (m_BulletArr[i] == nullptr)
			{
				m_BulletArr[i] = bullet;
				bullet = nullptr;
			}
		}
		if (bullet != nullptr) //not added above
		{
			m_BulletArr.push_back(bullet);
		}
	}
	

	for (size_t i = 0; i < m_AmmoArr.size(); i++)
	{

		if (!m_AmmoArr[i]->IsConsumed())
		{
			m_AmmoArr[i]->Tick(deltaTime);
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
		Enemy * enemy = m_ShadyguyArr[i];
		if (enemy->IsAlive())
		{
			enemy->Tick(deltaTime);
		}
	}

	for (size_t i = 0; i < m_SkelethonArr.size(); i++)
	{
		Enemy * enemy = m_SkelethonArr[i];
		if (enemy->IsAlive())
		{
			enemy->Tick(deltaTime);
		}
	}

	for (size_t i = 0; i < m_LootArr.size(); i++)
	{

		if (m_LootArr[i] != nullptr)
		{
			m_LootArr[i]->Tick(deltaTime);
			if (m_LootArr[i]->IsConsumed())
			{
				delete m_LootArr[i];
				m_LootArr[i] = nullptr;
			}
		}
	}
	for (size_t i = 0; i < m_BulletArr.size(); i++)
	{
		if (m_BulletArr[i] != nullptr)
		{
			m_BulletArr[i]->Tick(deltaTime);
			if (!m_BulletArr[i]->IsFlying())
			{
				delete m_BulletArr[i];
				m_BulletArr[i] = nullptr;
			}
		}
	}
}

void Roguelight::GamePaint(RECT rect)
{
	if (m_StartScrPtr != nullptr)
	{
		m_StartScrPtr->Paint();
		return;
	}
	
	if (m_PauseScrPtr->IsActive())
	{
		m_PauseScrPtr->Paint();	
		return;
	} 
	
	matTranslate.SetAsTranslate(m_Translate);
	matRotate.SetAsRotate(0);
	matRotate.SetAsScale(1);
	matWorldTransform = matRotate * matScale * matTranslate;

	GAME_ENGINE->DrawBitmap(m_BmpLvlPtr);

	m_ElfPtr->Paint();
	m_CthulhuPtr->Paint();

	for (size_t i = 0; i < m_MossArr.size(); i++)
	{
		m_MossArr[i]->Paint();
	}

	for (size_t i = 0; i < m_SpikeArr.size(); i++)
	{
		m_SpikeArr[i]->Paint();
	}

	for (size_t i = 0; i < m_AmmoArr.size(); i++)
	{
		if (!m_AmmoArr[i]->IsConsumed())
		{
			m_AmmoArr[i]->Paint();
		}
	}


	for (size_t i = 0; i < m_HeartArr.size(); i++)
	{
		if (!m_HeartArr[i]->IsConsumed())
		{
			m_HeartArr[i]->Paint();
		}
	}
	for (size_t i = 0; i < m_LootArr.size(); i++)
	{
		if (m_LootArr[i] != nullptr && !m_LootArr[i]->IsConsumed())
		{
			m_LootArr[i]->Paint();
		};
	}
	for (size_t i = 0; i < m_ShadyguyArr.size(); i++)
	{
		Enemy * enemy = m_ShadyguyArr[i];
		if (enemy->IsAlive())
			enemy->Paint();
	}
	for (size_t i = 0; i < m_SkelethonArr.size(); i++)
	{
		Enemy * enemy = m_SkelethonArr[i];
		if (enemy->IsAlive())
			enemy->Paint();
	}
	for (size_t i = 0; i < m_HudArr.size(); i++)
	{
		m_HudArr[i]->Paint();
	}

	for (size_t i = 0; i < m_LampArr.size(); i++)
	{
		m_LampArr[i]->Paint();
	}

	for (size_t i = 0; i < m_BulletArr.size(); i++)
	{
		if (m_BulletArr[i] != nullptr && m_BulletArr[i]->IsFlying())
		{
			m_BulletArr[i]->Paint();
		}
	}
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
	else if (item.find(L"Ammo") == 1)
	{
		ParseAmmo(Collectible::AMMO, item, m_AmmoArr);
	}
	else if (item.find(L"Skelethon") == 1)
	{
		ParseSkelethon(item);
	}
	else if ((item.find(L"Lamp") == 1))
	{
		ParseLamp(item);
	}
	else if ((item.find(L"Elf") == 1))
	{
		ParseElf(item);
	}
	else if ((item.find(L"Cthulhu") == 1))
	{
		ParseCthulhu(item);
	}
}

void Roguelight::ParseElf(std::wstring & item)
{
	DOUBLE2 pos = ParsePosition(item);
	m_ElfPtr = new Elf(pos);
}

void Roguelight::ParseLamp(std::wstring & item)
{
	DOUBLE2 pos = ParsePosition(item);
	m_LampArr.push_back(new Lamp(pos));
}

void Roguelight::ParseMoss(std::wstring & item)
{
	DOUBLE2 pos = ParsePosition(item);
	pos.x += 5;
	pos.y += 35;
	m_MossArr.push_back(new Moss(pos));
}

void Roguelight::ParseSpike(std::wstring & item)
{
	DOUBLE2 pos = ParsePosition(item);
	pos.x += 5;
	pos.y += 20;
	m_SpikeArr.push_back(new Spike(pos));
}

void Roguelight::ParseHeart(Collectible::Type type, std::wstring & item, std::vector<Collectible *> & arrayPtr)
{
	DOUBLE2 pos = ParsePosition(item);
	arrayPtr.push_back(new Collectible(pos, type));

}

void Roguelight::ParseAmmo(Collectible::Type type, std::wstring & item, std::vector<Collectible *> & arrayPtr)
{
	DOUBLE2 pos = ParsePosition(item);
	arrayPtr.push_back(new Collectible(pos, type));

}

void Roguelight::ParseCthulhu(std::wstring & item)
{
	DOUBLE2 pos = ParsePosition(item);
	m_CthulhuPtr = new Cthulhu(pos, 2, m_BmpCthulhuPtr);
}

void Roguelight::ParseShadyguy(std::wstring & item)
{
	DOUBLE2 pos = ParsePosition(item);
	m_ShadyguyArr.push_back(new Shadyguy(pos, m_BmpShadyGuyPtr));
}

void Roguelight::ParseSkelethon(std::wstring & item)
{
	DOUBLE2 pos = ParsePosition(item);
	m_SkelethonArr.push_back(new Skelethon(pos, 3, m_BmpSkelethonPtr));
}

PhysicsActor * Roguelight::GetLevelActor()
{
	return m_ActLevelPtr;
}



void Roguelight::CheckHitEnemy(PhysicsActor * actor)
{
	if (IsEnemiyHit(m_SkelethonArr, actor))
	{
		return;
	}
	if (IsEnemiyHit(m_ShadyguyArr, actor))
	{
		return;
	}

	for (size_t i = 0; i < m_LampArr.size(); i++) 
	{
		if (m_LampArr[i]->CheckHit(actor)) 
		{
			DOUBLE2 pos = m_LampArr[i]->GetPosition();
			pos.y += 30;
			NewCoin(pos);
			return; 
		}
	}

}

bool Roguelight::IsEnemiyHit(std::vector<Enemy *> & enemies, PhysicsActor * actor)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->GetPhysicsActor() == actor)
		{
			Enemy * enemy = enemies[i];
			enemies[i]->DecreaseHealth();
			if (!enemy->IsAlive())
			{
				DOUBLE2 pos = enemies[i]->GetPosition();
				NewCoin(pos);
			}
			return true;
		}
	}

	return false;
}


void Roguelight::NewCoin(DOUBLE2 pos)
{

	Collectible * coin = new Collectible(pos, Collectible::COINS);

	for (size_t i = 0; i < m_LootArr.size(); i++)
	{
		if (m_LootArr[i] == nullptr)
		{
			m_LootArr[i] = coin;
			coin = nullptr;
		}
	}
	if (coin != nullptr) //not added above
	{
		m_LootArr.push_back(coin);
	}

}


void Roguelight::Start()
{
	delete m_StartScrPtr;
	m_StartScrPtr = nullptr;
}

void Roguelight::ResetPos()
{
	m_ElfPtr->ResetPosition();
	
	for (size_t i = 0; i < m_MossArr.size(); i++)
	{
		m_MossArr[i]->ResetPos();
	}
	for (size_t i = 0; i < m_SpikeArr.size(); i++)
	{
		m_SpikeArr[i]->ResetPos();
	}
	for (size_t i = 0; i < m_AmmoArr.size(); i++)
	{
		m_AmmoArr[i]->ResetPos();
	}
	for (size_t i = 0; i < m_HeartArr.size(); i++)
	{
		m_HeartArr[i]->ResetPos();
	}
	for (size_t i = 0; i < m_ShadyguyArr.size(); i++)
	{
		m_ShadyguyArr[i]->Reset();
	}
	for (size_t i = 0; i < m_SkelethonArr.size(); i++)
	{
		m_SkelethonArr[i]->Reset();
	}
	//for (size_t i = 0; i < m_LampArr.size(); i++)
	//{
	//	m_LampArr[i]->Reset;
	//}

}


Camera * Roguelight::GetCamera()
{
	return m_CameraPtr;
}