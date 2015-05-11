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
	void Tick(double deltaTime);

private:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform;
	double m_Scale = 1;
	double m_Angle = 0;
	PhysicsActor * m_ActLampAPtr = nullptr, *m_ActLampBPtr = nullptr;
	PhysicsDistanceJoint *m_DistanceJointPtr = nullptr;
	static Bitmap * m_BmpLampAPtr, * m_BmpLampBPtr;
	static int m_InstanceCounter;
	double m_ActorAWidth, m_ActorAHeight, m_ActorBWidth, m_ActorBHeight;
	DOUBLE2 m_InitPosition, m_BulbPosition;

};


