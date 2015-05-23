#pragma once
//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Skelethon.h"
#include "Elf.h"
//#include "ContactListener.h"
//-----------------------------------------------------
// Cthulhu Class									
//-----------------------------------------------------
class Cthulhu : public Skelethon
{
public:
	Cthulhu(DOUBLE2 pos, int cols, Bitmap * bmpPtr);
	virtual ~Cthulhu();

	// C++11 make the class non-copCthulhuable
	Cthulhu(const Cthulhu&) = delete;
	Cthulhu& operator=(const Cthulhu&) = delete;

	//virtual void Tick(double deltaTime);

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual int GetInitialHealth();
public:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	
};


