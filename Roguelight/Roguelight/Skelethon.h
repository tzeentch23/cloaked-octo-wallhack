#pragma once
//-----------------------------------------------------
// Name:
// First name:
// Group: 1DAE.
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

//#include "ContactListener.h"
//-----------------------------------------------------
// Y Class									
//-----------------------------------------------------
class Y //: public ContactListener
{
public:
	Y( );
	virtual ~Y( );

	// C++11 make the class non-copyable
	Y( const Y& ) = delete;
	Y& operator=( const Y& ) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	//virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	//virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);   
	//virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);


private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

};

 
