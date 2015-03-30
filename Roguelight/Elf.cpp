//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "Elf.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
//static int ACTOR_HEIGHT = 100;
//static int ACTOR_WIDTH = 40;
Elf::Elf(DOUBLE2 spawnposition) : m_SpawnPos(spawnposition)
{
	m_ActElfPtr = new PhysicsActor(m_SpawnPos, 0, BodyType::KINEMATIC);
	m_ActElfPtr->AddBoxShape(ACTOR_HEIGHT, ACTOR_WIDTH);

	//m_BmpElfPtr = new Bitmap(String("./resources/"))
	// m_ActCirclePtr->AddContactListener(this);
}

Elf::~Elf()
{
	// nothing to destroElf
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
//void Elf::BeginContact(PhysicsActor *actorPtr, ContactListener * otherContactlistenerPtr)
//{
//	
//}
//
//void Elf::EndContact(PhysicsActor *actorPtr, ContactListener * otherContactlistenerPtr)
//{
//
//}

// Add here the methods - Member functions

void Elf::Paint()
{
	GAME_ENGINE->FillEllipse(m_Position, 30, 30);
}

void Elf::Tick(double deltatime)
{
	if (GAME_ENGINE->IsKeyboardKeyPressed('Z'))
	{
		DOUBLE2 velocityChange, desiredVelocity(0, -500);
		velocityChange.y = desiredVelocity.y - m_ActElfPtr->GetLinearVelocity().y;
		double mass = m_ActElfPtr->GetMass();
		DOUBLE2 impulse = mass* velocityChange / PhysicsActor::m_Scale;
		m_ActElfPtr->ApplyLinearImpulse(impulse);
	}
}