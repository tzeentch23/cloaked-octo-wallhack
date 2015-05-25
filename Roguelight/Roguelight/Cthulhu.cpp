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
	if (actThisPtr->GetContactList().size() > 1)
	{
		m_Direction *= -1;
	}
	Enemy::BeginContact(actThisPtr, actOtherPtr);
}

//void Cthulhu::Tick(double deltaTime)
//{
//	Elf * elf = Elf::GetPlayer();
//	DOUBLE2 elfPos = elf->GetPosition();
//	DOUBLE2 impulse;
//	DOUBLE2 newPos = m_ActActorPtr->GetPosition();
//	DOUBLE2 targetVelocity = DOUBLE2(1000, 1000);
//	double mass = m_ActActorPtr->GetMass();
//
//	impulse.x = IMPULSE.x * m_Direction;
//	impulse.y = IMPULSE.y * m_Direction;
//	m_ActActorPtr->SetLinearVelocity(impulse);
//	Enemy::Tick(deltaTime);
//
//	DOUBLE2 CthulhuPos = m_ActActorPtr->GetPosition();
//	double distance = DOUBLE2(CthulhuPos - elfPos).Length();
//
//	if (distance < MAX_DISTANCE)
//	{
//		DOUBLE2 dir = DOUBLE2(elfPos.x - CthulhuPos.x, elfPos.y - CthulhuPos.y);
//		m_ActActorPtr->ApplyForce(dir);
//	}
//}

int Cthulhu::GetInitialHealth()
{
	return 4;
}