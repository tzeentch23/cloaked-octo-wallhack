#pragma once
//-----------------------------------------------------
// Name:
// First name:
// Group: 1DAE.
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

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);   
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
	void Paint();

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
	
};

 
