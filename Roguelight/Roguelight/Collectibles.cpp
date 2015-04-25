//-----------------------------------------------------
// Name: Kirkorova 
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "Collectibles.h"
#include "Elf.h"
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Collectibles::Collectibles()
{
	// nothing to create
	// m_ActCirclePtr->AddContactListener(this);
}

Collectibles::~Collectibles()
{
	// nothing to destroCollectibles
}

void Collectibles::Tick()
{
	
}
void Collectibles::Paint()
{


}
//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Collectibles::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	//tuka pochnah  neshto ama ne moga da se dokopam do metodite na elfa 
	if (actThisPtr->IsOverlapping(actOtherPtr))
	{
		if (m_Type == Type::COINS)
		{
			//ediniat actor e vsyhtnost elf-a nali?da actotherptr
			//a zashto se opitvash tuk da go pravish tova?
			// poneje vyv elfa begin contact vaji za vsichki obekti
			//sekunda samo..
			//taka tuk variantite sa niakolko, no tozi kojto si izbrala moje bi e e naj-dobria..
			//stava.. no v takyv sluchaj triabva da si paziwsh n[kyde statichna
			//instanciata na elfa..
			//tova e variant 1 - i taka vinagi mojesh da dokopash elfa, no na men mi se struva che shte ima i drug nachin. sus HUD class?
			//kakvo e HUD class? user interface vse edno tam kydeto ti pishe kolko health i
			// ammo da be da
			//no ne, na teb ne ti e problema kyde shte trupash parite
			//a da  imash contact-a mejdu elfa i vsichko ostanalo, nali?da
			//vie za dynamic cast uchili li ste? ne ama ne prechi
			//iasno, no chakaj da pomislia za drug variant..
			//toj contactva collectables i oshte kakvo? ste emi kvoto ima (samo elfa she se contactva s tqh)
			//
		}
		if (m_Type == Type::ARROWS)
		{

		}
		if (m_Type == Type::HEARTS)
		{

		}
	}
}

void Collectibles::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Collectibles::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}


