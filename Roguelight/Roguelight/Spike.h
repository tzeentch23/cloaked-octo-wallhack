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
// Spike Class									
//-----------------------------------------------------
class Spike : public ContactListener
{
public:
	Spike(DOUBLE2 pos);
	virtual ~Spike( );

	// C++11 make the class non-copSpikesable
	Spike( const Spike& ) = delete;
	Spike& operator=( const Spike& ) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);   
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
	void Paint();
	void ResetPos();
	

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	DOUBLE2 m_SpawnPos;
	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform;
	double m_Scale = 1;
	double m_Angle = 0;
	PhysicsActor * m_ActSpikePtr = nullptr;
	static Bitmap * m_BmpSpikePtr;
	static int m_InstanceCounter;
};