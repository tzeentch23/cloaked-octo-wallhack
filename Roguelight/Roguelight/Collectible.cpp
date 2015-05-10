//-----------------------------------------------------
// Name: Kirkorova 
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
		
//---------------------------
// Includes
//---------------------------
#include "Collectible.h"
#include "Elf.h"
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * Collectible::m_BmpCoinPtr = nullptr;
Bitmap * Collectible::m_BmpAmmoPtr = nullptr;
Bitmap * Collectible::m_BmpHeartPtr = nullptr;
Collectible::Collectible(DOUBLE2 pos, Type type)
{

	m_ActCollectPtr = new PhysicsActor(pos, 0, BodyType::STATIC);
	m_ActCollectPtr->AddBoxShape(10, 10, 0.0, 0.2, 0.2);
	m_ActCollectPtr->AddContactListener(this);
	++m_InstanceCounter;
	
	m_Type = type;
	
	if ( type == Type::HEARTS)
	{
		m_BmpHeartPtr = new Bitmap(String("./resources/hearts.png"));
	}
	if (type == Type::AMMO)
	{
		m_BmpAmmoPtr = new Bitmap(String("./resources/arrows.png"));
	}
	if (type == Type::COINS)
	{
		m_BmpCoinPtr = new Bitmap(String("./resources/coins.png"));
	}
}

Collectible::~Collectible()
{
	delete m_ActCollectPtr;
	m_ActCollectPtr = nullptr;
	--m_InstanceCounter;
	if (m_InstanceCounter == 0)
	{
		delete m_BmpCoinPtr;
		m_BmpCoinPtr = nullptr;
		delete m_BmpHeartPtr;
		m_BmpHeartPtr = nullptr;
		delete m_BmpAmmoPtr;
		m_BmpAmmoPtr = nullptr;
	}
}

void Collectible::Tick(double deltaTime)
{
	m_Time += deltaTime;
	if (m_Time>1.0 / FRAMERATE)
	{
		++m_FrameNr;
		m_FrameNr %= NR_AMMO_COLS* NR_AMMO_ROWS;
		m_Time = 0;
	}
}

void Collectible::Paint()
{
	Bitmap *bmp = nullptr;
	int nrCols, nrRows;

	if (m_Type == Type::AMMO)
	{
		nrCols = NR_AMMO_COLS;
		nrRows = NR_AMMO_ROWS;
		bmp = m_BmpAmmoPtr;
	}
	if (m_Type==Type::COINS)
	{
		nrCols = NR_COINS_COLS;
		nrRows = NR_COINS_ROWS;
		bmp = m_BmpCoinPtr;
	}
	if (m_Type == Type::HEARTS)
	{
		nrCols = NR_HEARTS_COLS;
		nrRows = NR_HEARTS_ROWS;
		bmp = m_BmpHeartPtr;
	}
	
	int spriteWidth = bmp->GetWidth() / nrCols;
	int spriteHeight = bmp->GetHeight() / nrRows;
	int col = m_FrameNr % nrCols;
	int cropX = spriteWidth*col;
	int cropY = 0;
	RECT bmpRect;
	bmpRect.top = cropY;
	bmpRect.bottom = cropY + spriteHeight;
	bmpRect.left = cropX;
	bmpRect.right = cropX + spriteWidth;
	DOUBLE2 bitmapPos(m_ActCollectPtr->GetPosition().x - (spriteWidth / 2),
		m_ActCollectPtr->GetPosition().y - (spriteHeight / 2));

	if (bmp != nullptr) 
	{
		matTranslate.SetAsTranslate(bitmapPos); 
		matRotate.SetAsRotate(m_Angle);
		matRotate.SetAsScale(m_Scale);
		matWorldTransform = matRotate * matScale * matTranslate;

		GAME_ENGINE->SetWorldMatrix(matWorldTransform);

		GAME_ENGINE->DrawBitmap(bmp, bmpRect);
	}
	//tuk primerno, sledvashtata instancia koiato iskash da narisuvash shte grymne kofti zashtoto ti realno shte iztriesh m_BmpSpikePtr primernno.. t.e. ti triesh bmp *, no to sochi tova koeto sochi m_neshtoto, i sledvashtia pyt shte ti e kofti.. pak da kaja - triesh samo tova koeto e s new, nishti drugo.. tova e zakon
	////ok de, sega shte gi ogledam.. .....ok
}


//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Collectible::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	Elf * elf = Elf::GetPlayer();
	
		if (m_Type == Type::COINS)
		{
			elf->IncreaseCoins();
		}
		if (m_Type == Type::AMMO)
		{
			elf->IncreaseAmmo();
		}
		if (m_Type == Type::HEARTS)
		{
			elf->IncreaseHealth();
		}	
		m_IsConsumed = true;
		m_ActCollectPtr->SetGhost(true); 
}

void Collectible::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Collectible::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}

bool Collectible::IsConsumed() 
{
	return m_IsConsumed;
}