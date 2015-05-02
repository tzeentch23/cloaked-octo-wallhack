//-----------------------------------------------------
// Name:Angelika
// First name:Kirkorova
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "Elf.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

Elf* Elf::player = nullptr;
//---------------------------
// Constructor & Destructor
//---------------------------
Elf::Elf(DOUBLE2 spawnPos) : m_SpawnPos(spawnPos)
{
	player = this; 
	m_Ammo = 5;
	m_Health = 5;
	m_Money = 0;
	
	m_ActElfPtr = new PhysicsActor(m_SpawnPos, 0, BodyType::DYNAMIC);
	m_ActElfPtr->AddBoxShape(ACTOR_WIDTH, ACTOR_HEIGHT, 0.0, 0.2, 0.2);
	m_ActElfPtr->SetFixedRotation(true);
	//m_ActElfPtr->SetTrigger(false);
	m_ActElfPtr->SetGravityScale(1);

	
	m_BmpElfPtr = new Bitmap(String("./resources/spritesElf.png"));
	m_BmpElfPtr->SetTransparencyColor(COLOR(0, 0, 0));
}

Elf::~Elf()
{
	delete m_ActElfPtr;
	m_ActElfPtr = nullptr;
	delete m_BmpElfPtr;
	m_BmpElfPtr = nullptr;
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Elf::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	
}

void Elf::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Elf::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}

void Elf::Paint()
{
	DOUBLE2 currentPos = m_ActElfPtr->GetPosition();
	DOUBLE2 spritePos(currentPos.x - (m_BmpElfPtr->GetWidth() / 12),
		currentPos.y - (m_BmpElfPtr->GetHeight() / 10));
	int spriteWidth = m_BmpElfPtr->GetWidth()/NR_COLS;
	int spriteHeight = m_BmpElfPtr->GetHeight()/ NR_ROWS;
	int col = m_FrameNr / NR_COLS;
	int row;
	if (m_State == State::STANDING)
	{
		row = 0;
	}
	if (m_State == State::WALKING)
	{
		row = 1;
	}
	if (m_State == State::WALKANDAIM)
	{
		row = 2;
	}
	if (m_State == State::JUMPANDAIM)
	{
		row = 3;
	}
	if (m_State == State::JUMPING)
	{
		row = 4;
	}
	int cropX = spriteWidth* col;
	int cropY = spriteHeight* row;

	RECT2 spriteElf;
	spriteElf.top = cropY;
	spriteElf.bottom = cropY + spriteHeight;
	spriteElf.left = cropX;
	spriteElf.right = cropX + spriteWidth;

	GAME_ENGINE->DrawBitmap(m_BmpElfPtr,DOUBLE2(spritePos), spriteElf);

	String status = String(currentPos.x) + String(" ") + String(currentPos.y) + String("\n") +
		String(m_Ammo) + String("  ") + String(m_Health) + String("  ") + String(m_Money);
	GAME_ENGINE->SetColor(COLOR(255, 255, 255));
	GAME_ENGINE->DrawString(status, currentPos.x + 50, currentPos.y + 50);
	

}

void Elf::Tick(double deltatime)
{
	if (m_State != State::JUMPING || m_ActElfPtr->GetContactList().size() > 0)
	{
		m_State = State::STANDING;
	}

		DOUBLE2 velocityChange, newVelocity, impulse;
		newVelocity.y = 200;
		double mass = m_ActElfPtr->GetMass(); 
	
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT))
		{
			m_State = State::WALKING;
			newVelocity.x = -1000;
		}
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
		{
			m_State = State::WALKING;
			newVelocity.x = 1000;
		}

		if (GAME_ENGINE->IsKeyboardKeyPressed('Z'))
		{
			m_State = State::JUMPING;
			newVelocity.y = -25000;
		}

		velocityChange.y = newVelocity.y - m_ActElfPtr->GetLinearVelocity().y;
		velocityChange.x = newVelocity.x - m_ActElfPtr->GetLinearVelocity().x;
		impulse = mass * velocityChange / PhysicsActor::SCALE;
		m_ActElfPtr->ApplyForce(impulse);
		//m_ActElfPtr->SetLinearVelocity(DOUBLE2(-100, 500));
		//n/e/ tsi li se spi da, no zadryj taka 10 min oshte//pfu tova e elfa
		m_Time += deltatime;
		if (m_Time>1.0/FRAMERATE)
		{
			++m_FrameNr;
			m_FrameNr %= NR_COLS* NR_ROWS;
			m_Time = 0;
		}

}

	
DOUBLE2 Elf::GetPosition()
{
	DOUBLE2 posActor = m_ActElfPtr->GetPosition();
	return posActor;
}

void Elf::ResetPosition()
{
	m_ActElfPtr->SetPosition(DOUBLE2(GAME_ENGINE->GetWidth() / 2, GAME_ENGINE->GetHeight() / 2));
	m_ActElfPtr->SetAngle(0.0);
	m_ActElfPtr->SetAngularVelocity(0.0);
	m_ActElfPtr->SetLinearVelocity(DOUBLE2(0, 0));
}

void Elf::IncreaseAmmo()
{
	++m_Ammo; 
}
void Elf::DecreaseAmmo()
{
	--m_Ammo; 
}
void Elf::IncreaseHealth()
{	
	++ m_Health;
}
void Elf::DecreaseHealth()
{
	--m_Health;
}
void Elf::IncreaseMoney()
{
	++m_Money;
}

Elf * Elf::getPlayer() {
	return player;
}