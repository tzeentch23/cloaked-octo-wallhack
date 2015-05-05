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
	void IncreaseCoins();
		
	virtual int GetSpriteRow();
	static Elf * player;
	 
public:
	static Elf * GetPlayer();
	 int GetAmmo();
	 int GetHealth();
	 int GetCoins();
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	int m_Ammo, m_Coins;
	
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

 
