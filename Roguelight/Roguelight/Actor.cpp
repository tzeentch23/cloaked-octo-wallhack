//-----------------------------------------------------

// Name:Angelika
// First name:Kirkorova
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		

//---------------------------
// Includes
//---------------------------
#include "Actor.h"
#include "Elf.h"
#include "Roguelight.h"
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())
//---------------------------
// Constructor & Destructor
//---------------------------
Actor::Actor(DOUBLE2 spawnPos, int frameRate, int nrCols, int nrRows, int width, int height) : m_SpawnPos(spawnPos),
FRAMERATE(frameRate),
NR_COLS(nrCols),
NR_ROWS(nrRows),
ACTOR_HEIGHT(height),
ACTOR_WIDTH(width)
{
	m_ActActorPtr = new PhysicsActor(m_SpawnPos, 0, BodyType::DYNAMIC);
	m_ActActorPtr->AddBoxShape(ACTOR_WIDTH, ACTOR_HEIGHT, 0, 0.2, 1);
	m_ActActorPtr->SetFixedRotation(true);
	//m_ActActorPtr->SetTrigger(false);
	m_ActActorPtr->SetGravityScale(1);
	m_ActActorPtr->AddContactListener(this);
}

Actor::~Actor()
{
	delete m_ActActorPtr;
	m_ActActorPtr = nullptr;
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Actor::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Actor::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Actor::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}

void Actor::Tick(double deltatime)
{
	m_Time += deltatime;
	if (m_Time > (1.0 / FRAMERATE))
	{
		++m_FrameNr;
		m_FrameNr %= NR_COLS* NR_ROWS;
		m_Time = 0;
	}
}

int Actor::GetSpriteRow()
{
	return m_FrameNr / NR_COLS;
}

int Actor::GetSpriteCol()
{
	return m_FrameNr % NR_COLS;
}

DOUBLE2 Actor::GetPosition()
{
	DOUBLE2 posActor = m_ActActorPtr->GetPosition();
	return posActor;
}

void Actor::Paint()
{
	int spriteWidth = m_BmpActorPtr->GetWidth() / NR_COLS;
	int spriteHeight = m_BmpActorPtr->GetHeight() / NR_ROWS;

	DOUBLE2 bitmapPos(m_ActActorPtr->GetPosition().x - (spriteWidth/ 2),
		m_ActActorPtr->GetPosition().y - (spriteHeight / 2));
	if (m_Scale < 0)
	{
		bitmapPos.x += m_BmpActorPtr->GetWidth() / NR_COLS;
	}
	matTranslate.SetAsTranslate(bitmapPos);
	matRotate.SetAsRotate(0);
	matScale.SetAsScale(m_Scale, 1);
	matWorldTransform = matScale * matRotate* matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);
	GAME_ENGINE->SetBitmapInterpolationModeNearestNeighbor();

	DOUBLE2 currentPos = m_ActActorPtr->GetPosition();
	DOUBLE2 spritePos(currentPos.x - (m_BmpActorPtr->GetWidth() / 12),
		currentPos.y - (m_BmpActorPtr->GetHeight() / 10));
	int col = GetSpriteCol();
	int row = GetSpriteRow();
	int cropX = spriteWidth* col;
	int cropY = spriteHeight* row;

	RECT spriteRect;
	spriteRect.top = cropY;
	spriteRect.bottom = cropY + spriteHeight;
	spriteRect.left = cropX;
	spriteRect.right = cropX + spriteWidth;

	GAME_ENGINE->DrawBitmap(m_BmpActorPtr, spriteRect);

}

PhysicsActor * Actor::GetPhysicsActor()
{
	return m_ActActorPtr;
}

void Actor::DecreaseHealth()
{
	if (--m_Health <= 0) 
	{
		m_ActActorPtr->SetActive(false);
	}
}

int Actor::GetHealth()
{
	return m_Health;
}

bool Actor::IsAlive()
{
	return m_Health > 0;
}

void Actor::Reset()
{
	m_ActActorPtr->SetAngle(0.0);
	m_ActActorPtr->SetAngularVelocity(0.0);
	m_ActActorPtr->SetLinearVelocity(DOUBLE2(0, 0));
	m_ActActorPtr->SetPosition(m_SpawnPos);
	m_ActActorPtr->SetActive(true);
	m_Health = GetInitialHealth();
}