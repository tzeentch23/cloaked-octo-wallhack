//-----------------------------------------------------
// Name: Kirkorova
// First name: Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "Moss.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())


//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap* Moss::m_BmpMossPtr = nullptr;
int m_InstanceCounter = 0;
Moss::Moss(DOUBLE2 pos)
{
	if (m_BmpMossPtr == nullptr)
	{
		m_BmpMossPtr = new Bitmap(String("./resources/moss.png"));
		m_BmpMossPtr->SetTransparencyColor(COLOR(255, 0, 0));
		++m_InstanceCounter;
	}
	m_ActorWidth = m_BmpMossPtr->GetWidth();
	m_ActorHeight = m_BmpMossPtr->GetHeight();

	m_ActMossPtr = new PhysicsActor(pos, 0, BodyType::STATIC);
	m_ActMossPtr->AddBoxShape(m_ActorWidth, m_ActorHeight, 0.2, 0.9, 0.2);
}

Moss::~Moss()
{
	delete m_ActMossPtr;
	m_ActMossPtr = nullptr;
	--m_InstanceCounter;

	if (m_InstanceCounter == 0)
	{
		delete m_BmpMossPtr;
		m_BmpMossPtr = nullptr;
	}
}

void Moss::Paint()
{
	DOUBLE2 bitmapPos = DOUBLE2(m_ActMossPtr->GetPosition().x-m_BmpMossPtr->GetWidth()/2,
		m_ActMossPtr->GetPosition().y - m_BmpMossPtr->GetHeight() / 2);
	GAME_ENGINE->DrawBitmap(m_BmpMossPtr, bitmapPos);
}
//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Moss::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Moss::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Moss::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}


