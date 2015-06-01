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
Bitmap* Lamp::m_BmpChainFragmentPtr = nullptr;
Bitmap* Lamp::m_BmpBulbOnPtr = nullptr;
Bitmap* Lamp::m_BmpBulbOffPtr = nullptr;
int Lamp::m_InstanceCounter = 0;
double Lamp::m_ActorWidth = 11;
double Lamp::m_ActorHeight = 18;
Lamp::Lamp(DOUBLE2 pos)
{
	++m_InstanceCounter;
	if (m_BmpChainFragmentPtr == nullptr)
	{
		m_BmpChainFragmentPtr = new Bitmap(String("./resources/chainFragment.png"));
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

	// chain of revolute joints
	double boxWidth = 10;
	double boxHeight = 12;
	m_ActChainPtr = new PhysicsActor(m_InitPosition, 0, BodyType::STATIC);
	m_ActChainPtr->AddCircleShape(boxHeight / 2);
	PhysicsActor * actChainPtr = m_ActChainPtr;
	
	for (size_t i = 0; i < 4; i++)
	{
		PhysicsActor * newActChainPtr = new PhysicsActor(m_InitPosition + DOUBLE2(0, boxHeight * (i + 1) * 1.1), 0, BodyType::DYNAMIC);
		newActChainPtr->AddBoxShape(boxWidth, boxHeight);

		PhysicsRevoluteJoint *jointPtr = new PhysicsRevoluteJoint(
			actChainPtr, DOUBLE2(0, boxHeight / 2 * 1.1),
			newActChainPtr, DOUBLE2(0, -boxHeight / 2 * 1.1),
			false, 0.0);
			actChainPtr = newActChainPtr;

		m_ChainArr.push_back(newActChainPtr);
		m_RevJntArr.push_back(jointPtr);
	}
}

Lamp::~Lamp()
{
	for (size_t i = 0; i < m_RevJntArr.size(); i++)
	{
		delete m_RevJntArr[i];
		m_RevJntArr[i] = nullptr;
	}


	for(size_t i = 0; i < m_ChainArr.size(); i++)
	{
		delete m_ChainArr[i];
		m_ChainArr[i] = nullptr;
	}


	/*delete m_ActLampAPtr;
	m_ActLampAPtr = nullptr;
	*/
	delete m_ActBulbPtr;
	m_ActBulbPtr = nullptr;
	delete m_ActChainPtr;
	m_ActChainPtr = nullptr;

	--m_InstanceCounter;

	
	if (m_InstanceCounter == 0)
	{
		delete m_BmpChainFragmentPtr;
		m_BmpChainFragmentPtr = nullptr;
		delete m_BmpBulbOnPtr;
		m_BmpBulbOnPtr = nullptr;
		delete m_BmpBulbOffPtr;
		m_BmpBulbOffPtr = nullptr;
	}
}

void Lamp::Paint()
{	
	/*DOUBLE2 pivot = DOUBLE2(m_ChainArr[0]->GetPosition().x, m_ChainArr[0]->GetPosition().y);
	matPivot.SetAsTranslate(pivot);
*/
	for (int i = 0; i < m_ChainArr.size(); i++)
	{
		Bitmap * bmp = m_BmpChainFragmentPtr;
		if (i == m_ChainArr.size() - 1)
		{
			if (m_IsOn) 
			{
				bmp = m_BmpBulbOnPtr;
			}
			else 
			{
				bmp = m_BmpBulbOffPtr;
			}
		}
	
		DOUBLE2 chainFragmentPos = DOUBLE2(m_ChainArr[i]->GetPosition().x - bmp->GetWidth()/2,
			m_ChainArr[i]->GetPosition().y - bmp->GetHeight() / 2);
		matTranslate.SetAsTranslate(chainFragmentPos);
		matRotate.SetAsRotate(m_ChainArr[i]->GetAngle());
		if (m_IsOn) 
		{
			OutputDebugString(String(i) +  String(": ") + String(m_ChainArr[i]->GetAngle()) + String('\n'));
		}
		matRotate.SetAsScale(m_Scale);
		matWorldTransform = matPivot*  matRotate * matScale * matTranslate;
		GAME_ENGINE->SetWorldMatrix(matWorldTransform);
		GAME_ENGINE->DrawBitmap(bmp);
	}
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
	for (size_t i = 0; i < m_ChainArr.size(); i++)
	{
		if (actPtr == m_ChainArr[i])
		{
			m_IsOn = true;
			return true;
		}
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
	return m_ActChainPtr->GetPosition();
}

