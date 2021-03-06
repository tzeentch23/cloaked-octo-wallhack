#pragma once
//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

#include "ContactListener.h"
#include "Elf.h"
//-----------------------------------------------------
// Collectible Class									
//-----------------------------------------------------
class Collectible : public ContactListener
{
public:
	enum Type
	{
		COINS,
		HEARTS,
		AMMO,

	};

	Collectible(DOUBLE2 pos, Type type);
	virtual ~Collectible();

	// C++11 make the class non-copCollectibleable
	Collectible(const Collectible&) = delete;
	Collectible& operator=(const Collectible&) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
	void Paint();
	void Tick(double deltaTime);
	bool IsConsumed();
	void ResetPos();


public:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	DOUBLE2 m_InitialPosition;
	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform;
	double m_Scale = 1;
	double m_Angle = 0;
	double m_Time;
	int m_FrameNr;
	static int m_InstanceCounter;
	Type m_Type;
	PhysicsActor *m_ActCollectPtr = nullptr;
	static Bitmap * m_BmpHeartPtr;
	static Bitmap * m_BmpAmmoPtr;
	static Bitmap * m_BmpCoinPtr;

	bool m_IsConsumed = false;

	static const int NR_AMMO_COLS = 3;
	static const int NR_AMMO_ROWS = 1;
	static const int NR_COINS_COLS = 3;
	static const int NR_COINS_ROWS = 1;
	static const int NR_HEARTS_COLS = 4;
	static const int NR_HEARTS_ROWS = 1;
	static const int FRAMERATE = 3;
	static const int MAX_DISTANCE = 300;

	DOUBLE2 m_CoinVelocity = DOUBLE2(0, 50);
};


