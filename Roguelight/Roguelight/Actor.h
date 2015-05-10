#pragma once
//-----------------------------------------------------
// Name:Angelika
// First name:Kirkorova
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

#include "ContactListener.h"
//-----------------------------------------------------
// Actor Class									
//-----------------------------------------------------
class Actor : public ContactListener
{
public:
	Actor::Actor(DOUBLE2 spawnPos, int frameRate, int nrCols, int nrRows, int width, int height);
	virtual ~Actor();

	// C++11 make the class non-copActorable
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
	virtual void Paint();
	void Tick(double deltaTime);
	DOUBLE2 GetPosition();
	virtual int GetSpriteRow();
	virtual int GetSpriteCol();
	virtual PhysicsActor * GetPhysicsActor();
	
	//pyrvo premestih niakoi metodi ot elfa tuk, zashtoto sa si obshti za vsichki gadini
	virtual void IncreaseHealth();
	virtual void DecreaseHealth();
	virtual int GetHealth();
	virtual bool IsAlive();
	virtual void Reset();
	virtual int GetInitialHealth() = 0; //tozi e abstrakten, polzvam go v reset-a.. i osven tova vseki lkas si go vika v konstukrora za da si initne health-a, nishto interesno do tuk, nali?mhm
public:
	void ResetPosition();
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform;
	PhysicsActor * m_ActActorPtr = nullptr;
	Bitmap * m_BmpActorPtr = nullptr;
	double m_Time = 0.0;
	int m_FrameNr = 0;
	int m_Health, FRAMERATE, NR_COLS, NR_ROWS, ACTOR_HEIGHT, ACTOR_WIDTH;
	DOUBLE2 m_SpawnPos, m_Position;

};


