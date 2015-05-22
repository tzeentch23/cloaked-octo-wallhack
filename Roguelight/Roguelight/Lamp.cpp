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
Bitmap* Lamp::m_BmpChainPtr = nullptr;
Bitmap* Lamp::m_BmpBulbOnPtr = nullptr;
Bitmap* Lamp::m_BmpBulbOffPtr = nullptr;
int Lamp::m_InstanceCounter = 0;
double Lamp::m_ActorWidth = 11;
double Lamp::m_ActorHeight = 18;
Lamp::Lamp(DOUBLE2 pos)
{
	++m_InstanceCounter;
	if (m_BmpChainPtr == nullptr)
	{
		m_BmpChainPtr = new Bitmap(String("./resources/chain.png"));
	}
	if (m_BmpBulbOnPtr == nullptr)
	{
		m_BmpBulbOnPtr = new Bitmap(String("./resources/bulbOn.png"));
	}
	if (m_BmpBulbOffPtr == nullptr)
	{
		m_BmpBulbOffPtr = new Bitmap(String("./resources/bulbOff.png"));
	}
	m_InitPosition = pos;
	m_BulbPosition.y = m_InitPosition.y+m_JointLenght;
	m_BulbPosition.x = m_InitPosition.x;

	m_ActLampAPtr = new PhysicsActor(m_InitPosition, 0, BodyType::STATIC);
	m_ActLampAPtr->AddBoxShape(m_ActorWidth, m_ActorHeight / 2, 0.2, 0.5, 0.2);


	m_ActLampBPtr = new PhysicsActor(m_BulbPosition, 0, BodyType::DYNAMIC);
	m_ActLampBPtr->AddBoxShape(m_ActorWidth, m_ActorHeight / 2, 0.2, 0.5, 0.2);
	m_ActLampBPtr->SetGravityScale(1.3);
	m_ActLampBPtr->SetFixedRotation(true);

	m_DistanceJointPtr = new PhysicsDistanceJoint(m_ActLampAPtr, DOUBLE2(0, 0), m_ActLampBPtr, DOUBLE2(0, 0), m_JointLenght, -1, 0.1);
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
		delete m_BmpChainPtr;
		m_BmpChainPtr = nullptr;
		delete m_BmpBulbOnPtr;
		m_BmpBulbOnPtr = nullptr;
		delete m_BmpBulbOffPtr;
		m_BmpBulbOffPtr = nullptr;
	}
}

void Lamp::Paint()
{
	
	DOUBLE2 bulbPos = m_ActLampBPtr->GetPosition();
	matTranslate.SetAsTranslate(bulbPos);
	matRotate.SetAsRotate(m_Angle);
	matRotate.SetAsScale(m_Scale);
	matWorldTransform = matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);
	
	Bitmap *bmp;
	if (m_IsOn)
	{
		bmp = m_BmpBulbOnPtr;
	}
	else 
	{
		bmp = m_BmpBulbOffPtr;
	}
	GAME_ENGINE->DrawBitmap(bmp);
	//RECT Chain(0, 0, m_ActLampAPtr->GetPosition().x - m_ActLampBPtr->GetPosition().x, m_ActLampAPtr->GetPosition().y - m_ActLampBPtr->GetPosition().y);
	//matRotate.SetAsRotate(m_ActLampBPtr->GetAngle());
	//GAME_ENGINE->DrawBitmap(m_BmpChainPtr);
	//DOUBLE2 chainPos = m_ActLampAPtr->GetPosition();
}
void Lamp::Reset()
{
	m_IsOn = false;
}
//------------------------------------
//Checks that bullet has hit this lamp
//------------------------------------
bool Lamp::CheckHit(PhysicsActor * actPtr)
{
	if (actPtr == m_ActLampBPtr)
	{
		m_IsOn = true;
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


DOUBLE2 Lamp::GetPosition() 
{
	return m_ActLampBPtr->GetPosition();
}

