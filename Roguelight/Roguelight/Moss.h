#pragma once
//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

//#include "ContactListener.h"
//-----------------------------------------------------
// Moss Class									
//-----------------------------------------------------
class Moss //: public ContactListener
{
public:
	Moss(DOUBLE2 pos);
	virtual ~Moss( );

	// C++11 make the class non-copMossable
	Moss( const Moss& ) = delete;
	Moss& operator=( const Moss& ) = delete;

	
	void Paint();
	void ResetPos();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform;
	double m_Scale = 1;
	double m_Angle = 0;
	PhysicsActor * m_ActMossPtr = nullptr;
	static Bitmap * m_BmpMossPtr;
	static int m_InstanceCounter;
	double m_ActorWidth, m_ActorHeight;
	DOUBLE2 m_SpawnPos;
	
};

 
