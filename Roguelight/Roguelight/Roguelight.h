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
class Camera;
class Moss;
class Spike;
class Door;
class Collectible;
class Enemy;
class Cthulhu;
class HUD;
class Bullet;
class Lamp;
class StartScreen;
class PauseScreen;
class Session;
class Firefly;
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
	void ParseFirefly(std::wstring & item);
	void ParseMoss(std::wstring & item);
	void ParseSpike(std::wstring & item);
	void ParseAmmo(Collectible::Type type, std::wstring & item, std::vector<Collectible *> & arrayPtr);
	void ParseHeart(Collectible::Type type, std::wstring & item, std::vector<Collectible *> & arrayPtr);
	void ParseShadyguy(std::wstring & item);
	void ParseSkelethon(std::wstring & item);
	void ParseDoor(std::wstring & item);
	void ParseLamp(std::wstring & item);
	void ParseElf(std::wstring & item);
	void ParseCthulhu(std::wstring & item);
	void ParseItem(std::wstring & item);
	void InitGame();
	void CheckHitEnemy(PhysicsActor * actor);
	DOUBLE2 ParsePosition(std::wstring & item);
	void Start();
	void Reset();
	void Quit();
	Camera * GetCamera();
	void DrawBgRect(DOUBLE2 pos, int r);

	PhysicsActor * GetLevelActor();

	static Roguelight * GAME;
	static Bitmap *m_BmpDeadTextPtr;

private:
	// -------------------------
	// Privaalte Member functions
	// -------------------------

	void fixElfPos();
	// -------------------------
	// Private Datamembers
	// -------------------------
	StartScreen * m_StartScrPtr = nullptr;
	PauseScreen * m_PauseScrPtr = nullptr;
	Session * m_Session;
	PhysicsActor * m_ActFloorPtr = nullptr, *m_ActLevelPtr = nullptr;
	Camera * m_CameraPtr = nullptr;
	Bitmap *m_BmpGodModePtr = nullptr;

	enum class DrawMode
	{
		BITMAP,
		PHYSICS,
		ALL
	};
	DrawMode m_DrawMode = DrawMode::BITMAP;
	
	Elf * m_ElfPtr = nullptr;
	Cthulhu * m_CthulhuPtr = nullptr;

	std::vector<Moss *> m_MossArr;
	std::vector<Spike *> m_SpikeArr;
	std::vector<Door *> m_DoorArr;
	std::vector<Collectible *> m_AmmoArr;
	std::vector<Collectible *> m_CoinArr;
	std::vector<Collectible *> m_HeartArr;
	std::vector<Collectible *> m_LootArr;
	std::vector<Enemy *> m_ShadyguyArr;
	std::vector<Enemy *> m_SkelethonArr;
	std::vector<HUD *> m_HudArr;
	std::vector<Bullet *> m_BulletArr;
	std::vector<Lamp*> m_LampArr;
	std::vector<Firefly*> m_FireflyArr;
	Bitmap  * m_BmpLvlPtr = nullptr;
	Bitmap  * m_BmpLvlDarkPtr = nullptr;
	bool IsEnemyHit(Enemy * enemy, PhysicsActor * actor);
	void NewCoin(DOUBLE2 pos);

	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform;
	double m_Angle = 0;
	double m_Scale = 0.5;
	DOUBLE2 m_Translate, m_CameraPos, m_ElfPos, m_HealthPos, m_CoinsPos, m_AmmoPos;

	double m_ShootTime = 0;

	Bitmap * m_BmpShadyGuyPtr = nullptr,
		*m_BmpSkelethonPtr = nullptr,
		*m_BmpCthulhuPtr = nullptr,
		*m_BmpFireflyPtr = nullptr;
	Sound * m_GameSoundPtr = nullptr;
	RECT m_BgRect;

};
