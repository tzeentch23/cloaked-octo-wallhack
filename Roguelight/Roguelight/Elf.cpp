//-----------------------------------------------------
// Name:Angelika
// First name:Kirkorova
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
Elf::Elf(DOUBLE2 spawnPos) : m_SpawnPos(spawnPos)
{
	m_ActElfPtr = new PhysicsActor(m_SpawnPos, 0, BodyType::DYNAMIC);
	m_ActElfPtr->AddBoxShape(ACTOR_WIDTH, ACTOR_HEIGHT, 0, 0.2, 0.2);
	m_ActElfPtr->SetFixedRotation(true);
	m_ActElfPtr->SetGravityScale(1);
}

Elf::~Elf()
{
	delete m_ActElfPtr;
	m_ActElfPtr = nullptr;
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
//void Elf::BeginContact(PhElfsicsActor *actThisPtr, PhElfsicsActor *actOtherPtr)
//{
//
//}
//
//void Elf::EndContact(PhElfsicsActor *actThisPtr, PhElfsicsActor *actOtherPtr)
//{
//
//}
//
//void Elf::ContactImpulse(PhElfsicsActor *actThisPtr, double impulse)
//{
//
//}

void Elf::Paint()
{
	//GAME_ENGINE->FillEllipse(m_Position, 30, 30);
}

void Elf::Tick(double deltatime)
{
		DOUBLE2 velocityChange, newVelocity, impulse;
		newVelocity.y = 200;
		double mass = m_ActElfPtr->GetMass();//tova da ne e 
		m_Time += deltatime;

		if (GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT))
		{
			m_State = State::WALKING;
			newVelocity.x = -500;
		}
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
		{
			m_State = State::WALKING;
			newVelocity.x = 500;
		}

		if (GAME_ENGINE->IsKeyboardKeyPressed('Z'))
		{
			m_State = State::JUMPING;
			newVelocity.y = -25000;
		}

		velocityChange.y = newVelocity.y - m_ActElfPtr->GetLinearVelocity().y;
		velocityChange.x = newVelocity.x - m_ActElfPtr->GetLinearVelocity().x;
		impulse = mass * velocityChange / PhysicsActor::SCALE;
		m_ActElfPtr->ApplyForce(impulse);

	}
	
DOUBLE2 Elf::GetPosition()
{
	DOUBLE2 posActor = m_ActElfPtr->GetPosition();
	return posActor;
}

void Elf::ResetPosition()
{
	m_ActElfPtr->SetPosition(DOUBLE2(GAME_ENGINE->GetWidth() / 2, GAME_ENGINE->GetHeight() / 2));
	m_ActElfPtr->SetAngle(0.0);
	m_ActElfPtr->SetAngularVelocity(0.0);
	m_ActElfPtr->SetLinearVelocity(DOUBLE2(0, 0));
}