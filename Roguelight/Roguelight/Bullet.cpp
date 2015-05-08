//-----------------------------------------------------
// Name: Kirkorova 
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
		
//---------------------------
// Includes
//---------------------------
#include "Bullet.h"
#include "Elf.h"
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bullet::Bullet(DOUBLE2 pos, DOUBLE2 velocity) : m_IsFlying(true)
{
	m_ActortPtr = new PhysicsActor(pos, 0, BodyType::DYNAMIC);
	if (velocity.y == 0)
		m_ActortPtr->SetGravityScale(0.001);
	m_ActortPtr->SetBullet(true);
	m_ActortPtr->AddBoxShape(10, 10, 1.0, 100.0, 100);
	m_ActortPtr->AddContactListener(this);
	m_ActortPtr->SetPosition(pos);
	m_ActortPtr->SetLinearVelocity(velocity);
	
}

Bullet::~Bullet()
{
	m_ActortPtr->RemoveContactListener(this);
	delete m_ActortPtr;
	m_ActortPtr = nullptr;
}

void Bullet::Tick(double deltaTime)
{
	
	m_Time += deltaTime;
	if (m_Time>10)
	{
		m_IsFlying = false;
	}
}

void Bullet::Paint()
{
	if (!m_IsFlying) {
		return;
	}
	
	matTranslate.SetAsTranslate(m_ActortPtr->GetPosition()); 
	matRotate.SetAsRotate(m_Angle);
	matRotate.SetAsScale(m_Scale);
	matWorldTransform = matRotate * matScale * matTranslate;

	GAME_ENGINE->SetWorldMatrix(matWorldTransform);
	GAME_ENGINE->SetColor(COLOR(255, 0, 0));
	GAME_ENGINE->FillEllipse(DOUBLE2(0, 0), 2.0, 2.0);	
}


//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
void Bullet::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

	if (Elf::GetPlayer()->GetPhysicsActor() != actOtherPtr)
	{
		m_IsFlying = false;
		m_ActortPtr->SetActive(false);
	}
	//TODO
}

void Bullet::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{

}

void Bullet::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}

bool Bullet::IsFlying() 
{
	return m_IsFlying;
}