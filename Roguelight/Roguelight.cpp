//-----------------------------------------------------------------
// Game File
// C++ Source - Roguelight.cpp - version v2_16 jan 2015
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------
#include "stdafx.h"		// this include must be the first include line of every cpp file (due to using precompiled header)
	
//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Roguelight.h"					
#include "Elf.h"

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
	gameSettings.SetWindowTitle(String("Roguelight - Kirkorova Angelika, 1DAE2"));
	gameSettings.SetWindowWidth(842);
	gameSettings.SetWindowHeight(480);
	gameSettings.EnableConsole(false);
	gameSettings.EnableAntiAliasing(false);
}

void Roguelight::GameStart()
{
	DOUBLE2 elfSpawnPosition(200, 200);
	m_ElfPtr = new Elf(elfSpawnPosition);

	/*std::vector <DOUBLE2> floorArr;
	DOUBLE2 p1 {0, 400};
	DOUBLE2 p2 {double(GAME_ENGINE->GetWidth()), 400 };
	floorArr.push_back(p1);
	floorArr.push_back(p2);
	m_ActFloorPtr = new PhysicsActor(DOUBLE2(0, 0), 0, BodyType::STATIC);
	m_ActFloorPtr->AddChainShape(floorArr, floorArr.size());*/
	// Insert the code that needs to be executed at the start of the game
}

void Roguelight::GameEnd()
{
	// Insert the code that needs to be executed at the closing of the game
}

void Roguelight::GameTick(double deltaTime)
{
	if (GAME_ENGINE->IsKeyboardKeyPressed('P'))
	{
		m_IsPhysicsDebugRenderingOn = !m_IsPhysicsDebugRenderingOn;
		GAME_ENGINE->EnablePhysicsDebugRendering(m_IsPhysicsDebugRenderingOn);
	}
	m_ElfPtr->Tick(deltaTime);
	// Insert the code that needs to be executed, EXCEPT for paint commands (see next method)
}

void Roguelight::GamePaint(RECT rect)
{
	m_ElfPtr->Paint();
	// Insert the code that needs to be executed each time a new frame needs to be drawn to the screen
	// Technical note: engine uses double buffering when the gamecycle is running

}



