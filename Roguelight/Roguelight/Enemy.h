#pragma once
//-----------------------------------------------------
// Name: Kirkorova
// First name: Angelika
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

#include "ContactListener.h"
//-----------------------------------------------------
// Enemy Class									
//-----------------------------------------------------
class Enemy : public ContactListener
{
public:
	Enemy( );
	virtual ~Enemy( );

	// C++11 make the class non-copEnemyable
	Enemy( const Enemy& ) = delete;
	Enemy& operator=( const Enemy& ) = delete;
	void Paint();
	void Patrol();

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);   
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);


private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	int m_Health;
	const static int ENEMY_WIDTH;
	const static int ENEMY_HEIGHT;

};

 
