//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		

//---------------------------
// Includes
//---------------------------
#include "Cthulhu.h"
#include "Elf.h"
#include "Enemy.h"
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Cthulhu::Cthulhu(DOUBLE2 pos, int cols, Bitmap * bmpPtr) : Skelethon(pos, cols, bmpPtr)
{
	m_ActActorPtr->ApplyLinearImpulse(IMPULSE);
	m_Health = GetInitialHealth();
}


Cthulhu::~Cthulhu()
{
	delete m_ActActorPtr;
	m_ActActorPtr = nullptr;
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Cthulhu::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	Skelethon::BeginContact(actThisPtr, actOtherPtr);
}

int Cthulhu::GetInitialHealth()
{
	return 6;
}