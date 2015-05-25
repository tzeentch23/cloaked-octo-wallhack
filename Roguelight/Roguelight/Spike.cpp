//-----------------------------------------------------
// Name:Angelika
// First name:Kirkorova
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"	
#include "Elf.h"

//---------------------------
// Includes
//---------------------------
#include "Spike.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * Spike::m_BmpSpikePtr = nullptr;
int Spike::m_InstanceCounter = 0;
Spike::Spike(DOUBLE2 pos)
{

	m_SpawnPos = pos;
	++m_InstanceCounter;
	m_ActSpikePtr = new PhysicsActor(pos, 0, BodyType::KINEMATIC);
	m_ActSpikePtr->AddBoxShape(40, 10, 0.2, 0.9, 0);
	m_ActSpikePtr->AddContactListener(this);
	if (m_BmpSpikePtr == nullptr)
	{
		m_BmpSpikePtr = new Bitmap(String("./resources/Spike.png"));
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

	matTranslate.SetAsTranslate(bitmapPos);
	matRotate.SetAsRotate(m_Angle);
	matRotate.SetAsScale(m_Scale);
	matWorldTransform = matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);

	GAME_ENGINE->DrawBitmap(m_BmpSpikePtr);
}

void Spike::ResetPos()
{
	m_ActSpikePtr->SetPosition(m_SpawnPos);
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Spike::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	Elf * elf = Elf::GetPlayer();
	if (actOtherPtr == elf->GetPhysicsActor())
	{
		elf->DecreaseHealth();
	}
}

void Spike::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Spike::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}


