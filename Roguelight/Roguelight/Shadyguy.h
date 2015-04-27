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
//-----------------------------------------------------
// Shadyguy Class									
//-----------------------------------------------------
class Shadyguy : public Enemy
{
public:
	Shadyguy(DOUBLE2 pos);
	virtual ~Shadyguy( );

	// C++11 make the class non-copShadyguyable
	Shadyguy( const Shadyguy& ) = delete;
	Shadyguy& operator=( const Shadyguy& ) = delete;
	
	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	/*virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);   
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
*/

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static Bitmap *m_BmpShadyPtr;
	PhysicsActor * m_ActShadyPtr = nullptr;
};

 
