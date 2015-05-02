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
#include "Collectible.h"


//-----------------------------------------------------------------
// Roguelight Class																
//-----------------------------------------------------------------
class Elf;
class Moss;
class Spike;
class Collectible;
class Enemy;
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
	//opravi gi tezi, koemntiraj gi primerno.. shte se vyrna sled malko
	virtual void GameInitialize(GameSettings &gameSettings);
	virtual void GameStart();				
	virtual void GameEnd();
	virtual void GameTick(double deltaTime);
	virtual void GamePaint(RECT rect);

	// -------------------------
	// Public Member functions
	// -------------------------
	void Camera();
	void LoadMoss();
	void LoadSpike();
	void LoadCollectible(Collectible::Type type, String & fileName, std::vector<Collectible *> & arrayPtr);
	void LoadShadyguys();
	void LoadSkelethons();

private:
	// -------------------------
	// Private Member functions
	// -------------------------
	
	
	// -------------------------
	// Private Datamembers
	// -------------------------
	PhysicsActor * m_ActFloorPtr = nullptr, *m_ActLevelPtr = nullptr;
	Elf * m_ElfPtr = nullptr;
	std::vector<Moss *> m_MossArr;
	std::vector<Spike *> m_SpikeArr;
	std::vector<Collectible *> m_ArrowArr;
	std::vector<Collectible *> m_CoinArr;
	std::vector<Collectible *> m_HeartArr;

	std::vector<Enemy *> m_Enemies;
	Bitmap * m_BmpLvlPtr = nullptr;

	MATRIX3X2 matCamera, matCamRotate, matCamTranslate, 
		matCamScale, matPivot, matCamWorldTransform;
	DOUBLE2 m_CameraPos, m_ElfPos;
	double m_CameraAngle = 0;
	double m_CameraScale = 1;
	//ia pokaji txt-to
	//ami ok sa, triabva da trygvam, no spored men e ok load-a.. ok 
	//samo sekunda
	struct CameraDimension {
		DOUBLE2 topLeft;
		DOUBLE2 bottomRight;
	};

	CameraDimension m_CameraDimension;
	DOUBLE2 cameraSize;
	bool m_IsPhysicsDebudRendering = false;
	double m_Width = W, m_Height = H;

	Bitmap * m_ShadyGuyBmpPtr = nullptr;

	static const int W = 400;
	static const int H = 400;
	static const int MIN_LEFT = W / 2;
	static const int MAX_RIGHT = W / 2;
};
