#pragma once
//-----------------------------------------------------
// Name: Kirkorova
// First name: Angelika
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

#include "Actor.h"
//-----------------------------------------------------
// Enemy Class									
//-----------------------------------------------------
class Enemy : public Actor
{
public:
	Enemy(DOUBLE2 spawnPos, int frameRate, int nrCols, int nrRows, Bitmap * bmpPtr);
	virtual ~Enemy( );

	// C++11 make the class non-copEnemyable
	Enemy( const Enemy& ) = delete;
	Enemy& operator=( const Enemy& ) = delete;
	virtual void Paint();
	virtual void Tick(double deltaTime);
	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	//virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);

protected: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	DOUBLE2 m_LastPosition =  DOUBLE2(0, 0);
	int m_Direction = 1;
	time_t m_LastChangeDirectionTime = 0;
	double m_StuckTime = 0;
	void ChangeDirection();
};
 
