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
	m_ActElfPtr->AddBoxShape(ACTOR_WIDTH, ACTOR_HEIGHT, 0, 0, 1.0);
	m_ActElfPtr->SetFixedRotation(true);
	//m_ActElfPtr->SetGravityScale(10.0);
	
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
	double mass = m_ActElfPtr->GetMass();
	m_Time += deltatime;
	if (GAME_ENGINE->IsKeyboardKeyPressed('Z'))
	{
//		if (m_Time < 0.25)
//		{
			newVelocity.y = -200;
//		}
//		else if ((m_Time >= 0.25) && (GAME_ENGINE->IsKeyboardKeyReleased('Z')))
//		{
//			newVelocity.y = -400;
//		}
	}
	if (GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT))
	{
		newVelocity.x = -100;
	}
	if (GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
	{
		newVelocity.x = 100;
	}
	velocityChange.y = newVelocity.y - m_ActElfPtr->GetLinearVelocity().y;
	velocityChange.x = newVelocity.x - m_ActElfPtr->GetLinearVelocity().x;
	impulse = mass* velocityChange / PhysicsActor::SCALE;
	m_ActElfPtr->ApplyLinearImpulse(impulse);
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