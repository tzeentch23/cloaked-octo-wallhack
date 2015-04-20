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
	void Camera();

private:
	// -------------------------
	// Private Member functions
	// -------------------------
	
	
	// -------------------------
	// Private Datamembers
	// -------------------------
	PhysicsActor * m_ActFloorPtr = nullptr, *m_ActLevelPtr = nullptr;
	Elf * m_ElfPtr = nullptr;
	Bitmap * m_BmpLvlPtr = nullptr;

	MATRIX3X2 matCamera, matCamRotate, matCamTranslate, 
		matCamScale, matPivot, matCamWorldTransform;
	DOUBLE2 m_CameraPos;
	double m_CameraAngle = 0;
	double m_CameraScale = 1;

	struct CameraDimension {
		DOUBLE2 topLeft;
		DOUBLE2 bottomRight;
	};

	CameraDimension m_CameraDimension;
	DOUBLE2 cameraSize;
	
	double m_Width = W, m_Height = H;

	static const int W = 400;
	static const int H = 400;
	static const int MIN_LEFT = W / 2;
	static const int MAX_RIGHT = W / 2;
};
