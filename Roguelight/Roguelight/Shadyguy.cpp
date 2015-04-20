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
#include "Enemies.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Shadyguy::Shadyguy()
{
}

Shadyguy::~Shadyguy()
{
	delete m_BmpShadyPtr;
	m_BmpShadyPtr = nullptr;
	delete m_ActShadyPtr;
	m_ActShadyPtr = nullptr;
}

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


