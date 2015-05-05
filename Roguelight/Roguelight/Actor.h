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
	virtual ~Actor( );

	// C++11 make the class non-copActorable
	Actor( const Actor& ) = delete;
	Actor& operator=( const Actor& ) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);   
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
	virtual void Paint();
	void Tick(double deltaTime);
	DOUBLE2 GetPosition();
	virtual int getSpriteRow();
	virtual int getSpriteCol();
	 
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
	int m_Health;
	int FRAMERATE;
	int NR_COLS;
	int NR_ROWS;
	int ACTOR_HEIGHT;
	int ACTOR_WIDTH;
	DOUBLE2 m_SpawnPos, m_Position;
	
	enum class Type {
		ELF,
		ENEMY, 
	};

	Type m_Type;
};

 
