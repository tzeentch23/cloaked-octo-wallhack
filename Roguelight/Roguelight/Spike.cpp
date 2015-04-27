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
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * Spike::m_BmpSpikePtr = nullptr;
int m_InstanceCounter = 0;
Spike::Spike(DOUBLE2 pos)
{
	m_ActSpikePtr = new PhysicsActor(pos, 0, BodyType::STATIC);
	m_ActSpikePtr->AddBoxShape(40, 10, 0.2, 0.9, 0.2);
	if (m_BmpSpikePtr == nullptr)
	{
		m_BmpSpikePtr = new Bitmap(String("./resources/spikes.png"));
		m_BmpSpikePtr->SetTransparencyColor(COLOR(255, 0, 0));
	}
		}

Spike::~Spike()
{
	delete m_ActSpikePtr;
	m_ActSpikePtr = nullptr;
	--m_InstanceCounter;

	if (m_InstanceCounter == 0)
	{
		delete m_BmpSpikePtr;
		m_BmpSpikePtr = nullptr;
	}
}

void Spike::Paint()
{
	DOUBLE2 bitmapPos = DOUBLE2(m_ActSpikePtr->GetPosition().x - m_BmpSpikePtr->GetWidth() / 2,
		m_ActSpikePtr->GetPosition().y - m_BmpSpikePtr->GetHeight() / 2);
	GAME_ENGINE->DrawBitmap(m_BmpSpikePtr, bitmapPos);

}
//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Spike::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Spike::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Spike::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}


