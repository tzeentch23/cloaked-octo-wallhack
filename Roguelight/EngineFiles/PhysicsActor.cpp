#include "stdafx.h" //for compiler
#include "../stdafx.h" // for intellisense

#include "PhysicsActor.h"


// http://www.iforce2d.net/b2dtut
// http://box2d.org/manual.pdf

PhysicsActor::PhysicsActor(DOUBLE2 pos, double angle, BodyType bodyType)
{
	SetBody(pos, angle, bodyType);
}

PhysicsActor::~PhysicsActor()
{
	// remove the body from the scene
	(GameEngine::GetSingleton())->GetBox2DWorld()->DestroyBody(m_BodyPtr);
}

void PhysicsActor::SetName(String name)
{
	tstring stdName = name.C_str();
	m_Name = std::string(stdName.begin(), stdName.end());
}

String PhysicsActor::GetName()
{
	return String(m_Name.c_str());
}

bool PhysicsActor::SetBody(DOUBLE2 pos, double angle, BodyType bodyType)
{
	b2BodyDef bodyDef;
	// Define the dynamic body. We set its position and call the body factory.
	switch (bodyType)
	{
	case BodyType::DYNAMIC:
		bodyDef.type = b2_dynamicBody;
		break;
	case BodyType::STATIC:
		bodyDef.type = b2_staticBody;
		break;
	case BodyType::KINEMATIC:
		bodyDef.type = b2_kinematicBody;
		break;

	}

	// rescale to Box2D coordinates
	pos /= m_Scale;

	bodyDef.position.Set((float)(pos.x), (float)(pos.y));
	bodyDef.angle = (float)angle;

	m_BodyPtr = (GameEngine::GetSingleton())->GetBox2DWorld()->CreateBody(&bodyDef);

	if (m_BodyPtr == nullptr) return false;
	return true;
}

bool PhysicsActor::AddBoxShape(double width, double height, double restitution, double friction, double density)
{
	b2FixtureDef fixtureDef;
	width /= m_Scale; height /= m_Scale;

	// The extents are the half-widths of the box.
	b2PolygonShape shape;
	shape.SetAsBox((float)width / 2, (float)height / 2);

	// Define the dynamic body fixture.	
	fixtureDef.shape = &shape;

	fixtureDef.restitution = (float)restitution;
	// Set the box density to be non-zero, so it will be dynamic.
	if (m_BodyPtr->GetType() == b2_dynamicBody)fixtureDef.density = (float)density;
	else fixtureDef.density = 0.0f;

	// Override the default friction.
	fixtureDef.friction = (float)friction;

	// store this for contact information
	fixtureDef.userData = (void *) this;

	// Add the shape to the body.
	b2Fixture *fixturePtr = m_BodyPtr->CreateFixture(&fixtureDef);
	if (fixturePtr == nullptr)return false;
	ApplyGhost(fixturePtr);
	return true;
}

bool PhysicsActor::AddCircleShape(double radius, DOUBLE2 offset, double restitution, double friction, double density)
{
	b2FixtureDef fixtureDef;
	radius /= m_Scale;
	// The extents are the half-widths of the box.
	b2CircleShape circle;
	// position, relative to body position
	circle.m_p.Set((float)offset.x / m_Scale, (float)offset.y / m_Scale);
	// radius 
	circle.m_radius = (float)radius;

	// Define the dynamic body fixture.	
	fixtureDef.shape = &circle;

	fixtureDef.restitution = (float)restitution;
	// Set the box density to be non-zero, so it will be dynamic.
	if (m_BodyPtr->GetType() == b2_dynamicBody)fixtureDef.density = (float)density;
	else fixtureDef.density = 0.0f;

	// Override the default friction.
	fixtureDef.friction = (float)friction;

	// store this for contact information
	fixtureDef.userData = (void *) this;

	// Add the shape to the body.
	b2Fixture *fixturePtr = m_BodyPtr->CreateFixture(&fixtureDef);
	if (fixturePtr == nullptr)return false;
	ApplyGhost(fixturePtr);
	return true;
}

bool PhysicsActor::AddPolygonShape(const std::vector<DOUBLE2>& vertexArrRef, double restitution, double friction, double density)
{
	b2FixtureDef fixtureDef;
	std::vector<b2Vec2> vecArr;
	// scale to phyics units
	for (size_t i = 0; i < vertexArrRef.size(); i++)
	{
		vecArr.push_back(b2Vec2((float)vertexArrRef[i].x / m_Scale, (float)vertexArrRef[i].y / m_Scale));
	}

	//pass array to the shape
	b2PolygonShape polygonShape;
	polygonShape.Set(vecArr.data(), vecArr.size());

	// Define the dynamic body fixture.	
	fixtureDef.shape = &polygonShape;

	fixtureDef.restitution = (float)restitution;
	// Set the box density to be non-zero, so it will be dynamic.
	if (m_BodyPtr->GetType() == b2_dynamicBody)fixtureDef.density = (float)density;
	else fixtureDef.density = 0.0f;

	// Override the default friction.
	fixtureDef.friction = (float)friction;

	// store this for contact information
	fixtureDef.userData = (void *) this;

	// Add the shape to the body.
	b2Fixture *fixturePtr = m_BodyPtr->CreateFixture(&fixtureDef);
	if (fixturePtr == nullptr)return false;
	ApplyGhost(fixturePtr);
	return true;
}

bool PhysicsActor::AddChainShape(const std::vector<DOUBLE2>& vertexArrRef, bool closed, double restitution, double friction, double density)
{
	b2FixtureDef fixtureDef;
	std::vector<b2Vec2> vecArr;

	// seems that svg start vectex and end vertex are sometimes too close together or coincide, 
	// causing a crash in Box2D -> remove the last element
	// check the distance between begin and end points, omit the end point
	int omitLastVertex = 0;
	if ((vertexArrRef[0] - vertexArrRef[vertexArrRef.size() - 1]).SquaredLength() < 0.1)
	{
		omitLastVertex = 1;
	}

	for (size_t i = 0; i < vertexArrRef.size() - omitLastVertex; i++)
	{
		vecArr.push_back(b2Vec2((float)vertexArrRef[i].x / m_Scale, (float)vertexArrRef[i].y / m_Scale));
	}

	//pass array to the shape
	b2ChainShape chainShape;
	if (closed)chainShape.CreateLoop(vecArr.data(), vecArr.size());
	else chainShape.CreateChain(vecArr.data(), vecArr.size());

	// Define the dynamic body fixture.	
	fixtureDef.shape = &chainShape;

	fixtureDef.restitution = (float)restitution;
	// Set the box density to be non-zero, so it will be dynamic.
	if (m_BodyPtr->GetType() == b2_dynamicBody)fixtureDef.density = (float)density;
	else fixtureDef.density = 0.0f;

	// Override the default friction.
	fixtureDef.friction = (float)friction;

	// store this for contact information
	fixtureDef.userData = (void *) this;

	// Add the shape to the body.
	b2Fixture *fixturePtr = m_BodyPtr->CreateFixture(&fixtureDef);
	if (fixturePtr == nullptr)return false;

	ApplyGhost(fixturePtr);

	return true;
}

bool PhysicsActor::AddSVGShape(const String & svgFilePathRef, double restitution, double friction, double density)
{
	// a vector containing chains
	std::vector<std::vector<DOUBLE2>> verticesArr;

	//parse the svg file
	SVGParser(svgFilePathRef, verticesArr);

	// process the chains
	for (size_t i = 0; i < verticesArr.size(); i++)
	{
		std::vector<DOUBLE2> &chain = verticesArr[i];
		bool result = AddChainShape(chain, true, restitution, friction, density);
		if (!result) OutputDebugStringA("svg Chain creation failed");
	}
	return true;
}

DOUBLE2 PhysicsActor::GetPosition()
{
	b2Vec2 position = m_BodyPtr->GetPosition();
	return DOUBLE2(position.x, position.y) * m_Scale;
}

void PhysicsActor::SetPosition(const DOUBLE2& positionRef)
{
	m_BodyPtr->SetTransform(b2Vec2((float)(positionRef.x / m_Scale), (float)(positionRef.y / m_Scale)), m_BodyPtr->GetAngle());
	m_BodyPtr->SetAwake(true);
}

double PhysicsActor::GetAngle()
{
	float32 angle = m_BodyPtr->GetAngle(); 
	return angle;
}

void PhysicsActor::SetAngle(double angle)
{
	m_BodyPtr->SetTransform(m_BodyPtr->GetPosition(), (float)angle);
	m_BodyPtr->SetAwake(true);
}

void PhysicsActor::SetLinearVelocity(DOUBLE2 velocity)
{
	velocity /= m_Scale;
	m_BodyPtr->SetLinearVelocity(b2Vec2((float)velocity.x, (float)velocity.y));
	m_BodyPtr->SetAwake(true);
}

DOUBLE2  PhysicsActor::GetLinearVelocity()
{
	b2Vec2 v = m_BodyPtr->GetLinearVelocity();
	return DOUBLE2(v.x, v.y) * m_Scale;
}

void PhysicsActor::SetAngularVelocity(double velocity)
{
 	m_BodyPtr->SetAngularVelocity((float)velocity);
	m_BodyPtr->SetAwake(true);
}

double  PhysicsActor::GetAngularVelocity()
{
	return m_BodyPtr->GetAngularVelocity(); 
}

double PhysicsActor::GetMass()
{
	return m_BodyPtr->GetMass();
}

void PhysicsActor::SetFixedRotation(bool fixedRotation)
{
	m_BodyPtr->SetFixedRotation(fixedRotation);
}

bool PhysicsActor::IsFixedRotation()
{
	return m_BodyPtr->IsFixedRotation();
}

void PhysicsActor::SetBullet(bool bullet)
{
	m_BodyPtr->SetBullet(bullet);
}

void PhysicsActor::SetActive(bool active)
{
	m_BodyPtr->SetActive(active);
}

void PhysicsActor::SetGravityScale(double scale)
{
	m_BodyPtr->SetGravityScale((float)scale);
}

bool PhysicsActor::Raycast(DOUBLE2 point1, DOUBLE2 point2, DOUBLE2 &intersectionRef, DOUBLE2 &normalRef, double &fractionRef)
{
	point1 /= m_Scale;
	point2 /= m_Scale;
	b2Transform transform;
	//transform.SetIdentity();
	transform.Set(m_BodyPtr->GetPosition(), m_BodyPtr->GetAngle());
	b2RayCastInput input;
	input.p1.Set((float)point1.x, (float)point1.y);
	input.p2.Set((float)point2.x, (float)point2.y);
	input.maxFraction = 1.0f;
	b2RayCastOutput output, closestOutput;
	closestOutput.fraction = 1; //start with end of line as p2
	//check every fixture of every body to find closest 
	for (b2Fixture* fixturePtr = m_BodyPtr->GetFixtureList(); fixturePtr != nullptr; fixturePtr = fixturePtr->GetNext())
	{
		//A child index is included for chain shapes because the ray cast will only	check a single edge at a time.
		for (int edgeIndex = 0; edgeIndex < fixturePtr->GetShape()->GetChildCount(); ++edgeIndex)
		{
			bool hit = fixturePtr->GetShape()->RayCast(&output, input, transform, edgeIndex);
			if (hit)
			{
				if (output.fraction < closestOutput.fraction)
					closestOutput = output;
			}
		}
	}
	if (closestOutput.fraction < 1)
	{
		b2Vec2 hitPoint = input.p1 + closestOutput.fraction * (input.p2 - input.p1);
		intersectionRef = DOUBLE2(hitPoint.x, hitPoint.y) * m_Scale;
		normalRef = DOUBLE2(output.normal.x, output.normal.y);
		fractionRef = output.fraction;
		return true;
	}
	// no intersection
	return false;
}

void PhysicsActor::ApplyForce(DOUBLE2 force, DOUBLE2 offsetPoint)
{
	if (offsetPoint.x == 0 && offsetPoint.y == 0)
	{
		m_BodyPtr->ApplyForceToCenter(b2Vec2((float)force.x, (float)force.y), true);
	}
	else
	{
		b2Vec2 p = m_BodyPtr->GetWorldPoint(b2Vec2((float)offsetPoint.x / m_Scale, (float)offsetPoint.y / m_Scale));
		m_BodyPtr->ApplyForce(b2Vec2((float)force.x, (float)force.y), p, true);
	}
}

void PhysicsActor::ApplyTorque(double torque)
{
	m_BodyPtr->ApplyTorque((float)torque, true);
}

void PhysicsActor::ApplyLinearImpulse(DOUBLE2 impulse)
{
	m_BodyPtr->ApplyLinearImpulse(b2Vec2((float)impulse.x, (float)impulse.y), m_BodyPtr->GetWorldCenter(), true);
}

void PhysicsActor::ApplyAngularImpulse(double impulse)
{
	m_BodyPtr->ApplyAngularImpulse((float)impulse, true);
}

void PhysicsActor::SetTrigger(bool trigger)
{
	for (b2Fixture* fixturePtr = m_BodyPtr->GetFixtureList(); fixturePtr != nullptr; fixturePtr = fixturePtr->GetNext())
	{
		fixturePtr->SetSensor(trigger);
	}
}

void PhysicsActor::SetGhost(bool ghost)
{
	m_bGhost = ghost;

	// apply the setting to all fixtures
	for (b2Fixture* fixturePtr = m_BodyPtr->GetFixtureList(); fixturePtr != nullptr; fixturePtr = fixturePtr->GetNext())
	{
		ApplyGhost(fixturePtr);
	}
}

void PhysicsActor::ApplyGhost(b2Fixture * fixturePtr)
{
	if (m_bGhost)
	{
		b2Filter filter;
		filter.maskBits = 0;
		fixturePtr->SetFilterData(filter);
	}
	else
	{
		b2Filter filter;
		filter.maskBits = 0xFFFF;
		fixturePtr->SetFilterData(filter);
	}
}

bool PhysicsActor::IsPointInActor(const DOUBLE2 &pointRef)
{
	bool hit = false;
	for (b2Fixture* fixturePtr = m_BodyPtr->GetFixtureList(); fixturePtr != nullptr && !hit; fixturePtr = fixturePtr->GetNext())
	{
		hit = fixturePtr->TestPoint(b2Vec2((float)pointRef.x / m_Scale, (float)pointRef.y / m_Scale));

	}
	return hit;
}

bool PhysicsActor::IsPointInActor(const POINT &pointRef)
{
	bool hit = false;
	for (b2Fixture* fixturePtr = m_BodyPtr->GetFixtureList(); fixturePtr != nullptr && !hit; fixturePtr = fixturePtr->GetNext())
	{
		hit = fixturePtr->TestPoint(b2Vec2((float)pointRef.x / m_Scale, (float)pointRef.y / m_Scale));

	}
	return hit;
}

bool PhysicsActor::IsOverlapping(PhysicsActor* otherActor)
{
	b2Transform transform;
	transform.Set(m_BodyPtr->GetPosition(), m_BodyPtr->GetAngle());
	b2Transform otherTransform;
	otherTransform.Set(otherActor->m_BodyPtr->GetPosition(), otherActor->m_BodyPtr->GetAngle());

	bool overlaps = false;
	for (b2Fixture* fixturePtr = m_BodyPtr->GetFixtureList(); fixturePtr != nullptr; fixturePtr = fixturePtr->GetNext())
	{
		for (int edgeIndex = 0; edgeIndex < fixturePtr->GetShape()->GetChildCount(); ++edgeIndex)
		{
			for (b2Fixture* otherfixturePtr = otherActor->m_BodyPtr->GetFixtureList(); otherfixturePtr != nullptr; otherfixturePtr = otherfixturePtr->GetNext())
			{
				for (int otherEdgeIndex = 0; otherEdgeIndex < otherfixturePtr->GetShape()->GetChildCount(); ++otherEdgeIndex)
				{
					if (b2TestOverlap(fixturePtr->GetShape(), edgeIndex, otherfixturePtr->GetShape(), otherEdgeIndex, transform, otherTransform))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

std::vector<DOUBLE2> PhysicsActor::GetContactList()
{
	std :: vector<DOUBLE2> contactPoints;
	for (b2ContactEdge* edgePtr = m_BodyPtr->GetContactList(); edgePtr; edgePtr = edgePtr->next)
	{
		if (edgePtr->contact->IsTouching())
		{
			//...world manifold is helpful for getting locations
			b2WorldManifold worldManifold;
			edgePtr->contact->GetWorldManifold(&worldManifold);

			int numPoints = edgePtr->contact->GetManifold()->pointCount;

			for (int i = 0; i < numPoints; i++)
			{
				contactPoints.push_back(DOUBLE2(worldManifold.points[i].x * m_Scale, worldManifold.points[i].y * m_Scale));
			}
		}
	}
	return contactPoints;
}

void PhysicsActor::AddContactListener(ContactListener *listenerPtr)
{
	//store the pointer in userdata to be used by the ContactCaller
	m_BodyPtr->SetUserData((void*)listenerPtr);
}

ContactListener *PhysicsActor::GetContactListener()
{
	return reinterpret_cast <ContactListener *>(m_BodyPtr->GetUserData());
}