//-----------------------------------------------------
// Name:
// First name:
// Group: 1DAE.
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "Spikes.h"

//---------------------------
// Defines
//---------------------------
//#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Spikes::Spikes()
{
	// nothing to create
	// m_ActCirclePtr->AddContactListener(this);
}

Spikes::~Spikes()
{
	// nothing to destroSpikes
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Spikes::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Spikes::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Spikes::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}


