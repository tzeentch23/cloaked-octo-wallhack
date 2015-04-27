//-----------------------------------------------------
// Name: Kirkorova 
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "Collectibles.h"
#include "Elf.h"
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Collectibles::Collectibles()
{
	// nothing to create
	// m_ActCirclePtr->AddContactListener(this);
}

Collectibles::~Collectibles()
{
	// nothing to destroCollectibles
}

void Collectibles::Tick()
{
	
}
void Collectibles::Paint()
{


}
//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Collectibles::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	//tuka pochnah  neshto ama ne moga da se dokopam do metodite na elfa 
	Elf * elf = Elf::getPlayer();
	if (actThisPtr->IsOverlapping(actOtherPtr))
	{
		if (m_Type == Type::COINS)
		{
			elf->IncreaseMoney();
		}
		if (m_Type == Type::ARROWS)
		{

		}
		if (m_Type == Type::HEARTS)
		{

		}
	}
}

void Collectibles::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Collectibles::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}


