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
#include "Skelethon.h"
#include "Shadyguy.h"
#include "Elf.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Enemy::Enemy(DOUBLE2 spawnPos, int frameRate, int nrCols, int nrRows, Bitmap * bmpPtr)
:Actor(spawnPos, frameRate, nrCols, nrRows, bmpPtr->GetWidth() / nrCols , bmpPtr->GetHeight() / nrRows )
{
	m_BmpActorPtr = bmpPtr;
}

Enemy::~Enemy() 
{
	delete m_ActActorPtr;
	m_ActActorPtr = nullptr;
}

void Enemy::Paint() {
	Actor::Paint();
}

void Enemy::Tick(double deltatime)
{	
	Actor::Tick(deltatime);
}
//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------

void Enemy::BeginContact(PhysicsActor *actthisptr, PhysicsActor *actotherptr)
{
	Elf * elf = Elf::GetPlayer();
	
	if (actotherptr == elf->GetPhysicsActor())
	{
		elf->DecreaseHealth();
	}
}

void Enemy::EndContact(PhysicsActor *actthisptr, PhysicsActor *actotherptr)
{
}
