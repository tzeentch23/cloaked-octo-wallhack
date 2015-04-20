#pragma once
//-----------------------------------------------------
// Name:Angelika
// First name:Kirkorova
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

#include "ContactListener.h"
//-----------------------------------------------------
// Elf Class									
//-----------------------------------------------------
class Elf //: public ContactListener
{
public:
	Elf(DOUBLE2 spawnPos);
	virtual ~Elf( );

	// C++11 make the class non-copElfable
	Elf( const Elf& ) = delete;
	Elf& operator=( const Elf& ) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	//virtual void BeginContact(PhElfsicsActor *actThisPtr, PhElfsicsActor *actOtherPtr); 
	//virtual void EndContact(PhElfsicsActor *actThisPtr, PhElfsicsActor *actOtherPtr);   
	//virtual void ContactImpulse(PhElfsicsActor *actThisPtr, double impulse);
	void Paint();
	void Tick(double deltaTime);
	DOUBLE2 GetPosition();
	void ResetPosition();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	PhysicsActor * m_ActElfPtr = nullptr;
	const static int ACTOR_HEIGHT = 100;
	const static int ACTOR_WIDTH = 40;
	DOUBLE2 m_SpawnPos, m_Position;
	double m_Time;
	
	enum class State {
		STANDING,
		JUMPING, 
		WALKING,
		AIMING,
		JUMPANDAIM,
		WALKANDAIM,
	};

	State m_State;
};

 
