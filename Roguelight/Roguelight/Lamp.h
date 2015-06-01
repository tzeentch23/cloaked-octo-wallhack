#pragma once
//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

#include "ContactListener.h"
//-----------------------------------------------------
// Lamp Class									
//-----------------------------------------------------

class PhysicsActor;
class Roguelight;
class Lamp : public ContactListener
{
public:
	Lamp(DOUBLE2 pos);
	virtual ~Lamp();

	// C++11 make the class non-copLampable
	Lamp(const Lamp&) = delete;
	Lamp& operator=(const Lamp&) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
	void Paint();
	void Reset();
	bool CheckHit(PhysicsActor * actPtr);
	DOUBLE2 GetPosition();
	
private:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform, matPivot;
	double m_Scale = 1;
	double m_Angle = 0;
	int m_JointLenght = 50;
	PhysicsActor * m_ActLampAPtr = nullptr, *m_ActBulbPtr = nullptr;
	PhysicsActor *m_ActChainPtr = nullptr;
	std::vector<PhysicsActor*> m_ChainArr;
	std::vector<PhysicsRevoluteJoint*> m_RevJntArr;
	static Bitmap * m_BmpChainFragmentPtr, *m_BmpBulbOnPtr, *m_BmpBulbOffPtr;
	static int m_InstanceCounter;
	static double m_ActorWidth, m_ActorHeight;
	DOUBLE2 m_InitPosition, m_BulbPosition;
	Roguelight * m_Game;
	bool m_IsOn = false;
};

