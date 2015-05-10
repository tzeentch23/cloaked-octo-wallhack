//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		

//---------------------------
// Includes
//---------------------------
#include "Shadyguy.h"
#include "Enemy.h"
#include "Roguelight.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

const DOUBLE2 Shadyguy::IMPULSE = DOUBLE2(60, 0);
//---------------------------
// Constructor & Destructor
//---------------------------
Shadyguy::Shadyguy(DOUBLE2 pos, Bitmap * bmpPtr) : Enemy(pos, 5, 3, 1, 20, 40, bmpPtr)
{
	m_ActActorPtr->ApplyLinearImpulse(IMPULSE);
	m_Health = GetInitialHealth();
}

Shadyguy::~Shadyguy()
{
	delete m_ActActorPtr;
	m_ActActorPtr = nullptr;
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Shadyguy::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

	if (actThisPtr->GetContactList().size() > 2)
	{
		m_Direction *= -1;
	}
	Enemy::BeginContact(actThisPtr, actOtherPtr);
}
//
//void Shadyguy::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
//{
//
//}
//
//void Shadyguy::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
//{
//
//}

void Shadyguy::Tick(double deltaTime)
{
	DOUBLE2 impulse;
	DOUBLE2 newPos = m_ActActorPtr->GetPosition();
	DOUBLE2 targetVelocity = DOUBLE2(100, 0);
	double mass = m_ActActorPtr->GetMass();

	impulse.x = IMPULSE.x * m_Direction;
	impulse.y = IMPULSE.y;
	m_ActActorPtr->SetLinearVelocity(impulse);
	Enemy::Tick(deltaTime);

}

int Shadyguy::GetInitialHealth()
{
	return 3;
}