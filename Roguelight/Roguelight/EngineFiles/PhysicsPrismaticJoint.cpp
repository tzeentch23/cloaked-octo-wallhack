#include "stdafx.h"
#include "../stdafx.h" // for intellisense

#include "PhysicsPrismaticJoint.h"
#include "PhysicsActor.h"

PhysicsPrismaticJoint::PhysicsPrismaticJoint(PhysicsActor *actAPtr, DOUBLE2 anchorA, PhysicsActor *actBPtr, DOUBLE2 anchorB, DOUBLE2 jointAxis, bool collide)
{
	b2PrismaticJointDef prismaticJointDef;
	prismaticJointDef.bodyA = actAPtr->m_BodyPtr;
	prismaticJointDef.bodyB = actBPtr->m_BodyPtr;
	prismaticJointDef.localAnchorA = b2Vec2((float)anchorA.x / (float)PhysicsActor::SCALE, (float)anchorA.y / (float)PhysicsActor::SCALE);
	prismaticJointDef.localAnchorB = b2Vec2((float)anchorB.x / (float)PhysicsActor::SCALE, (float)anchorB.y / (float)PhysicsActor::SCALE);
	prismaticJointDef.collideConnected = collide;
	prismaticJointDef.referenceAngle = (float)0;
	prismaticJointDef.localAxisA.Set((float)jointAxis.x, (float)jointAxis.y);
	m_PrismaticJointPtr = dynamic_cast <b2PrismaticJoint*>((GameEngine::GetSingleton())->GetBox2DWorld()->CreateJoint(&prismaticJointDef));
}

PhysicsPrismaticJoint::~PhysicsPrismaticJoint()
{
	(GameEngine::GetSingleton())->GetBox2DWorld()->DestroyJoint(m_PrismaticJointPtr);
}

void PhysicsPrismaticJoint::EnableJointLimits(bool enableLimits, double lowerTranslation, double upperTranslation)
{
	m_PrismaticJointPtr->EnableLimit(enableLimits);
	m_PrismaticJointPtr->SetLimits((float)lowerTranslation / (float)PhysicsActor::SCALE, (float)upperTranslation / (float)PhysicsActor::SCALE);
}

void PhysicsPrismaticJoint::EnableMotor(bool enableMotor, double targetSpeed, double maxMotorForce)
{
	m_PrismaticJointPtr->EnableMotor(enableMotor);
	m_PrismaticJointPtr->SetMotorSpeed((float)targetSpeed / (float)PhysicsActor::SCALE);
	m_PrismaticJointPtr->SetMaxMotorForce((float)maxMotorForce);
}

double PhysicsPrismaticJoint::GetJointTranslation() const
{
	return m_PrismaticJointPtr->GetJointTranslation() * (float)PhysicsActor::SCALE;
}

//query joint limits
bool PhysicsPrismaticJoint::IsLimitEnabled() const 
{ 
	return m_PrismaticJointPtr->IsLimitEnabled(); 
}

double PhysicsPrismaticJoint::GetLowerLimit() const
{
	return m_PrismaticJointPtr->GetLowerLimit() * (float)PhysicsActor::SCALE;
}

double PhysicsPrismaticJoint::GetUpperLimit() const
{
	return m_PrismaticJointPtr->GetUpperLimit() * (float)PhysicsActor::SCALE;
}

//query joint motor
bool PhysicsPrismaticJoint::IsMotorEnabled() const
{ 
	return m_PrismaticJointPtr->IsMotorEnabled();
}

double PhysicsPrismaticJoint::GetMotorSpeed() const
{
	return m_PrismaticJointPtr->GetMotorSpeed() * (float)PhysicsActor::SCALE;
}

double PhysicsPrismaticJoint::GetMotorForce(double deltaTime) const
{
	return m_PrismaticJointPtr->GetMotorForce(1/(float)deltaTime);
}