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
	Skelethon(DOUBLE2 pos, Bitmap * bmpPtr); 
	virtual ~Skelethon( );

	// C++11 make the class non-copSkelethonable
	Skelethon( const Skelethon& ) = delete;
	Skelethon& operator=( const Skelethon& ) = delete;

	virtual void Tick(double deltaTime);
	/*void Fly();
*/
	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	//virtual void EndContact(PhSkelethonsicsActor *actThisPtr, PhSkelethonsicsActor *actOtherPtr);   
	//virtual void ContactImpulse(PhSkelethonsicsActor *actThisPtr, double impulse);


public: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static const DOUBLE2 IMPULSE;
	int m_Direction = 1;

};

 
