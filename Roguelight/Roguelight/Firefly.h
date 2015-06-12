#pragma once
//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

#include "Skelethon.h"
//-----------------------------------------------------
// Firefly Class									
//-----------------------------------------------------
class Firefly
{
public:
	Firefly(DOUBLE2 pos, Bitmap* bmp);
	virtual ~Firefly( );

	// C++11 make the class non-copFireflysable
	Firefly( const Firefly& ) = delete;
	Firefly& operator=( const Firefly& ) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	void Paint();
	void Tick(double deltaTime);
	DOUBLE2 GetPosition();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform;
	double m_Scale = 1;
	double m_Angle = 0;
	DOUBLE2 m_Position;
	static const int NR_COLS = 8; 
	static const int NR_ROWS = 1;
	static const int FRAMERATE = 5;
	Bitmap *m_BmpPtr = nullptr;
	PhysicsActor * m_ActFireflyPtr;
	int m_FrameNr = 0;
	double m_Time = 0.0;
};