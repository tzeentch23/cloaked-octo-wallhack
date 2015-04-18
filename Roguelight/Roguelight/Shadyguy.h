#pragma once
//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

#include "Enemies.h"
//-----------------------------------------------------
// Shadyguy Class									
//-----------------------------------------------------
class Shadyguy : public Enemies
{
public:
	Shadyguy( );
	virtual ~Shadyguy( );

	// C++11 make the class non-copShadyguyable
	Shadyguy( const Shadyguy& ) = delete;
	Shadyguy& operator=( const Shadyguy& ) = delete;
	
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
	Bitmap *m_BmpShadyPtr = nullptr;
	PhysicsActor * m_ActShadyPtr = nullptr;
};

 
