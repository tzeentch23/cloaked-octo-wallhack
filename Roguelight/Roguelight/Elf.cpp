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
#include "Camera.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------

Elf* Elf::player = nullptr;
Elf::Elf(DOUBLE2 spawnPos) :Actor(spawnPos, 3, 5, 7, 20, 40)
{
	player = this;
	m_Ammo = MAX_AMMO;
	m_Coins = 0;
	m_Health = GetInitialHealth();
	m_BmpActorPtr = new Bitmap(String("./resources/spritesElf.png"));
	
	m_GodmodeSndPtr = new Sound(String("./resources/godmode.mp3"));

	m_DecreaseHealthSndPtr = new Sound(String("./resources/sound_decreasehealth.mp3"));
	m_DecreaseHealthSndPtr->SetVolume(0.7);
	m_GetCoinSndPtr = new Sound(String("./resources/sound_get_coin.mp3"));
	m_GetCoinSndPtr->SetVolume(0.7);
	m_IsDeadSndPtr = new Sound(String("./resources/sound_death.mp3"));
	m_IsDeadSndPtr->SetVolume(0.7);
	m_BmpActorPtr->SetTransparencyColor(COLOR(0, 0, 0));
	m_ActActorPtr->AddContactListener(this);
}
Elf::~Elf()
{
	delete m_BmpActorPtr;
	m_BmpActorPtr = nullptr;

	delete m_DecreaseHealthSndPtr;
	m_DecreaseHealthSndPtr = nullptr;

	delete m_IsDeadSndPtr;
	m_IsDeadSndPtr = nullptr;

	delete m_GetCoinSndPtr;
	m_GetCoinSndPtr = nullptr;

	delete m_GodmodeSndPtr;
	m_GodmodeSndPtr = nullptr;
}

void Elf::Paint()
{
	Actor::Paint();
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
		bool applyImpulse = false;
		bool isStanding = abs(m_ActActorPtr->GetLinearVelocity().y) < 50;
		if (isStanding)
		{
			m_State = State::STANDING;
		}
		else
		{
			m_State = State::JUMPING;
		}

		if (GAME_ENGINE->IsKeyboardKeyPressed('G'))
		{
			m_GodMode = !m_GodMode;
			m_ActActorPtr->SetGhost(m_GodMode);
			if (m_GodMode)
			{
				m_ActActorPtr->SetGravityScale(0);
			}
			else
			{
				m_ActActorPtr->SetGravityScale(1);
			}
			if (m_GodMode)
			{ 
				m_GodmodeSndPtr->Play();
			}
		
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
			applyImpulse = true;
		}
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
		{
			m_State = State::WALKING;
			newVelocity.x = 500;
			m_Direction = 1;
			m_Scale = 1;
			applyImpulse = true;

		}

	
		if (abs(m_ActActorPtr->GetLinearVelocity().y) < 40)
		{
			m_JumpTime = 0;
		}
		else
		{
			m_JumpTime += deltatime;
		}

		if (GAME_ENGINE->IsKeyboardKeyPressed('Z'))
		{
			if (m_JumpTime == 0)
			{
				m_ActActorPtr->ApplyLinearImpulse(DOUBLE2(0, -3000));
			}
		}

		if (GAME_ENGINE->IsKeyboardKeyDown('Z'))
		{
				m_State = State::JUMPING;
			if (m_JumpTime > 0.1 && m_JumpTime < 0.4)
			{
				m_ActActorPtr->ApplyForce(DOUBLE2(0, -12000));
			}
		}

		if (GAME_ENGINE->IsKeyboardKeyDown('S'))
		{
			DOUBLE2 pos = m_ActActorPtr->GetPosition();
			String status = String(pos.x) + String(" ") + String(pos.y) + String("\n");
			OutputDebugString(status);
		}
		if (m_GodMode)
		{
			if (GAME_ENGINE->IsKeyboardKeyDown(VK_UP))
			{
				newVelocity.y = -250;
				applyImpulse = true;
			}

			if (GAME_ENGINE->IsKeyboardKeyDown(VK_DOWN))
			{
				newVelocity.y = 250;
				applyImpulse = true;
			}
		}

		if (applyImpulse) 
		{
			velocityChange.y = newVelocity.y;
			velocityChange.x = newVelocity.x - m_ActActorPtr->GetLinearVelocity().x;
			impulse = mass * velocityChange / PhysicsActor::SCALE;
			m_ActActorPtr->ApplyForce(impulse);
		}


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

void Elf::Reload()
{
	m_Ammo = MAX_AMMO;
}
void Elf::DecreaseAmmo()
{
	--m_Ammo;
}

void Elf::IncreaseCoins()
{
	m_GetCoinSndPtr->Play();
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
	return MAX_HEALTH;
}
void Elf::DecreaseHealth()
{
	int previousHealth = m_Health;
	Actor::DecreaseHealth();  

	if (previousHealth > 0 && m_Health <= 0)
	{
		m_IsDeadSndPtr->Play();
	}
	else
	{
		m_DecreaseHealthSndPtr->Play();
	}
}


void Elf::Reset()
{
	Actor::Reset();
	m_Ammo = MAX_AMMO;
	m_State = State::STANDING;
}

void Elf::IncreaseHealth()
{
	m_Health = MAX_HEALTH;
}

void Elf::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr) 
{
	m_NrOfJumps = 0;

}
