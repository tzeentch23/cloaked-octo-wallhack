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
Lamp::Lamp(DOUBLE2 pos)
{
	++m_InstanceCounter;
	if (m_BmpLampAPtr == nullptr)
	{
//		m_BmpLampAPtr = new Bitmap(String("./resources/Lamp.png"));
	}
	if (m_BmpLampBPtr == nullptr)
	{
//		m_BmpLampBPtr = new Bitmap(String("./resources/Lamp.png"));
	}
//	m_ActorWidth = m_BmpLampPtr->GetWidth();
//	m_ActorHeight = m_BmpLampPtr->GetHeight();
	m_InitPosition = pos;
	m_BulbPosition.x = m_InitPosition.x;
	m_BulbPosition.y = m_InitPosition.y+80;
	m_ActLampAPtr = new PhysicsActor(pos, 0, BodyType::KINEMATIC);
	m_ActLampAPtr->AddBoxShape(m_ActorAWidth, m_ActorAHeight / 2, 0.2, 0.5, 0.2);

	m_ActLampBPtr = new PhysicsActor(pos, 0, BodyType::KINEMATIC);
	m_ActLampBPtr->AddBoxShape(m_ActorBWidth, m_ActorBHeight / 2, 0.2, 0.5, 0.2);

}

Lamp::~Lamp()
{
	delete m_ActLampAPtr;
	m_ActLampAPtr = nullptr;
	delete m_ActLampBPtr;
	m_ActLampBPtr = nullptr;
	delete m_DistanceJointPtr;
	m_DistanceJointPtr = nullptr;

	--m_InstanceCounter;

	if (m_InstanceCounter == 0)
	{
		delete m_BmpLampAPtr;
		m_BmpLampAPtr = nullptr;
		delete m_BmpLampBPtr;
		m_BmpLampBPtr = nullptr;
	}
}

void Lamp::Tick(double deltaTime)
{
	m_ActLampAPtr = new PhysicsActor(m_InitPosition, 0, BodyType::KINEMATIC);
	m_ActLampAPtr->AddBoxShape(10, 20);
	m_ActLampAPtr->SetGhost(true);

	m_ActLampBPtr = new PhysicsActor(m_BulbPosition, 0, BodyType::DYNAMIC);
	m_ActLampBPtr->AddBoxShape(50, 70);

	m_DistanceJointPtr = new PhysicsDistanceJoint(m_ActLampAPtr, DOUBLE2(0, 0), m_ActLampBPtr, DOUBLE2(0, 0), 150);

}
void Lamp::Paint()
{
	/*matTranslate.SetAsTranslate(m_);
	matRotate.SetAsRotate(m_Angle);
	matRotate.SetAsScale(m_Scale);
	matWorldTransform = matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);

	GAME_ENGINE->DrawBitmap(m_BmpLampPtr);*/
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


