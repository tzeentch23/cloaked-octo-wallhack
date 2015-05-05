#pragma once
//-----------------------------------------------------
// Name:Angelika
// First name:Kirkorova
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

#include "Actor.h"
//-----------------------------------------------------
// Elf Class									
//--------------	---------------------------------------
class Elf : public Actor
{
public:
	Elf(DOUBLE2 spawnPos);
	virtual ~Elf( );

	// C++11 make the class non-copElfable
	Elf( const Elf& ) = delete;
	Elf& operator=( const Elf& ) = delete;

	virtual void Paint() ;
	virtual void Tick(double deltatime);
	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	void IncreaseHealth();
	void DecreaseHealth();
	void IncreaseAmmo();
	void DecreaseAmmo();
	void IncreaseMoney();
	
	virtual int getSpriteRow();
	static Elf * player;
	 
public:
	static Elf * getPlayer();
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	//PhysicsActor * m_ActElfPtr = nullptr;
	//Bitmap * m_BmpElfPtr = nullptr;
	//double m_Time = 0.0;
	//int m_FrameNr = 0;	
	int m_Ammo, m_Money;
	/*
	const static int FRAMERATE = 25;
	const static int NR_COLS = 6;
	const static int NR_ROWS = 5;
	const static int ACTOR_HEIGHT = 35;
	const static int ACTOR_WIDTH = 20;
	*/
	DOUBLE2 m_SpawnPos, m_Position;
	
	
	enum class State {
		STANDING,
		JUMPING, 
		WALKING,
		AIMING,
		JUMPANDAIM,
		WALKANDAIM,
		DEAD,
	};

	State m_State;
};

 
