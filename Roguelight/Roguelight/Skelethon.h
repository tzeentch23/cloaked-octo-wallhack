#pragma once
//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Enemy.h"
//#include "ContactListener.h"
//-----------------------------------------------------
// Skelethon Class									
//-----------------------------------------------------
class Skelethon : public Enemy
{
public:
	Skelethon( );
	virtual ~Skelethon( );

	// C++11 make the class non-copSkelethonable
	Skelethon( const Skelethon& ) = delete;
	Skelethon& operator=( const Skelethon& ) = delete;

	void Follow(DOUBLE2 posActor);
	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	//virtual void BeginContact(PhSkelethonsicsActor *actThisPtr, PhSkelethonsicsActor *actOtherPtr); 
	//virtual void EndContact(PhSkelethonsicsActor *actThisPtr, PhSkelethonsicsActor *actOtherPtr);   
	//virtual void ContactImpulse(PhSkelethonsicsActor *actThisPtr, double impulse);


private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	PhysicsActor * m_ActSkelethonPtr = nullptr;
	Bitmap * m_BmpSkelethonPtr = nullptr;
	
	
};

 
