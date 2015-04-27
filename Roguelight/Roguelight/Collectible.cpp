//-----------------------------------------------------
// Name: Kirkorova 
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "Collectible.h"
#include "Elf.h"
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * Collectible::m_BmpCoinPtr = nullptr;
Bitmap * Collectible::m_BmpArrowPtr = nullptr;
Bitmap * Collectible::m_BmpHeartPtr = nullptr;
Collectible::Collectible(DOUBLE2 pos, Type type)
{
	m_ActCollectPtr = new PhysicsActor(pos, 0, BodyType::DYNAMIC);
	if ( type == Type::HEARTS)
	{
		//m_BmpHeartPtr = new Bitmap(String("./resources/hearts.png"));
	}
	else if (type == Type::ARROWS)
	{
	//	m_BmpArrowPtr = new Bitmap(String("./resources/arrow.png"));
	}
	else if (type == Type::COINS)
	{
	//	m_BmpCoinPtr = new Bitmap(String)
	}
}

Collectible::~Collectible()
{
	// nothing to destroCollectible
}

void Collectible::Tick()
{
	
}
void Collectible::Paint()
{


}
//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Collectible::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	Elf * elf = Elf::getPlayer();
	
		if (m_Type == Type::COINS)
		{
			elf->IncreaseMoney();
		}
		if (m_Type == Type::ARROWS)
		{
			elf->IncreaseAmmo();
		}
		if (m_Type == Type::HEARTS)
		{
			elf->IncreaseHealth();
		}
	
}

void Collectible::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Collectible::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}


