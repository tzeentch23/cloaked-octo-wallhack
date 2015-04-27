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
		ARROWS,

	};

	Collectible(DOUBLE2 pos, Type type);
	virtual ~Collectible( );
	
	// C++11 make the class non-copCollectibleable
	Collectible( const Collectible& ) = delete;
	Collectible& operator=( const Collectible& ) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);   
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
	void Paint();
	void Tick();

	

public: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	 Type m_Type;
	 PhysicsActor *m_ActCollectPtr = nullptr;
	 static Bitmap * m_BmpHeartPtr;
	 static Bitmap * m_BmpArrowPtr;
	 static Bitmap * m_BmpCoinPtr;
	
};

 
