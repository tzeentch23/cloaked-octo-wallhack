//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		

//---------------------------
// Includes
//---------------------------
#include "HUD.h"
#include "Elf.h"
#include "Roguelight.h"
#include "Camera.h"
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())
//---------------------------
// Constructor & Destructor
//---------------------------
int HUD::m_InstanceCount = 0;
Bitmap * HUD::m_Bmp1UpPtr = nullptr;
Bitmap * HUD::m_BmpCoinCountPtr = nullptr;
HUD::HUD(Type type, Roguelight * game)
{
	m_InstanceCount++;
	m_Game = game;
	m_Type = type;
	if (m_Type == Type::HEALTH)
	{
		m_BmpHUDPtr = new Bitmap(String("./resources/HUDHealth.png"));
	}
	else if (m_Type == Type::AMMO)
	{
		m_BmpHUDPtr = new Bitmap(String("./resources/HUDAmmo.png"));
	}
	else if (m_Type == Type::COINS)
	{
		m_BmpHUDPtr = new Bitmap(String("./resources/HUDCoins.png"));
	}

	if (m_Bmp1UpPtr == nullptr)
	{
		m_Bmp1UpPtr = new Bitmap(String("./resources/1up.png"));
	}

	if (m_BmpCoinCountPtr == nullptr)
	{
		m_BmpCoinCountPtr = new Bitmap(String("./resources/coins_0to9.png"));
	}
	m_HealthPos = DOUBLE2(200, (GAME_ENGINE->GetHeight() / 4) * 3);
	m_CoinsPos = DOUBLE2(GAME_ENGINE->GetWidth() / 2 - m_BmpHUDPtr->GetWidth() / 2,
						(GAME_ENGINE->GetHeight() / 4) * 3);
	m_AmmoPos = DOUBLE2((GAME_ENGINE->GetWidth() - m_BmpHUDPtr->GetWidth() - 200),
						(GAME_ENGINE->GetHeight() / 4) * 3);
}

HUD::~HUD()
{
	delete m_BmpHUDPtr;
	m_BmpHUDPtr = nullptr;

	if (--m_InstanceCount == 0)
	{
		delete m_Bmp1UpPtr;
		m_Bmp1UpPtr = nullptr;
		delete m_BmpCoinCountPtr;
		m_BmpCoinCountPtr = nullptr;
	}
	
}

void HUD::Paint()
{
	Elf * elf = Elf::GetPlayer();
	DOUBLE2 elfPos = elf->GetPosition();
	int health = elf->GetHealth();
	int ammo = elf->GetAmmo();
	int coins = elf->GetCoins();


	DOUBLE2 finalPos;
	switch (m_Type)
	{
	case HUD::Type::HEALTH:
		finalPos.Set(m_HealthPos.x, m_HealthPos.y);
		break;
	case HUD::Type::COINS:
		finalPos.Set(m_CoinsPos.x, m_CoinsPos.y);
		break;
	case HUD::Type::AMMO:
		finalPos.Set(m_AmmoPos.x, m_AmmoPos.y);
		break;
	}

	Bitmap * bmp = m_BmpHUDPtr;

	DOUBLE2 origin = m_Game->GetCamera()->GetCameraOrigin();
	DOUBLE2 originTranslate = DOUBLE2(origin.x - GAME_ENGINE->GetWidth() / 2,
										origin.y - GAME_ENGINE->GetHeight() / 2);
	matTranslate.SetAsTranslate(originTranslate);
	matRotate.SetAsRotate(m_Angle);
	matScale.SetAsScale(m_Scale);
	matWorldTransform = matRotate*matScale*matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);
	GAME_ENGINE->SetBitmapInterpolationModeNearestNeighbor();
	GAME_ENGINE->DrawBitmap(bmp, finalPos);
	
	int w = m_Bmp1UpPtr->GetWidth();
	DOUBLE2 startPos;

	switch (m_Type) 
	{
	case Type::HEALTH:
		startPos = DOUBLE2(m_HealthPos.x + 45, m_HealthPos.y+11);
		for (int i = 0; i < elf->GetHealth(); i++)
		{
			matStartPos.SetAsTranslate(startPos);
			matWorldTransform = matStartPos* matRotate*matScale*matTranslate;
			GAME_ENGINE->SetWorldMatrix(matWorldTransform);
			GAME_ENGINE->DrawBitmap(m_Bmp1UpPtr);
			startPos.x += w + 2;
		}
		break;
	case Type::AMMO:
		startPos = DOUBLE2(m_AmmoPos.x + 10, m_AmmoPos.y + 11);
	
		for (int i = 0; i < elf->GetAmmo(); i++)
		{
			matStartPos.SetAsTranslate(startPos);
			matWorldTransform = matStartPos* matRotate*matScale*matTranslate;
			GAME_ENGINE->SetWorldMatrix(matWorldTransform);
			GAME_ENGINE->DrawBitmap(m_Bmp1UpPtr);
			startPos.x += w + 2;
		}
		break;
	case Type::COINS:
			int coins = elf->GetCoins();
			if (coins > 99)
			{
				coins = 99;
			}
			int first = coins / 10;
			int second = coins % 10;
			DOUBLE2 startPos = DOUBLE2(m_CoinsPos.x + 25, m_CoinsPos.y + 10);
			matStartPos.SetAsTranslate(startPos);
			matWorldTransform = matStartPos* matRotate*matScale*matTranslate;
			GAME_ENGINE->SetWorldMatrix(matWorldTransform);
			
			RECT coin;
			coin.top = 0;
			coin.bottom = m_BmpCoinCountPtr->GetHeight();
			int w = m_BmpCoinCountPtr->GetWidth() / 10;
			coin.left = w * first;
			coin.right = coin.left + w;
			GAME_ENGINE->DrawBitmap(m_BmpCoinCountPtr, coin);
			startPos.x += w + 5;

			matStartPos.SetAsTranslate(startPos);
			matWorldTransform = matStartPos* matRotate*matScale*matTranslate;
			GAME_ENGINE->SetWorldMatrix(matWorldTransform);

			coin.left = w * second;
			coin.right = coin.left + w;
			GAME_ENGINE->DrawBitmap(m_BmpCoinCountPtr, coin);

	}
	

	if (m_Type == Type::HEALTH)
	{
		GAME_ENGINE->DrawString(String("Health: ") + String(health), DOUBLE2(finalPos.x + 60, finalPos.y + 40));
	}

	if (m_Type == Type::AMMO)
	{
		GAME_ENGINE->DrawString(String("Ammo: ") + String(ammo), DOUBLE2(finalPos.x + 60, finalPos.y + 40));
	}

	if (m_Type == Type::COINS)
	{
		GAME_ENGINE->DrawString(String("Coins: ") + String(coins), DOUBLE2(finalPos.x + 60, finalPos.y + 40));
	}

}

