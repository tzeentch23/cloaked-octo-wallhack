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
// Collectibles Class									
//-----------------------------------------------------
class Collectibles : public ContactListener
{
public:
	Collectibles( );
	virtual ~Collectibles( );

	// C++11 make the class non-copCollectiblesable
	Collectibles( const Collectibles& ) = delete;
	Collectibles& operator=( const Collectibles& ) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);   
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
	void Paint();
	void Tick();


private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	enum class Type
	{
		COINS,
		HEARTS,
		ARROWS,

	};
	Type m_Type;
};

 
