//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "Skelethon.h"
#include "Elf.h"
#include "Enemy.h"
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
const DOUBLE2 Skelethon::IMPULSE = DOUBLE2(100, 100);
Skelethon::Skelethon(DOUBLE2 pos, Bitmap * bmpPtr) : Enemy(pos, 5, 3, 1, 30, 50, bmpPtr)
{
	m_ActActorPtr->ApplyLinearImpulse(IMPULSE);
	m_Health = GetInitialHealth();
}

Skelethon::~Skelethon()
{
	delete m_ActActorPtr;
	m_ActActorPtr = nullptr;
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Skelethon::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	if (actThisPtr->GetContactList().size() > 1)
	{
		m_Direction *= -1;
	}
	Enemy::BeginContact(actThisPtr, actOtherPtr);
}

//void Skelethon::EndContact(PhSkelethonsicsActor *actThisPtr, PhSkelethonsicsActor *actOtherPtr)
//{
//
//}
//
//void Skelethon::ContactImpulse(PhSkelethonsicsActor *actThisPtr, double impulse)
//{
//
//}
//
//void Shadyguy::Tick(double deltaTime)
//{
//
//}

void Skelethon::Tick(double deltaTime)
{
	Elf * elf = Elf::GetPlayer();
	DOUBLE2 elfPos = elf->GetPosition();
	DOUBLE2 impulse;
	DOUBLE2 newPos = m_ActActorPtr->GetPosition();
	DOUBLE2 targetVelocity = DOUBLE2(1000, 1000);
	double mass = m_ActActorPtr->GetMass();

	impulse.x = IMPULSE.x * m_Direction;
	impulse.y = IMPULSE.y * m_Direction;
	m_ActActorPtr->SetLinearVelocity(impulse);
	Enemy::Tick(deltaTime);

	DOUBLE2 velocity = m_ActActorPtr->GetLinearVelocity();
	DOUBLE2 enemyPos = m_ActActorPtr->GetPosition();
	double distance = DOUBLE2(enemyPos - elfPos).Length();
	double maxdistance = 300;

	if (distance < maxdistance)
	{
		DOUBLE2 dir = enemyPos - elfPos;
		m_ActActorPtr->ApplyLinearImpulse(dir);
	}
}

int Skelethon::GetInitialHealth()
{
	return 2;
}