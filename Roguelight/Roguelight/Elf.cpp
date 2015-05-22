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
#include "Roguelight.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

Elf* Elf::player = nullptr;
//---------------------------
// Constructor & Destructor
//---------------------------
Elf::Elf(DOUBLE2 spawnPos) :Actor(spawnPos, 3, 5, 7, 20, 40)
{
	player = this;
	m_Ammo = 5;
	m_Coins = 0;
	m_Health = GetInitialHealth();
	m_BmpActorPtr = new Bitmap(String("./resources/spritesElf.png"));
	m_BmpActorPtr->SetTransparencyColor(COLOR(0, 0, 0));
}

Elf::~Elf()
{
	delete m_BmpActorPtr;
	m_BmpActorPtr = nullptr;
}

void Elf::Paint()
{
	m_Position = m_ActActorPtr->GetPosition();
	Actor::Paint();
	String status = String(m_Position.x) + String(" ") + String(m_Position.y) + String("\n") +
		String(m_Ammo) + String("  ") + String(m_Health) + String("  ") + String(m_Coins);
	GAME_ENGINE->SetColor(COLOR(255, 255, 255));
}

int Elf::GetSpriteRow()
{
	int row ;
	switch (m_State)
	{
	case State::WALKING:
		row = 1;
		break;
	case State::WALKANDAIM:
		row = 2;
		break;
	case State::JUMPANDAIM:
		row = 3;
		break;
	case State::JUMPING:
		row = 4;
		break;
	case State::AIMING:
		row = 5;
		break;
	case State::DEAD:
		row = 6;
		break;
	default:
		row = 0;
		break;
	}
	return row;
}

void Elf::Tick(double deltatime)
{
	if (m_Health > 0)
	{
		if (m_ActActorPtr->GetContactList().size() > 0)
		{
			m_State = State::STANDING;
		}

		DOUBLE2 velocityChange, newVelocity, impulse;
		newVelocity.y = 200;
		double mass = m_ActActorPtr->GetMass();
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT))
		{
			m_State = State::WALKING;
			newVelocity.x = -500;
			m_Direction = -1;
			m_Scale = -1;
		}
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
		{
			m_State = State::WALKING;
			newVelocity.x = 500;
			m_Direction = 1;
			m_Scale = 1;
		}


		if (GAME_ENGINE->IsKeyboardKeyDown('Z'))
		{
			m_State = State::JUMPING;
			newVelocity.y = -2500;
		}

		velocityChange.y = newVelocity.y - m_ActActorPtr->GetLinearVelocity().y;
		velocityChange.x = newVelocity.x - m_ActActorPtr->GetLinearVelocity().x;
		impulse = mass * velocityChange / PhysicsActor::SCALE;
		m_ActActorPtr->ApplyForce(impulse);


		if (GAME_ENGINE->IsKeyboardKeyDown('X'))
		{
			if (m_State == State::JUMPING)
			{
				m_State = State::JUMPANDAIM;
			}
			else if (m_ActActorPtr->GetLinearVelocity().x != 0)
			{
				m_State = State::WALKANDAIM;
			}
			else 
			{
				m_State = State::AIMING;
			}
		}
		Actor::Tick(deltatime);
	}
	else
	{
		m_State = State::DEAD;
		if (m_FrameNr < NR_COLS)
		{
			Actor::Tick(deltatime);
		}
	}

}

void Elf::IncreaseAmmo()
{
	++m_Ammo;
}
void Elf::DecreaseAmmo()
{
	--m_Ammo;
}

void Elf::IncreaseCoins()
{
	++m_Coins;
}

Elf * Elf::GetPlayer() {
	return player;
}

int Elf::GetAmmo()
{
	return m_Ammo;
}

int Elf::GetCoins()
{
	return m_Coins;
}

int Elf::GetDirection()
{
	return m_Direction;
}

int Elf::GetInitialHealth()
{
	return 5;
}

void Elf::DecreaseHealth()
{
	Actor::DecreaseHealth();
	if (m_Health <= 0)
	{
	//GameOver();
	}
}