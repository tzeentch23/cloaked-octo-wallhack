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
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void Reset();
	void Reload();
	void DecreaseAmmo();
	void IncreaseCoins();
	void IncreaseHealth();
	virtual void DecreaseHealth(); 
	virtual int GetSpriteRow();
	static Elf * player;
	int GetDirection();
	void PlayGodmodeSound();

public:
	static Elf * GetPlayer();
	 int GetAmmo();
	 int GetCoins();
	 virtual int GetInitialHealth();
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	int m_Ammo, m_Coins;
	
	enum class State {
		STANDING,
		JUMPING, 
		WALKING,
		AIMING,
		JUMPANDAIM,
		WALKANDAIM,
		DEAD,
		GODMODE,	
	};
	Bitmap *m_BmpGodModePtr = nullptr;
	bool m_GodMode = false;
	State m_State;
	static const int MAX_AMMO = 8;
	static const int MAX_HEALTH = 8;
	int m_Direction = 1;
	int m_NrOfJumps = 0;
	double m_JumpTime = 0;
	double m_SoundTime = 0;
	Sound * m_DecreaseHealthSndPtr = nullptr, 
			*m_GetCoinSndPtr = nullptr, 
			*m_IsDeadSndPtr = nullptr,
			*m_GodmodeSndPtr = nullptr;
};

 
