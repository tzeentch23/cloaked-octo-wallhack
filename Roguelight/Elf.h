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
	Elf(DOUBLE2 spawnposition);
	virtual ~Elf( );

	// C++11 make the class non-copElfable
	Elf( const Elf& ) = delete;
	Elf& operator=( const Elf& ) = delete;

	// -------------------------
	// Public member functions
	// -------------------------
	void Paint();
	void Tick(double deltatime);
	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	//virtual void BeginContact(PhElfsicsActor *actorPtr, ContactListener * otherContactlistenerPtr);
	//virtual void EndContact(PhElfsicsActor *actorPtr, ContactListener * otherContactlistenerPtr);
	
private: 
	// -------------------------
	// Private member functions
	// -------------------------

	// -------------------------
	// Private datamembers
	// -------------------------
	Bitmap  *m_BmpElfStandingPtr = nullptr,
			*m_BmpElfJumpingPtr = nullptr,
			*m_BmpElfShootingPtr = nullptr,
			*m_BmpElfDeadPtr = nullptr;
	PhysicsActor * m_ActElfPtr = nullptr;
	DOUBLE2 m_Position, m_SpawnPos;
	enum class State {
		STANDING,
		JUMPING,
		SHOOTING,
		DEAD,
	};
	static const int ACTOR_HEIGHT = 100;
	static const int ACTOR_WIDTH = 40;
};

 
