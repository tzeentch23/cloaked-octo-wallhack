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
#include "Door.h"
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
Bitmap* Roguelight::m_BmpDeadTextPtr = nullptr;
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
	m_BmpLvlDarkPtr = new Bitmap(String("./resources/levelmapb.png"));
	m_BmpLvlPtr = new Bitmap(String("./resources/levelmap.png"));
	m_BmpLvlPtr->SetTransparencyColor(COLOR(35, 29, 63));
	m_GameSoundPtr = new Sound(String("./resources/game_song.mp3"));
	m_GameSoundPtr->SetVolume(0.2);
	m_BmpShadyGuyPtr = new Bitmap(String("./resources/enemy_shadyguy.png"));
	m_BmpSkelethonPtr = new Bitmap(String("./resources/enemy_skelethon.png"));
	m_BmpCthulhuPtr = new Bitmap(String("./resources/enemy_cthulhu.png"));
	m_BmpDeadTextPtr = new Bitmap(String("./resources/deadText.png"));

	m_CameraPtr = new Camera(m_BmpLvlPtr->GetWidth(), m_BmpLvlPtr->GetHeight());

	InitGame();

	m_Session->Start(m_ElfPtr->GetHealth(), m_ElfPtr->GetAmmo());

	//temp:
	/*DOUBLE2 elfSpawn = m_ElfPtr->GetPosition();
	m_DoorArr.push_back(new Door(DOUBLE2(elfSpawn.x - 100, elfSpawn.y)));
	m_LampArr.push_back(new Lamp(DOUBLE2(elfSpawn.x, elfSpawn.y-100)));
*/

	m_HudArr.push_back(new HUD(HUD::Type::HEALTH, this));
	m_HudArr.push_back(new HUD(HUD::Type::COINS, this));
	m_HudArr.push_back(new HUD(HUD::Type::AMMO, this));
	
	m_ActLevelPtr = new PhysicsActor(DOUBLE2(-12, 7), 0, BodyType::STATIC);
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
	delete m_BmpLvlDarkPtr;
	m_BmpLvlDarkPtr = nullptr;
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
	delete m_BmpDeadTextPtr;
	m_BmpDeadTextPtr = nullptr;
	delete m_GameSoundPtr;
	m_GameSoundPtr = nullptr; 
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
	for (size_t i = 0; i < m_DoorArr.size(); i++)
	{
		delete m_DoorArr[i];
		m_DoorArr[i] = nullptr;
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
	m_DoorArr.clear();
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

//	m_GameSoundPtr->Play();
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
		switch (m_DrawMode)
		{
		case DrawMode::BITMAP:
			m_DrawMode = DrawMode::PHYSICS;
			break;
		case DrawMode::PHYSICS:
			m_DrawMode = DrawMode::ALL;
			break;

		case DrawMode::ALL:
			m_DrawMode = DrawMode::BITMAP;
			break;		
		}

		if (m_DrawMode != DrawMode::BITMAP)
		{
			GAME_ENGINE->EnablePhysicsDebugRendering(true);
		}
		else
		{
			GAME_ENGINE->EnablePhysicsDebugRendering(false);
		}
	}
	
	if (GAME_ENGINE->IsKeyboardKeyPressed('R'))
	{
		Reset();
	}

	if (GAME_ENGINE->IsKeyboardKeyPressed('X'))
	{
		m_ShootTime = 0;	
	}
	if (GAME_ENGINE->IsKeyboardKeyReleased('X'))
	{	
		if (m_ElfPtr->GetAmmo()>0)
		{
			DOUBLE2 bulletSpeed = DOUBLE2(350, 0);
			if (m_ShootTime > 0.2)
			{
				bulletSpeed.y = m_ShootTime * -1500;
			}
			int direction = m_ElfPtr->GetDirection();
			bulletSpeed.x *= direction;
			DOUBLE2 bulletPos = m_ElfPos;
			bulletPos.x += 10 * direction; //paddding
			Bullet * bullet = new Bullet(bulletPos, bulletSpeed);
			m_ElfPtr->DecreaseAmmo();

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

	for (size_t i = 0; i < m_DoorArr.size(); i++)
	{
		m_DoorArr[i]->Tick(deltaTime);
	}

	fixElfPos();
}

void Roguelight::GamePaint(RECT rect)
{
	if (m_DrawMode == DrawMode::PHYSICS)
	{
		return;
	}
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

	GAME_ENGINE->DrawBitmap(m_BmpLvlDarkPtr);
	DrawBgRect(m_ElfPos, 100);

	for (size_t i = 0; i < m_LampArr.size(); i++)
	{
		if (m_LampArr[i]->IsOn())
		{
			DrawBgRect(m_LampArr[i]->GetPosition(), 100);
		}
		m_LampArr[i]->Paint();
	}
	m_CthulhuPtr->Paint();

	for (size_t i = 0; i < m_MossArr.size(); i++)
	{
		m_MossArr[i]->Paint();
	}

	for (size_t i = 0; i < m_SpikeArr.size(); i++)
	{
		m_SpikeArr[i]->Paint();
	}

	for (size_t i = 0; i < m_DoorArr.size(); i++)
	{
		m_DoorArr[i]->Paint();
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

	for (size_t i = 0; i < m_BulletArr.size(); i++)
	{
		if (m_BulletArr[i] != nullptr && m_BulletArr[i]->IsFlying())
		{
			m_BulletArr[i]->Paint();
		}
	}

	m_ElfPtr->Paint();

	if (!m_ElfPtr->IsAlive())
	{
		MATRIX3X2 camOrigin, textTranslate, textScale, textWorldTransfrom, matPivot;

		DOUBLE2 bannerPos = DOUBLE2(GAME_ENGINE->GetWidth() / 2 - m_BmpDeadTextPtr->GetWidth() / 2,
			GAME_ENGINE->GetHeight() / 2 - m_BmpDeadTextPtr->GetHeight() / 2);
		DOUBLE2 origin = GetCamera()->GetCameraOrigin();
		DOUBLE2 originChange = DOUBLE2(origin.x - GAME_ENGINE->GetWidth() / 2,
			origin.y - GAME_ENGINE->GetHeight() / 2);
		matTranslate.SetAsTranslate(originChange);
		matScale.SetAsScale(1);
		matPivot.SetAsTranslate(bannerPos);
		matWorldTransform = matPivot * matRotate * matScale * matTranslate;
		GAME_ENGINE->SetWorldMatrix(matWorldTransform);
		GAME_ENGINE->DrawBitmap(m_BmpDeadTextPtr);
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
	else if ((item.find(L"Door") == 1))
	{
		ParseDoor(item);
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

void Roguelight::ParseDoor(std::wstring & item)
{
	DOUBLE2 pos = ParsePosition(item);
	m_DoorArr.push_back(new Door(pos));
}

PhysicsActor * Roguelight::GetLevelActor()
{
	return m_ActLevelPtr;
}



void Roguelight::CheckHitEnemy(PhysicsActor * actor)
{
	if (IsEnemyHit(m_SkelethonArr, actor))
	{
		return;
	}
	if (IsEnemyHit(m_ShadyguyArr, actor))
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


void Roguelight::fixElfPos()
{
	int border = 200;
	DOUBLE2 levelPos = m_ActLevelPtr->GetPosition();
	DOUBLE2 pos = m_ElfPos;

	if (pos.y - border < levelPos.y)
	{
		pos.y = levelPos.y  - border;

		m_ElfPtr->GetPhysicsActor()->SetPosition(pos);

		m_ElfPtr->GetPhysicsActor()->SetLinearVelocity(DOUBLE2(0, 100));
	}
	if (pos.y > levelPos.y + m_BmpLvlPtr->GetHeight() - border)
	{
		pos.y = levelPos.y +m_BmpLvlPtr->GetHeight() + border;
		m_ElfPtr->GetPhysicsActor()->SetPosition(pos);

	}


}
bool Roguelight::IsEnemyHit(std::vector<Enemy *> & enemies, PhysicsActor * actor)
{
	for (size_t i = 0; i 
		< enemies.size(); i++)
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


void Roguelight::Reset()
{
	m_ElfPtr->Reset();

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

void Roguelight::Quit()
{
	GAME_ENGINE->QuitGame();
}

void Roguelight::DrawBgRect(DOUBLE2 pos, int r)
{
	m_BgRect.left = pos.x - r;
	m_BgRect.top = pos.y - r;
	m_BgRect.right = pos.x + r;
	m_BgRect.bottom = pos.y + r;

	matTranslate.SetAsTranslate(pos.x - r, pos.y - r);
	matRotate.SetAsRotate(m_Angle);
	matScale.SetAsScale(1);

	matWorldTransform = matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);
	GAME_ENGINE->DrawBitmap(m_BmpLvlPtr, m_BgRect);
}