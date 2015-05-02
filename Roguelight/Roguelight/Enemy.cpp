//-----------------------------------------------------
// Name: Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------hahhhha
#include "Enemy.h"
#include "Skelethon.h"
#include "Shadyguy.h"
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Enemy::Enemy(DOUBLE2 pos, Bitmap * bmpPtr) : m_Position(pos), m_BmpEnemyPtr(bmpPtr)
{
	m_ActEnemyPtr = new PhysicsActor(pos, 0, BodyType::DYNAMIC); //s velocity-to triabva da stane..
}

Enemy::~Enemy()
{
	delete m_ActEnemyPtr;
	m_ActEnemyPtr = nullptr;
}
//nz
void Enemy::Paint()
{
	DOUBLE2 currentPos = m_ActEnemyPtr->GetPosition();
	DOUBLE2 spritePos(m_ActEnemyPtr->GetPosition().x - m_BmpEnemyPtr->GetWidth(),
		m_ActEnemyPtr->GetPosition().y - m_BmpEnemyPtr->GetHeight());
	int spriteWidth = m_BmpEnemyPtr->GetWidth() / NR_COLS;
	int spriteHeight = m_BmpEnemyPtr->GetHeight() / NR_ROWS;
	int col = m_FrameNr / NR_COLS;
	int row = NR_ROWS;


	int cropX = spriteWidth* col;
	int cropY = spriteHeight* row;

	GAME_ENGINE->DrawBitmap(m_BmpEnemyPtr, spritePos);
}


//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Enemy::BeginContact(PhysicsActor *actthisptr, PhysicsActor *actotherptr)
{
	m_Health -= 25;
}

void Enemy::EndContact(PhysicsActor *actthisptr, PhysicsActor *actotherptr)
{

}

void Enemy::ContactImpulse(PhysicsActor *actthisptr, double impulse)
{

}


