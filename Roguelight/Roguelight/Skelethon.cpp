//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "Skelethon.h"
#include "Elf.h"
#include "Enemy.h"
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
const DOUBLE2 Skelethon::IMPULSE = DOUBLE2(100, 100);
const int Skelethon::MAX_DISTANCE = 300;

Skelethon::Skelethon(DOUBLE2 pos, int cols, Bitmap * bmpPtr) : Enemy(pos, 5, cols, 1, bmpPtr)
{
	//m_ActActorPtr->ApplyLinearImpulse(IMPULSE);
	m_Health = GetInitialHealth();
	m_ActActorPtr->SetGravityScale(0);
}

Skelethon::~Skelethon()
{
	delete m_ActActorPtr;
	m_ActActorPtr = nullptr;
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Skelethon::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	if (actThisPtr->GetContactList().size() > 1)
	{
		m_Direction *= -1;
	}
	Enemy::BeginContact(actThisPtr, actOtherPtr);
}

void Skelethon::Tick(double deltaTime)
{
	m_ImpulseTime += deltaTime;

	if (m_ImpulseTime > 1)
	{
		m_ImpulseTime = 0;
		Elf * elf = Elf::GetPlayer();
		DOUBLE2 elfPos = elf->GetPosition();
		DOUBLE2 impulse;
		DOUBLE2 newPos = m_ActActorPtr->GetPosition();

		//Enemy::Tick(deltaTime);

		DOUBLE2 skelethonPos = m_ActActorPtr->GetPosition();
		double distance = DOUBLE2(skelethonPos - elfPos).Length();

		DOUBLE2 target = m_SpawnPos;
		if (distance < MAX_DISTANCE)
		{
			target = elfPos;
		}

		int dirX = 1;
		if (target.x - skelethonPos.x < 0)
		{
			dirX = -1;
		}

		int dirY = 1;
		if (target.y - skelethonPos.y < 0)
		{
			dirX = -1;
		}
		m_Scale = dirX;


		DOUBLE2 dir = DOUBLE2(dirX * (rand() % 500 + 100), ((rand() % 500 + 100) * dirY));

		//m_ActActorPtr->ApplyLinearImpulse(dir);
	
		m_ActActorPtr->ApplyForce(dir * 100);
	}
}

int Skelethon::GetInitialHealth()
{
	return 4;
}