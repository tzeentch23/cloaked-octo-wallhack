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
	m_ActActorPtr->SetGravityScale(0.1);
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
	Elf * elf = Elf::GetPlayer();
	DOUBLE2 elfPos = elf->GetPosition();
	DOUBLE2 impulse;
	DOUBLE2 newPos = m_ActActorPtr->GetPosition();
//	DOUBLE2 targetVelocity = DOUBLE2(1000, 1000);
	double mass = m_ActActorPtr->GetMass();

	Enemy::Tick(deltaTime);

	DOUBLE2 skelethonPos = m_ActActorPtr->GetPosition();
	double distance = DOUBLE2(skelethonPos - elfPos).Length();

	if (distance < MAX_DISTANCE)
	{
	  //DOUBLE2 dir = DOUBLE2((elfPos.x - skelethonPos.x) *10 ,  (elfPos.y - skelethonPos.y) * 10);
		DOUBLE2 dir = DOUBLE2((elfPos.x - skelethonPos.x) * 5, ( rand() % 50 * m_Direction) *  50);
		//OutputDebugString(String("Y " )+ String(dir.y));
		m_ActActorPtr->ApplyForce(dir );
	}
	else 
	{
		impulse.x = IMPULSE.x * m_Direction;
		impulse.y = IMPULSE.y * m_Direction * -1;
		m_ActActorPtr->SetLinearVelocity(impulse);
	}
}

int Skelethon::GetInitialHealth()
{
	return 2;
}