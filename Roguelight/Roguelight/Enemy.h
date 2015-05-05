#pragma once
//-----------------------------------------------------
// Name: Kirkorova
// First name: Angelika
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

#include "Actor.h"
//-----------------------------------------------------
// Enemy Class									
//-----------------------------------------------------
class Enemy : public Actor
{
public:
	Enemy(DOUBLE2 spawnPos, int frameRate, int nrCols, int nrRows, int width, int height, Bitmap * bmpPtr);
	virtual ~Enemy( );

	// C++11 make the class non-copEnemyable
	Enemy( const Enemy& ) = delete;
	Enemy& operator=( const Enemy& ) = delete;
	virtual void Paint();
	virtual void Tick(double deltaTime);
	//virtual void Tick(double deltaTime) = 0; //no implementataion here..

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	//virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);   
	//virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);

protected: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	//int m_Health;
	//int m_FrameNr;
	//DOUBLE2 m_Position;
	//PhysicsActor * m_ActEnemyPtr = nullptr;
	//Bitmap * m_BmpEnemyPtr = nullptr;
	//double m_Time;
	//static const int ENEMY_WIDTH; 
	//static const int ENEMY_HEIGHT;
	//static const int FRAMERATE = 10;
	//static const int NR_COLS = 3;
	//static const int NR_ROWS = 1;	
};
 
