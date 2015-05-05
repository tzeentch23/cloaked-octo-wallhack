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

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
HUD::HUD(DOUBLE2 pos, Type type)
{
	m_ActHUDPtr = new PhysicsActor(pos, 0, BodyType::STATIC);
	m_ActHUDPtr->AddBoxShape(HUD_WIDTH, HUD_HEIGHT, 0.0, 0.2, 0.2);
	m_ActHUDPtr->SetFixedRotation(true);
	m_ActHUDPtr->SetGravityScale(1);
		
	if (m_Type == Type::HEALTH)
	{
		m_BmpHUDPtr = new Bitmap(String(""));
	}
	if (m_Type == Type::AMMO)
	{
		m_BmpHUDPtr = new Bitmap(String(""));
	}
	if (m_Type == Type::COINS)
	{
		m_BmpHUDPtr = new Bitmap(String(""));
	}
}

HUD::~HUD()
{
	// nothing to destroHUD
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
	DOUBLE2 bitmapPos(m_ActHUDPtr->GetPosition().x - (m_BmpHUDPtr->GetWidth() / 2),
		m_ActHUDPtr->GetPosition().y - (m_BmpHUDPtr->GetHeight() / 2));

	matTranslate.SetAsTranslate(bitmapPos);
	matRotate.SetAsRotate(m_Angle);
	matRotate.SetAsScale(m_Scale);
	matWorldTransform = matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);
	GAME_ENGINE->SetBitmapInterpolationModeNearestNeighbor();
	GAME_ENGINE->DrawBitmap(m_BmpHUDPtr);

}

void HUD::Tick(double deltaTime)
{
	int ammo = Elf::GetAmmo();
	String health = String(Elf::m_Health());
	int coins = Elf::GetCoins();

	//temp
	DOUBLE2 position = m_ActHUDPtr->GetPosition();
	if (m_Type == Type::HEALTH)
	{
		GAME_ENGINE->DrawString(String("\tHealth: ") + String(Elf::m_Health), position);
	}
	
	if (m_Type == Type::AMMO)
	{
		GAME_ENGINE->DrawString(String("\nAmmo: ") + String(ammo), position);
	}

	if (m_Type == Type::COINS)
	{
		GAME_ENGINE->DrawString(String("\nCoins: ") + String(ammo), position);
	}

}