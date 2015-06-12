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
#include "Skelethon.h"
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------

Firefly::Firefly(DOUBLE2 pos, Bitmap * bmpPtr)
{
	m_Position = pos;
	m_ActFireflyPtr = new PhysicsActor(pos, 0, BodyType::STATIC);
	m_BmpPtr = bmpPtr;
}

Firefly::~Firefly()
{
	delete m_ActFireflyPtr;
	m_ActFireflyPtr = nullptr;
}

void Firefly::Paint()
{
	
	int spriteWidth = m_BmpPtr->GetWidth() / NR_COLS;
	int spriteHeight = m_BmpPtr->GetHeight() / NR_ROWS;
	int col = m_FrameNr % NR_COLS;
	int cropX = spriteWidth*col;
	int cropY = 0;
	RECT bmpRect;
	bmpRect.top = cropY;
	bmpRect.bottom = cropY + spriteHeight;
	bmpRect.left = cropX;
	bmpRect.right = cropX + spriteWidth;
	DOUBLE2 bitmapPos(m_ActFireflyPtr->GetPosition().x - (spriteWidth / 2),
		m_ActFireflyPtr->GetPosition().y - (spriteHeight / 2));

	if (m_BmpPtr != nullptr)
	{
		matTranslate.SetAsTranslate(bitmapPos);
		matRotate.SetAsRotate(m_Angle);
		matRotate.SetAsScale(m_Scale);
		matWorldTransform = matRotate * matScale * matTranslate;

		GAME_ENGINE->SetWorldMatrix(matWorldTransform);

		GAME_ENGINE->DrawBitmap(m_BmpPtr, bmpRect);
	}
	
}

void Firefly::Tick(double deltaTime)
{
	m_Time += deltaTime;
	if (m_Time>1.0 / FRAMERATE)
	{
		++m_FrameNr;
		m_FrameNr %= NR_COLS* NR_ROWS;
		m_Time = 0;
	}
}

DOUBLE2 Firefly::GetPosition()
{
	return m_Position;
}
