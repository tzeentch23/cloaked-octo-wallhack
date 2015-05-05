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
	m_Health = 5;
	m_ActActorPtr = new PhysicsActor(m_SpawnPos, 0, BodyType::DYNAMIC);
	m_ActActorPtr->AddBoxShape(ACTOR_WIDTH, ACTOR_HEIGHT, 0.0, 0.2, 0.2);
	m_ActActorPtr->SetFixedRotation(true);
	//m_ActActorPtr->SetTrigger(false);
	m_ActActorPtr->SetGravityScale(1);
	m_ActActorPtr->AddContactListener(this);
}

Actor::~Actor()
{
	delete m_ActActorPtr;
	m_ActActorPtr = nullptr;
//	delete m_BmpActorPtr;
//	m_BmpActorPtr = nullptr;
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
	if (m_Time>(1.0/FRAMERATE))
	{
		++m_FrameNr;
		m_FrameNr %= NR_COLS* NR_ROWS;
		//m_FrameNr = 0;
		m_Time = 0;
	}
}

int Actor::getSpriteRow()
{
	return m_FrameNr / NR_COLS;
}

int Actor::getSpriteCol()
{
	return m_FrameNr % NR_COLS; 
}

DOUBLE2 Actor::GetPosition()
{
	DOUBLE2 posActor = m_ActActorPtr->GetPosition();
	return posActor;
}

void Actor::ResetPosition()
{
	m_ActActorPtr->SetPosition(DOUBLE2(GAME_ENGINE->GetWidth() / 2, GAME_ENGINE->GetHeight() / 2));
	m_ActActorPtr->SetAngle(0.0);
	m_ActActorPtr->SetAngularVelocity(0.0);
	m_ActActorPtr->SetLinearVelocity(DOUBLE2(0, 0));
}

void Actor::Paint() 
{
	int spriteWidth = m_BmpActorPtr->GetWidth() / NR_COLS;
	int spriteHeight = m_BmpActorPtr->GetHeight() / NR_ROWS;
	
	DOUBLE2 bitmapPos(m_ActActorPtr->GetPosition().x - (spriteWidth / 2),
		m_ActActorPtr->GetPosition().y - (spriteHeight / 2));

	matTranslate.SetAsTranslate(bitmapPos);
	matRotate.SetAsRotate(0);
	matRotate.SetAsScale(1);
	matWorldTransform = matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);
	GAME_ENGINE->SetBitmapInterpolationModeNearestNeighbor();

	DOUBLE2 currentPos = m_ActActorPtr->GetPosition();
	DOUBLE2 spritePos(currentPos.x - (m_BmpActorPtr->GetWidth() / 12),
		currentPos.y - (m_BmpActorPtr->GetHeight() / 10));
	int col = getSpriteCol();
	int row = getSpriteRow(); 
	int cropX = spriteWidth* col;
	int cropY = spriteHeight* row;

	RECT spriteElf;
	spriteElf.top = cropY;
	spriteElf.bottom = cropY + spriteHeight;
	spriteElf.left = cropX;
	spriteElf.right = cropX + spriteWidth;
	
	GAME_ENGINE->DrawBitmap(m_BmpActorPtr,  spriteElf);

}