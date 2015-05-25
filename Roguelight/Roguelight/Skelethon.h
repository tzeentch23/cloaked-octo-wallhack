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
#include "Elf.h"
//#include "ContactListener.h"
//-----------------------------------------------------
// Skelethon Class									
//-----------------------------------------------------
class Skelethon : public Enemy
{
public:
	Skelethon(DOUBLE2 pos, int cols, Bitmap * bmpPtr); 
	virtual ~Skelethon( );

	// C++11 make the class non-copSkelethonable
	Skelethon( const Skelethon& ) = delete;
	Skelethon& operator=( const Skelethon& ) = delete;

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
	static const DOUBLE2 IMPULSE;
	static const int MAX_DISTANCE;
	double m_ImpulseTime;

};

 
