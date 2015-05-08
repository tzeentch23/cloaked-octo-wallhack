#pragma once
//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

//#include "ContactListener.h"
//-----------------------------------------------------
// Arrow Class									
//-----------------------------------------------------
class Arrow //: public ContactListener
{
public:
	Arrow( );
	virtual ~Arrow( );

	// C++11 make the class non-copArrowable
	Arrow( const Arrow& ) = delete;
	Arrow& operator=( const Arrow& ) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	//virtual void BeginContact(PhArrowsicsActor *actThisPtr, PhArrowsicsActor *actOtherPtr); 
	//virtual void EndContact(PhArrowsicsActor *actThisPtr, PhArrowsicsActor *actOtherPtr);   
	//virtual void ContactImpulse(PhArrowsicsActor *actThisPtr, double impulse);


private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

};

 
