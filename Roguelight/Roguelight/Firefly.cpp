//-----------------------------------------------------
// Name:Angelika
// First name:Kirkorova
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"	
#include "Elf.h"

//---------------------------
// Includes
//---------------------------
#include "Firefly.h"
#include "Shadyguy.h"
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
int Firefly::m_InstanceCounter = 0;

Firefly::Firefly(DOUBLE2 pos, int nrCols, int nrRows, Bitmap * bmpPtr) : Shadyguy(pos, nrRows, nrCols , bmpPtr)
{
	nrCols = NR_COLS;
	nrRows = NR_ROWS;
	m_SpawnPos = pos;
	++m_InstanceCounter;
	m_ActFireflyPtr = new PhysicsActor(pos, 0, BodyType::DYNAMIC);
	m_ActFireflyPtr->AddBoxShape(5, 5, 0.2, 0.9, 0);
	
}

Firefly::~Firefly()
{
	delete m_ActFireflyPtr;
	m_ActFireflyPtr = nullptr;
}

void Firefly::Paint()
{
	DOUBLE2 bitmapPos = DOUBLE2(m_ActFireflyPtr->GetPosition().x - m_BmpActorPtr->GetWidth() / 2,
		m_ActFireflyPtr->GetPosition().y - m_BmpActorPtr->GetHeight() / 2);

	matTranslate.SetAsTranslate(bitmapPos);
	matRotate.SetAsRotate(m_Angle);
	matRotate.SetAsScale(m_Scale);
	matWorldTransform = matRotate * matScale * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matWorldTransform);

	GAME_ENGINE->DrawBitmap(m_BmpActorPtr);
}

void Firefly::Tick(double deltaTime)
{
	Shadyguy::Tick(deltaTime);
}

void Firefly::ResetPos()
{
	m_ActFireflyPtr->SetPosition(m_SpawnPos);
}


