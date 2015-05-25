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
#include "Roguelight.h"
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
int Collectible::m_InstanceCounter = 0;

Collectible::Collectible(DOUBLE2 pos, Type type)
{
	m_Type = type;
	BodyType bodyType;
	if (m_Type == Type::COINS)
	{
		bodyType = BodyType::DYNAMIC;
	}
	else
	{
		bodyType = BodyType::STATIC;
	}
	m_InitialPosition = pos;
	m_ActCollectPtr = new PhysicsActor(pos, 0, bodyType);
	m_ActCollectPtr->AddBoxShape(10, 10, 0, 0.5, 1);
	m_ActCollectPtr->SetGravityScale(0.1);
	m_ActCollectPtr->AddContactListener(this);

	++m_InstanceCounter;
	
	
	if ( type == Type::HEARTS)
	{
		if (m_BmpHeartPtr == nullptr)
		{
			m_BmpHeartPtr = new Bitmap(String("./resources/hearts.png"));
		}
	}
	if (type == Type::AMMO)
	{
		if (m_BmpAmmoPtr == nullptr)
		{
			m_BmpAmmoPtr = new Bitmap(String("./resources/ammo.png"));
		}
	}
	if (type == Type::COINS)
	{
		if (m_BmpCoinPtr == nullptr)
		{
			m_BmpCoinPtr = new Bitmap(String("./resources/coins.png"));
		}
		m_ActCollectPtr->SetLinearVelocity(m_CoinVelocity);
	}
}

Collectible::~Collectible()
{
	m_ActCollectPtr->RemoveContactListener(this);
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

	if (m_Type == Type::COINS)
	{
		Elf * elf = Elf::GetPlayer();
		DOUBLE2 elfPos = elf->GetPosition();
		DOUBLE2 coinPos = m_ActCollectPtr->GetPosition();
		double distance = DOUBLE2(coinPos - elfPos).Length();

		if (distance < MAX_DISTANCE)
		{
			DOUBLE2 dir = DOUBLE2(elfPos.x - coinPos.x, elfPos.y - coinPos.y);
			m_ActCollectPtr->ApplyForce(dir*5);
		}
		else 
		{
			if (m_ActCollectPtr->GetPosition().y <= m_InitialPosition.y)
			{
				m_CoinVelocity.y *= -1;
			}
			m_ActCollectPtr->SetLinearVelocity(m_CoinVelocity);
		}

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
}


//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Collectible::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	if (m_Type == Type::COINS)
	{
		if (actOtherPtr == Roguelight::GAME->GetLevelActor())
		{
			m_CoinVelocity.y *= -1;
			m_ActCollectPtr->SetLinearVelocity(m_CoinVelocity);
		}
	}

	Elf * elf = Elf::GetPlayer();
	
	if (actOtherPtr != elf->GetPhysicsActor())
	{
		return;
	}
	if (m_Type == Type::COINS)
	{
		elf->IncreaseCoins();
	}
	if (m_Type == Type::AMMO)
	{
		elf->Reload();
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

void Collectible::ResetPos()
{
	m_ActCollectPtr->SetPosition(m_InitialPosition);
	m_IsConsumed = false;
}