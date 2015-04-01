//-----------------------------------------------------------------
// Game File
// C++ Source - Roguelight.h - version v2_16 jan 2015
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Student data
// Name:Kirkorova Angelika
// Group:1DAE2
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Resource.h"	
#include "AbstractGame.h"

//-----------------------------------------------------------------
// Roguelight Class																
//-----------------------------------------------------------------
class Elf;
class Roguelight : public AbstractGame
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	Roguelight();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Roguelight();

	// C++11 make the class non-copyable
	Roguelight(const Roguelight&) = delete;
	Roguelight& operator=(const Roguelight&) = delete;

	//---------------------------
	// General Methods
	//---------------------------

	virtual void GameInitialize(GameSettings &gameSettings);
	virtual void GameStart();				
	virtual void GameEnd();
	virtual void GameTick(double deltaTime);
	virtual void GamePaint(RECT rect);

	// -------------------------
	// Public Member functions
	// -------------------------

private:
	// -------------------------
	// Private Member functions
	// -------------------------

	// -------------------------
	// Private Datamembers
	// -------------------------
	PhysicsActor * m_ActFloorPtr = nullptr;
	Elf * m_ElfPtr = nullptr;

};
