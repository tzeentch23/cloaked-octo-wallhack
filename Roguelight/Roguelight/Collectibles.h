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
// Collectibles Class									
//-----------------------------------------------------
class Collectibles //: public ContactListener
{
public:
	Collectibles( );
	virtual ~Collectibles( );

	// C++11 make the class non-copCollectiblesable
	Collectibles( const Collectibles& ) = delete;
	Collectibles& operator=( const Collectibles& ) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	//virtual void BeginContact(PhCollectiblessicsActor *actThisPtr, PhCollectiblessicsActor *actOtherPtr); 
	//virtual void EndContact(PhCollectiblessicsActor *actThisPtr, PhCollectiblessicsActor *actOtherPtr);   
	//virtual void ContactImpulse(PhCollectiblessicsActor *actThisPtr, double impulse);


private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

};

 
