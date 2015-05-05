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

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Shadyguy::Shadyguy(DOUBLE2 pos, Bitmap * bmpPtr) : Enemy(pos, 5, 3, 1, 20, 40, bmpPtr)
{
	//m_InitialPosition = pos;
	m_ActActorPtr->ApplyLinearImpulse(DOUBLE2(3000, 100));
	//m_ActEnemyPtr->AddBoxShape(10, 10, 0.0, 0.2, 0.2);
	//m_ActEnemyPtr->SetFixedhRotation(true);
//	m_ActEnemyPtr->SetGravityScale(1);
//	m_ActEnemyPtr->AddContactListener(this);
}

Shadyguy::~Shadyguy()
{
	delete m_ActActorPtr;
	m_ActActorPtr = nullptr;
//	delete m_BmpActorPtr;
//	m_BmpActorPtr = nullptr;
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Shadyguy::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
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
		DOUBLE2 current = m_ActActorPtr->GetLinearVelocity();
		double mass = m_ActActorPtr->GetMass();
		
		/*
		if (newPos.x - m_SpawnPos.x >= 100)
		{
			current.x *= -1;
		}
		else if (m_SpawnPos.x - newPos.x >= 100) 
		{
			current.x *= -1;
		}
		desired velocity to impulse
		*/
		//current *= direction;
		impulse = mass * current / PhysicsActor::SCALE;
		//m_ActActorPtr->ApplyForce(impulse); 
		m_ActActorPtr->SetLinearVelocity(impulse);
		Enemy::Tick(deltaTime);

}

void Shadyguy::Patrol()
{
	
}
