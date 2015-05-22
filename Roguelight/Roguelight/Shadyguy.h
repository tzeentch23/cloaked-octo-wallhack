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
	virtual ~Shadyguy();

	// C++11 make the class non-copShadyguyable
	Shadyguy(const Shadyguy&) = delete;
	Shadyguy& operator=(const Shadyguy&) = delete;

	virtual void Tick(double deltaTime);
	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	
	virtual int GetInitialHealth();

public:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

private:
	int m_Direction = 1;
	static const DOUBLE2 IMPULSE;
	static const int MAX_DISTANCE = 300;
};



