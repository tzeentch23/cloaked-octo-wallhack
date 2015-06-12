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
int Moss::m_InstanceCounter = 0;
Moss::Moss(DOUBLE2 pos)
{
	m_SpawnPos = pos;
	++m_InstanceCounter;
	if (m_BmpMossPtr == nullptr)
	{
		m_BmpMossPtr = new Bitmap(String("./resources/moss.png"));
	}
	m_ActorWidth = m_BmpMossPtr->GetWidth();
	m_ActorHeight = m_BmpMossPtr->GetHeight();

	m_ActMossPtr = new PhysicsActor(pos, 0, BodyType::KINEMATIC);
	m_ActMossPtr->AddBoxShape(m_ActorWidth, m_ActorHeight / 2, 0.3, 0, 0.2);
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
	DOUBLE2 bitmapPos = DOUBLE2(m_ActMossPtr->GetPosition().x - m_BmpMossPtr->GetWidth() / 2,
		m_ActMossPtr->GetPosition().y - m_BmpMossPtr->GetHeight());

	matTranslate.SetAsTranslate(bitmapPos);
	matRotate.SetAsRotate(m_Angle);
	matRotate.SetAsScale(m_Scale);
	matWorldTransform = matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);

	GAME_ENGINE->DrawBitmap(m_BmpMossPtr);
}


void Moss::ResetPos()
{
	m_ActMossPtr->SetPosition(m_SpawnPos);
}