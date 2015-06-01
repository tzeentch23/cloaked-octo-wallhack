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
// Door Class									
//-----------------------------------------------------
class Door //: public ContactListener
{
public:
	Door(DOUBLE2 pos);
	virtual ~Door( );

	// C++11 make the class non-copDoorable
	Door( const Door& ) = delete;
	Door& operator=( const Door& ) = delete;

	
	void Paint();
	void ResetPos();
	void Tick(double deltaTime);

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform;
	double m_Scale = 1;
	double m_Angle = 0;
	PhysicsActor * m_ActDoorPtr = nullptr, * m_ActTriggerPtr = nullptr;
	static Bitmap * m_BmpDoorPtr;
	static int m_InstanceCounter;
	double m_ActorWidth, m_ActorHeight;
	DOUBLE2 m_SpawnPos;
	
};

 
