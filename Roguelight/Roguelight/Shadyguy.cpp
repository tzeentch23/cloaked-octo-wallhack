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

const DOUBLE2 Shadyguy::IMPULSE = DOUBLE2(60, 60);
//---------------------------
// Constructor & Destructor
//---------------------------
Shadyguy::Shadyguy(DOUBLE2 pos, Bitmap * bmpPtr) : Enemy(pos, 5, 3, 1, bmpPtr)
{
	m_Position = pos;
	m_ActActorPtr->ApplyLinearImpulse(IMPULSE);
	m_ActActorPtr->SetGravityScale(0.0);
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
	Enemy::BeginContact(actThisPtr, actOtherPtr);
}

void Shadyguy::Tick(double deltaTime)
{
	DOUBLE2 impulse;
	DOUBLE2 newPos = m_ActActorPtr->GetPosition();
	double dif = (newPos - m_Position).Length();

	if (dif >= 50)
	{
		ChangeDirection();
	}

	impulse.x = IMPULSE.x * m_Direction;
	impulse.y = IMPULSE.y;
	m_ActActorPtr->SetLinearVelocity(impulse);

	Enemy::Tick(deltaTime);	
}

int Shadyguy::GetInitialHealth()
{
	return 3;
}