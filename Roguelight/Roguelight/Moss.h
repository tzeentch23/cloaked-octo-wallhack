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
// Moss Class									
//-----------------------------------------------------
class Moss //: public ContactListener
{
public:
	Moss( );
	virtual ~Moss( );

	// C++11 make the class non-copMossable
	Moss( const Moss& ) = delete;
	Moss& operator=( const Moss& ) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);   
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
	void Paint();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	PhysicsActor * m_ActMossPtr = nullptr;
	Bitmap * m_BmpMossPtr = nullptr;
};

 
