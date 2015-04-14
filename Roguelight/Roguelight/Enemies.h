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
// Enemies Class									
//-----------------------------------------------------
class Enemies : public ContactListener
{
public:
	Enemies( );
	virtual ~Enemies( );

	// C++11 make the class non-copEnemiesable
	Enemies( const Enemies& ) = delete;
	Enemies& operator=( const Enemies& ) = delete;
	//void Paint();
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
};

 
