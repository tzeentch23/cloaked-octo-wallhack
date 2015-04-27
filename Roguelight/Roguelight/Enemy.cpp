//-----------------------------------------------------
// Name: Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "Enemy.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Enemy::Enemy()
{
	// nothing to create
	// m_ActCirclePtr->AddContactListener(this);
}

Enemy::~Enemy()
{
	// nothing to destroEnemy
}

void Enemy::Paint()
{



}


//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Enemy::BeginContact(PhysicsActor *actthisptr, PhysicsActor *actotherptr)
{
	m_Health -= 25;
}

void Enemy::EndContact(PhysicsActor *actthisptr, PhysicsActor *actotherptr)
{

}

void Enemy::ContactImpulse(PhysicsActor *actthisptr, double impulse)
{

}


