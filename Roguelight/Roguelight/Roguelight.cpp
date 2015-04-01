//-----------------------------------------------------------------
// Game File
// C++ Source - Roguelight.cpp - version v2_16 jan 2015
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------
#include "stdafx.h"		// this include must be the first include line of every cpp file (due to using precompiled header)
#include "Elf.h"	
//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Roguelight.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//-----------------------------------------------------------------
// Roguelight methods																				
//-----------------------------------------------------------------

Roguelight::Roguelight()
{
	// nothing to create
}

Roguelight::~Roguelight()																						
{
	// nothing to destroy
}

void Roguelight::GameInitialize(GameSettings &gameSettings)
{
	gameSettings.SetWindowTitle(String("Roguelight - Name, First name - group"));
	gameSettings.SetWindowWidth(400);
	gameSettings.SetWindowHeight(400);
	gameSettings.EnableConsole(false);
	gameSettings.EnableAntiAliasing(false);
}

void Roguelight::GameStart()
{
	DOUBLE2 elfSpawn(20, 20);
	m_ElfPtr = new Elf(elfSpawn);
	m_ActFloorPtr = new PhysicsActor(DOUBLE2(GAME_ENGINE->GetWidth()/2, GAME_ENGINE->GetHeight() - 10), 0, BodyType::STATIC);
	m_ActFloorPtr->AddBoxShape(GAME_ENGINE->GetHeight(), 20, 0, 0, 0);

	// Insert the code that needs to be executed at the start of the game
}

void Roguelight::GameEnd()
{
	// Insert the code that needs to be executed at the closing of the game
}

void Roguelight::GameTick(double deltaTime)
{
	m_ElfPtr->Tick(deltaTime);
	GAME_ENGINE->EnablePhysicsDebugRendering(true);
	// Insert the code that needs to be executed, EXCEPT for paint commands (see next method)
}

void Roguelight::GamePaint(RECT rect)
{
	m_ElfPtr->Paint();
	// Insert the code that needs to be executed each time a new frame needs to be drawn to the screen
	// Technical note: engine uses double buffering when the gamecycle is running

}



