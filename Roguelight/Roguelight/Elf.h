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
class Elf : public ContactListener
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
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);   
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
	void Paint();
	void Tick(double deltaTime);
	DOUBLE2 GetPosition();
	void ResetPosition();
	int IncreaseHealth(int health);
	int DecreaseHealth(int health);
	int IncreaseAmmo(int ammo);
	int DecreaseAmmo(int ammo);
	int IncreaseMoney(int money);
	int DecreaseMoney(int money);
	
	//tozi variant ne e naj-dobria no shte ti svyrshi rabota na pyrvo vreme//
	static Elf player;
	 
public: 
	static Elf * getPlayer();
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	PhysicsActor * m_ActElfPtr = nullptr;
	Bitmap * m_BmpElfPtr = nullptr;
	double m_Time = 0.0;
	int m_FrameNr = 0;	
	int m_Ammo, m_Health, m_Money;
	const static int FRAMERATE = 25;
	const static int NR_COLS = 6;
	const static int NR_ROWS = 5;
	const static int ACTOR_HEIGHT = 35;
	const static int ACTOR_WIDTH = 20;
	DOUBLE2 m_SpawnPos, m_Position;
	
	
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

 
