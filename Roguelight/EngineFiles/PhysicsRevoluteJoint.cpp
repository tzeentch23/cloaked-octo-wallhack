#include "stdafx.h"
#include "../stdafx.h" // for intellisense

#include "PhysicsRevoluteJoint.h"
#include "PhysicsActor.h"

PhysicsRevoluteJoint::PhysicsRevoluteJoint(PhysicsActor *actAPtr, DOUBLE2 anchorA, PhysicsActor *actBPtr, DOUBLE2 anchorB, bool collide, double referenceAngle)
{
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = actAPtr->m_BodyPtr;
	revoluteJointDef.bodyB = actBPtr->m_BodyPtr;
	revoluteJointDef.localAnchorA = b2Vec2((float)anchorA.x / (float)PhysicsActor::m_Scale, (float)anchorA.y/ (float)PhysicsActor::m_Scale);
	revoluteJointDef.localAnchorB = b2Vec2((float)anchorB.x / (float)PhysicsActor::m_Scale, (float)anchorB.y/ (float)PhysicsActor::m_Scale);
	revoluteJointDef.collideConnected = collide;
	revoluteJointDef.referenceAngle = (float)referenceAngle;

	m_RevoluteJointPtr = dynamic_cast <b2RevoluteJoint*>((GameEngine::GetSingleton())->GetBox2DWorld()->CreateJoint(&revoluteJointDef));
}

PhysicsRevoluteJoint::~PhysicsRevoluteJoint()
{
	(GameEngine::GetSingleton())->GetBox2DWorld()->DestroyJoint(m_RevoluteJointPtr);
}

void PhysicsRevoluteJoint::EnableJointLimits(bool enableLimits, double lowerAngle, double upperAngle)
{
	m_RevoluteJointPtr->EnableLimit(enableLimits);
	m_RevoluteJointPtr->SetLimits((float)lowerAngle, (float)upperAngle);
}

void PhysicsRevoluteJoint::EnableMotor(bool enableMotor, double targetSpeed, double maxMotorTorque)
{
	m_RevoluteJointPtr->EnableMotor(enableMotor);
	m_RevoluteJointPtr->SetMotorSpeed((float)targetSpeed);
	m_RevoluteJointPtr->SetMaxMotorTorque((float)maxMotorTorque);
}

//query joint limits
bool PhysicsRevoluteJoint::IsLimitEnabled() const
{
	return m_RevoluteJointPtr->IsLimitEnabled();
}

double PhysicsRevoluteJoint::GetLowerLimit() const
{
	return m_RevoluteJointPtr->GetLowerLimit() * (float)PhysicsActor::m_Scale;
}

double PhysicsRevoluteJoint::GetUpperLimit() const
{
	return m_RevoluteJointPtr->GetUpperLimit() * (float)PhysicsActor::m_Scale;
}

//query joint motor
bool PhysicsRevoluteJoint::IsMotorEnabled() const
{
	return m_RevoluteJointPtr->IsMotorEnabled();
}

double PhysicsRevoluteJoint::GetMotorSpeed() const
{
	return m_RevoluteJointPtr->GetMotorSpeed();
}

double PhysicsRevoluteJoint::GetMotorTorque(double deltaTime) const
{
	return m_RevoluteJointPtr->GetMotorTorque(1 / (float)deltaTime);
}