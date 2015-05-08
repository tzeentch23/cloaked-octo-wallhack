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
// Bullet Class									
//-----------------------------------------------------
class Bullet : public ContactListener
{
public:
	Bullet(DOUBLE2 pos, DOUBLE2 velocity);
	virtual ~Bullet();

	// C++11 make the class non-copBulletable
	Bullet(const Bullet&) = delete;
	Bullet& operator=(const Bullet&) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
	void Paint();
	void Tick(double deltaTime);
	bool IsFlying();

public:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform;
	double m_Scale = 1;
	double m_Angle = 0;
	double m_Time;

	DOUBLE2 m_Position;
	DOUBLE2 m_Velocity;

	PhysicsActor *m_ActortPtr = nullptr;

	bool m_IsFlying = false;
};


