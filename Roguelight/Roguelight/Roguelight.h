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
#include <map>


//-----------------------------------------------------------------
// Roguelight Class																
//-----------------------------------------------------------------
class Elf;
class Moss;
class Spike;
class Collectible;
class Enemy;
class HUD;
class Bullet;
class Lamp;
class StartScreen;
class PauseScreen;
class Session;
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
	void ParseMoss(std::wstring & item);
	void ParseSpike(std::wstring & item);
	void ParseAmmo(Collectible::Type type, std::wstring & item, std::vector<Collectible *> & arrayPtr);
	void ParseCoin(Collectible::Type type, std::wstring & item, std::vector<Collectible *> & arrayPtr);
	void ParseHeart(Collectible::Type type, std::wstring & item, std::vector<Collectible *> & arrayPtr);
	void ParseShadyguy(std::wstring & item);
	void ParseSkelethon(std::wstring & item);
	void ParseLamp(std::wstring & item);
	void ParseElf(std::wstring & item);
	void ParseItem(std::wstring & item);
	void InitGame();
	void CheckHitEnemy(PhysicsActor * actor);
	DOUBLE2 ParsePosition(std::wstring & item);
	DOUBLE2 GetCameraOrigin();
	DOUBLE2 GetCameraSize();
	void Start();
	
	PhysicsActor * GetLevelActor();

	MATRIX3X2 matCamera, matCamRotate, matCamTranslate,
		matCamScale, matPivot, matCamWorldTransform;

	static Roguelight * GAME;
private:
	// -------------------------
	// Privaalte Member functions
	// -------------------------


	// -------------------------
	// Private Datamembers
	// -------------------------
	StartScreen * m_StartScrPtr = nullptr;
	PauseScreen * m_PauseScrPtr = nullptr;
	Session * m_Session;
	PhysicsActor * m_ActFloorPtr = nullptr, *m_ActLevelPtr = nullptr;
	Elf * m_ElfPtr = nullptr;
	std::vector<Moss *> m_MossArr;
	std::vector<Spike *> m_SpikeArr;
	std::vector<Collectible *> m_AmmoArr;
	std::vector<Collectible *> m_CoinArr;
	std::vector<Collectible *> m_HeartArr;
	std::vector<Collectible *> m_LootArr;
	std::vector<Enemy *> m_ShadyguyArr;
	std::vector<Enemy *> m_SkelethonArr;
	std::vector<HUD *> m_HudArr;
	std::vector<Bullet *> m_BulletArr;
	std::vector<Lamp*> m_LampArr;
	Bitmap  * m_BmpLvlPtr = nullptr;
	bool IsEnemiyHit(std::vector<Enemy *> & enemies, PhysicsActor * actor);
	void NewCoin(DOUBLE2 pos);

	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform;
	double m_Angle = 0;
	double m_Scale = 0.5;
	DOUBLE2 m_Translate, m_CameraPos, m_ElfPos, m_HealthPos, m_CoinsPos, m_AmmoPos;
	double m_CameraAngle = 0;
	double m_CameraScale = 0.7;

	double m_ShootTime = 0;
	struct CameraDimension {
		DOUBLE2 topLeft;
		DOUBLE2 bottomRight;
	};

	CameraDimension m_CameraDimension;
	DOUBLE2 m_CameraSize;
	bool m_IsPhysicsDebudRendering = false;
	double m_Width = W, m_Height = H;

	Bitmap * m_BmpShadyGuyPtr = nullptr,
		*m_BmpSkelethonPtr = nullptr;

	static const int W = 800;
	static const int H = 600;
	static const int MIN_LEFT = W / 2;
	static const int MAX_RIGHT = W / 2;

};
