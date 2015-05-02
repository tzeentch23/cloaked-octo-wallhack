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
Shadyguy::Shadyguy(DOUBLE2 pos, Bitmap * bmpPtr) : Enemy(pos, bmpPtr)
{
	m_InitialPosition = pos;
	m_ActEnemyPtr->SetLinearVelocity(DOUBLE2(-100, 500)); //neka i toj si pada
	m_ActEnemyPtr->AddBoxShape(10, 10, 0.0, 0.2, 0.2);
	m_ActEnemyPtr->AddContactListener(this);
}
//vidq li gi :D:D:D:DD::) maj da.. ok, dvijenieto moje bi ne sy go ucelil
Shadyguy::~Shadyguy()
{
}
//actiora moje da e dinamichen
//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
//void Shadyguy::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
//{
//
//}
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
	//to shto ne se blyska? mi mai nqma contact
		DOUBLE2 newPos = m_ActEnemyPtr->GetPosition();
		DOUBLE2 current = m_ActEnemyPtr->GetLinearVelocity();
		
		if (newPos.x - m_InitialPosition.x >= 100)
		{
			current.x *= -1;
		}
		else if (m_InitialPosition.x - newPos.x >= 100) 
		{
			current.x *= -1;
		}
		
		m_ActEnemyPtr->SetLinearVelocity(current); 
 }

void Shadyguy::Patrol()
{
	
}
