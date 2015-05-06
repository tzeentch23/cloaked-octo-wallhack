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
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())
//---------------------------
// Constructor & Destructor
//---------------------------
HUD::HUD(Type type, Roguelight * game)
{
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
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
//void HUD::BeginContact(PhHUDsicsActor *actThisPtr, PhHUDsicsActor *actOtherPtr)
//{
//
//}
//
//void HUD::EndContact(PhHUDsicsActor *actThisPtr, PhHUDsicsActor *actOtherPtr)
//{
//
//}
//
//void HUD::ContactImpulse(PhHUDsicsActor *actThisPtr, double impulse)
//{
//
//}

void HUD::Paint()
{
	Elf * elf = Elf::GetPlayer();
	DOUBLE2 elfPos = elf->GetPosition();
	int health = elf->GetHealth();
	int ammo = elf->GetAmmo();
	int coins = elf->GetCoins();

	//DOUBLE2 bitmapPos = m_Position;
	/*DOUBLE2 originChange(elfPos.x - 400,
		elfPos.y - 300);
		*/

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
	DOUBLE2 originTranslate = DOUBLE2(m_Game->GetCameraOrigin().x - GAME_ENGINE->GetWidth() / 2,
		m_Game->GetCameraOrigin().y - GAME_ENGINE->GetHeight() / 2);
	matTranslate.SetAsTranslate(originTranslate);
	matRotate.SetAsRotate(m_Angle);
	matScale.SetAsScale(m_Scale);
	matWorldTransform = matRotate*matScale*matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);
	GAME_ENGINE->SetBitmapInterpolationModeNearestNeighbor();
	GAME_ENGINE->DrawBitmap(bmp, finalPos);

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

