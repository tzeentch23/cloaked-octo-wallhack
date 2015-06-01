//-----------------------------------------------------
// Name: Kirkorova
// First name: Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		

//---------------------------
// Includes
//---------------------------
#include "Door.h"
#include "Elf.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())


//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap* Door::m_BmpDoorPtr = nullptr;
int Door::m_InstanceCounter = 0;
Door::Door(DOUBLE2 pos)
{
	m_SpawnPos = pos;
	++m_InstanceCounter;
	if (m_BmpDoorPtr == nullptr)
	{
		m_BmpDoorPtr = new Bitmap(String("./resources/door.png"));
	}
	m_ActorWidth = m_BmpDoorPtr->GetWidth();
	m_ActorHeight = m_BmpDoorPtr->GetHeight();

	m_ActDoorPtr = new PhysicsActor(pos, 0, BodyType::KINEMATIC);
	m_ActDoorPtr->AddBoxShape(m_ActorWidth, m_ActorHeight, 0.5, 0.5, 0.2);
	m_ActTriggerPtr = new PhysicsActor(DOUBLE2(pos.x + 50, pos.y), 0, BodyType::STATIC);
	m_ActTriggerPtr->AddBoxShape(5,5,0,0,0);
	m_ActTriggerPtr->SetTrigger(true);

	}

Door::~Door()
{
	delete m_ActDoorPtr;
	m_ActDoorPtr = nullptr;
	delete m_ActTriggerPtr;
	m_ActTriggerPtr = nullptr;
	--m_InstanceCounter;

	if (m_InstanceCounter == 0)
	{
		delete m_BmpDoorPtr;
		m_BmpDoorPtr = nullptr;
	}
}

void Door::Paint()
{
	DOUBLE2 bitmapPos = DOUBLE2(m_ActDoorPtr->GetPosition().x - m_BmpDoorPtr->GetWidth() / 2,
		m_ActDoorPtr->GetPosition().y - m_BmpDoorPtr->GetHeight()/2);

	matTranslate.SetAsTranslate(bitmapPos);
	matRotate.SetAsRotate(m_Angle);
	matRotate.SetAsScale(m_Scale);
	matWorldTransform = matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);

	GAME_ENGINE->DrawBitmap(m_BmpDoorPtr);
}
void Door::Tick(double deltaTime)
{
	if (m_ActTriggerPtr->IsOverlapping(Elf::GetPlayer()->GetPhysicsActor()))
	{
		
		m_ActDoorPtr->SetLinearVelocity(DOUBLE2(0, -50));

		DOUBLE2 newPos = m_ActDoorPtr->GetPosition();
		double dif = (newPos - m_SpawnPos).Length();
		if (dif >= m_ActorHeight)
		{
			m_ActDoorPtr->SetLinearVelocity(DOUBLE2(0, 0));
		}
	}
}

void Door::ResetPos()
{
	m_ActDoorPtr->SetPosition(m_SpawnPos);
}