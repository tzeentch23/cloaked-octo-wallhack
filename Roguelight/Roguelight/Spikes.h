#pragma once
//-----------------------------------------------------
// Name:
// First name:
// Group: 1DAE.
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

#include "ContactListener.h"
//-----------------------------------------------------
// Spikes Class									
//-----------------------------------------------------
class Spikes : public ContactListener
{
public:
	Spikes( );
	virtual ~Spikes( );

	// C++11 make the class non-copSpikesable
	Spikes( const Spikes& ) = delete;
	Spikes& operator=( const Spikes& ) = delete;

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
	PhysicsActor * m_ActSpikesPtr = nullptr;
	Bitmap * m_BmpSpikesPtr = nullptr;

};

 
