//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "Skelethon.h"
#include "Enemy.h"
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Skelethon::Skelethon(DOUBLE2 pos, Bitmap * bmpPtr) : Enemy(pos, 5, 3, 1, 30, 50, bmpPtr)
{

}

Skelethon::~Skelethon()
{
	delete m_ActActorPtr;
	m_ActActorPtr = nullptr;
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
//void Skelethon::BeginContact(PhSkelethonsicsActor *actThisPtr, PhSkelethonsicsActor *actOtherPtr)
//{
//
//}
//
//void Skelethon::EndContact(PhSkelethonsicsActor *actThisPtr, PhSkelethonsicsActor *actOtherPtr)
//{
//
//}
//
//void Skelethon::ContactImpulse(PhSkelethonsicsActor *actThisPtr, double impulse)
//{
//
//}
//
//void Shadyguy::Tick(double deltaTime)
//{
//
//}
//void Skelethon::Follow(DOUBLE2 posActor)
//{
//	/*	double difX = posActor.x - m_ActSkelethonPtr->GetPosition().x;
//		double difY = posActor.y - m_ActSkelethonPtr->GetPosition().y;
//	if ((difX<300) && (difY<300))
//	{
//		for (size_t i = 0; i < difX; i++)
//		{
//			for (size_t j = 0; j < difY; j++)
//			{
//				m_ActSkelethonPtr->SetLinearVelocity(DOUBLE2(5, 5));
//			}
//		}
//	}
//*/
//}

void Skelethon::Tick(double deltaTime)
{
	Enemy::Tick(deltaTime);
}