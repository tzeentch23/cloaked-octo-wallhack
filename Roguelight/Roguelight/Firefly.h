#pragma once
//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

#include "Shadyguy.h"
//-----------------------------------------------------
// Firefly Class									
//-----------------------------------------------------
class Firefly : public Shadyguy
{
public:
	Firefly(DOUBLE2 pos, int nrCols, int nrRows,Bitmap* bmp);
	virtual ~Firefly( );

	// C++11 make the class non-copFireflysable
	Firefly( const Firefly& ) = delete;
	Firefly& operator=( const Firefly& ) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	void Paint();
	void Tick(double deltaTime);
	void ResetPos();
	

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	DOUBLE2 m_SpawnPos;
	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform;
	double m_Scale = 1;
	double m_Angle = 0;
	PhysicsActor * m_ActFireflyPtr = nullptr;
	static int m_InstanceCounter;
	static const int NR_COLS = 8; 
	static const int NR_ROWS = 1;
};