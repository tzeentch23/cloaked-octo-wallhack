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
	Shadyguy(DOUBLE2 pos, Bitmap * bmpPtr);
	virtual ~Shadyguy( );

	// C++11 make the class non-copShadyguyable
	Shadyguy( const Shadyguy& ) = delete;
	Shadyguy& operator=( const Shadyguy& ) = delete;
	
	void Tick(double deltaTime);
	void Patrol();
	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	/*virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);   
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
*/

public: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	
	
	 //ok kak shte gi podavame? zashto da gi podavame?
	//enemy-to shte si gi pravi..

private:
	
	DOUBLE2 m_InitialPosition;
};

 
