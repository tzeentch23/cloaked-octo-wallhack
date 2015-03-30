#pragma once

//-----------------------------------------------------
// ContactListener Class									
//-----------------------------------------------------
class ContactListener
{
public:
	ContactListener( );
	virtual ~ContactListener( );

	// C++11 make the class non-copyable
	ContactListener( const ContactListener& ) = delete;
	ContactListener& operator=( const ContactListener& ) = delete;

	//! BeginContact is called by the GameEngine when contact between a trigger ContactListener and another ContactListener has begun.
	//! @param contactlistenerPtr is the pointer of the other listener who began contact.
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr) = 0; //pure virtual

	//! BeginContact is called by the GameEngine when contact between a trigger ContactListener and another ContactListener has ended.
	//! @param contactlistenerPtr is the pointer of the other listener who ended contact.
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr) = 0; //pure virtual

	//! ContactImpulse in called by the GameEngine when the Listener had contact.
	//! @param impulse is calculated by Box2D to push the actors out of each other. The bigger the impulse, the harder they have hit each other
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse) = 0; //pure virtual
};

 
