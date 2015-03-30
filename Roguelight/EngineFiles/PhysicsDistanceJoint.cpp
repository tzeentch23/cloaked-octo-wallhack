#include "stdafx.h"
#include "../stdafx.h" // for intellisense

#include "PhysicsDistanceJoint.h"
#include "PhysicsActor.h"

PhysicsDistanceJoint::PhysicsDistanceJoint(PhysicsActor *actAPtr, DOUBLE2 anchorA, PhysicsActor *actBPtr, DOUBLE2 anchorB, double length, double frequencyHz, double dampingRatio)
{
	b2DistanceJointDef DistanceJointDef;
	DistanceJointDef.bodyA = actAPtr->m_BodyPtr;
	DistanceJointDef.bodyB = actBPtr->m_BodyPtr;
	DistanceJointDef.localAnchorA = b2Vec2((float)anchorA.x / (float)PhysicsActor::m_Scale, (float)anchorA.y / (float)PhysicsActor::m_Scale);
	DistanceJointDef.localAnchorB = b2Vec2((float)anchorB.x / (float)PhysicsActor::m_Scale, (float)anchorB.y / (float)PhysicsActor::m_Scale);
	DistanceJointDef.length = (float)length / (float)PhysicsActor::m_Scale;
	DistanceJointDef.frequencyHz = (float)frequencyHz;
	DistanceJointDef.dampingRatio = (float)dampingRatio;

	m_DistanceJointPtr = dynamic_cast <b2DistanceJoint*>((GameEngine::GetSingleton())->GetBox2DWorld()->CreateJoint(&DistanceJointDef));

}

PhysicsDistanceJoint::~PhysicsDistanceJoint()
{
	(GameEngine::GetSingleton())->GetBox2DWorld()->DestroyJoint(m_DistanceJointPtr);
}

double PhysicsDistanceJoint::GetLength() const
{
	return m_DistanceJointPtr->GetLength() * (float)PhysicsActor::m_Scale;
}

void PhysicsDistanceJoint::SetLength(double length)
{
	if (length < 0.1)
	{
		GameEngine::GetSingleton()->MessageBox(String("Length can not be a very small number "));
	}
	m_DistanceJointPtr->SetLength((float)length / (float)PhysicsActor::m_Scale);
}


double PhysicsDistanceJoint::GetFrequency() const
{
	return m_DistanceJointPtr->GetFrequency();
}

void PhysicsDistanceJoint::SetFrequency(double frequency)
{
	m_DistanceJointPtr->SetFrequency((float)frequency);
}


double PhysicsDistanceJoint::GetDampingRatio() const
{
	return m_DistanceJointPtr->GetDampingRatio();
}

void PhysicsDistanceJoint::SetDampingRatio(double dampingRatio)
{
	m_DistanceJointPtr->SetDampingRatio((float)dampingRatio);
}

DOUBLE2 PhysicsDistanceJoint::GetReactionForce(double deltaTime) const
{
	b2Vec2 vec2 = m_DistanceJointPtr->GetReactionForce(1/(float)deltaTime);
	return DOUBLE2(vec2.x, vec2.y);
}

double PhysicsDistanceJoint::GetReactionTorque(double deltaTime) const
{
	return m_DistanceJointPtr->GetReactionTorque(1 / (float)deltaTime);
}
