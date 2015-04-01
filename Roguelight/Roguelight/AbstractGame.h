//-----------------------------------------------------------------
// AbstractGame Object
// C++ Header - AbstractGame.h - version v2_16 jan 2015 
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//
// AbstractGame is the abstract class which defines the functions that a 
// game class can implement for use in the game engine
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Game Engine Object
// C++ Header - version v2_16 jan 2015 
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

#pragma once

class PhysicsActor;
class GameSettings;
//-----------------------------------------------------------------
// AbstractGame Class
//-----------------------------------------------------------------
class AbstractGame
{
public : 	
	AbstractGame() 
	{
		// nothing to create
	}

	virtual ~AbstractGame() 
	{
		// nothing to destroy
	}
	// C++11 make the class non-copyable

	AbstractGame(const AbstractGame&) = delete;
	AbstractGame& operator=(const AbstractGame&) = delete;

	virtual void GameInitialize(GameSettings &gameSettings) {}								// empty definition
	virtual void GameStart(void) {}																// empty definition
	virtual void GameEnd(void) {}																// empty definition
	virtual void GamePaint(RECT rect) {}														// empty definition
	virtual void GameTick(double deltaTime) {}													// empty definition
};