//-----------------------------------------------------
// Name: Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "Enemies.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Enemies::Enemies()
{
	// nothing to create
	// m_ActCirclePtr->AddContactListener(this);
}

Enemies::~Enemies()
{
	// nothing to destroEnemies
}

void Enemies::Paint()
{



}


//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Enemies::BeginContact(PhysicsActor *actthisptr, PhysicsActor *actotherptr)
{
	m_Health -= 25;
}

void Enemies::EndContact(PhysicsActor *actthisptr, PhysicsActor *actotherptr)
{

}

void Enemies::ContactImpulse(PhysicsActor *actthisptr, double impulse)
{

}


