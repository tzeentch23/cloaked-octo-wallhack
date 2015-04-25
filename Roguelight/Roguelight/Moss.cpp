//-----------------------------------------------------
// Name:
// First name:
// Group: 1DAE.
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "Moss.h"

//---------------------------
// Defines
//---------------------------
//#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Moss::Moss()
{
	m_ActMossPtr = new PhysicsActor(DOUBLE2(399.41, 1725.23), 0, BodyType::STATIC);
	m_ActMossPtr->AddBoxShape(40, 10, 0.2, 0.9, 0.2);
	//m_ActMossPtr->SetGhost();
	// m_ActCirclePtr->AddContactListener(this);
}

Moss::~Moss()
{
	// nothing to destroMoss
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Moss::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Moss::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Moss::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}


