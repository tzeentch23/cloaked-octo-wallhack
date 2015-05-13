//-----------------------------------------------------
// Name: Kirkorova
// First name: Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		

//---------------------------
// Includes
//---------------------------
#include "Lamp.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())


//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap* Lamp::m_BmpLampAPtr = nullptr;
Bitmap* Lamp::m_BmpLampBPtr = nullptr;
int Lamp::m_InstanceCounter = 0;
double Lamp::m_ActorAWidth = 20;
double Lamp::m_ActorAHeight = 10;
double Lamp::m_ActorBWidth = 10;
double Lamp::m_ActorBHeight = 20;
Lamp::Lamp(DOUBLE2 pos)
{
	++m_InstanceCounter;
	if (m_BmpLampAPtr == nullptr)
	{
	}
	if (m_BmpLampBPtr == nullptr)
	{
	}
	m_InitPosition = pos;
	m_BulbPosition.y = m_InitPosition.y+80;
	m_BulbPosition.x = m_InitPosition.x;

	m_ActLampAPtr = new PhysicsActor(m_InitPosition, 0, BodyType::STATIC);
	m_ActLampAPtr->AddBoxShape(m_ActorAWidth, m_ActorAHeight / 2, 0.2, 0.5, 0.2);


	m_ActLampBPtr = new PhysicsActor(m_BulbPosition, 0, BodyType::DYNAMIC);
	m_ActLampBPtr->AddBoxShape(m_ActorBWidth, m_ActorBHeight / 2, 0.2, 0.5, 0.2);
	m_ActLampBPtr->SetGravityScale(1);

	m_DistanceJointPtr = new PhysicsDistanceJoint(m_ActLampAPtr, DOUBLE2(0, 0), m_ActLampBPtr, DOUBLE2(0, 0), 50);


}

Lamp::~Lamp()
{
	delete m_DistanceJointPtr;
	m_DistanceJointPtr = nullptr;
	delete m_ActLampAPtr;
	m_ActLampAPtr = nullptr;
	delete m_ActLampBPtr;
	m_ActLampBPtr = nullptr;

	--m_InstanceCounter;

	
	if (m_InstanceCounter == 0)
	{
		delete m_BmpLampAPtr;
		m_BmpLampAPtr = nullptr;
		delete m_BmpLampBPtr;
		m_BmpLampBPtr = nullptr;
	}
}

void Lamp::Paint()
{
	matTranslate.SetAsTranslate(m_BulbPosition);
	matRotate.SetAsRotate(m_Angle);
	matRotate.SetAsScale(m_Scale);
	matWorldTransform = matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);

	GAME_ENGINE->DrawBitmap(m_BmpLampAPtr);
}

bool Lamp::CheckHit(PhysicsActor * actPtr)
{
	if (actPtr == m_ActLampBPtr)
	{
		return true; 
	}
	return false;
}
//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Lamp::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Lamp::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Lamp::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}


