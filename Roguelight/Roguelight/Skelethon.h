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
	virtual int GetImpulseForce();
public: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static const DOUBLE2 IMPULSE;
	static const int MAX_DISTANCE;
	double m_ImpulseTime;

};//ok de stava li samo da mahnem damage-a i da gi ostavim taka che nqmam vreme. koe da mahnem? ami kato se udrq v elfa i vzima health
//ne mojem da go mahnem of 
//imash ghost, kojto po niakakva prichina go precakva.. triabva da se napravi izcialo nanovo - da e static i triger i da si shava podobno na tova.. no po-razlichno..


 
