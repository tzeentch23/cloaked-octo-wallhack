#pragma once
//-----------------------------------------------------
// Name: Angelika	
// First name: Kirkorova
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Elf.h"
//#include "ContactListener.h"
//-----------------------------------------------------
// HUD Class									
//-----------------------------------------------------
class HUD //: public ContactListener
{
public:
	enum class Type
	{
		HEALTH,
		COINS,
		AMMO,
	};

	HUD(DOUBLE2 pos,Type type);
	virtual ~HUD( );

	// C++11 make the class non-copHUDable
	HUD( const HUD& ) = delete;
	HUD& operator=( const HUD& ) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	//virtual void BeginContact(PhHUDsicsActor *actThisPtr, PhHUDsicsActor *actOtherPtr); 
	//virtual void EndContact(PhHUDsicsActor *actThisPtr, PhHUDsicsActor *actOtherPtr);   
	//virtual void ContactImpulse(PhHUDsicsActor *actThisPtr, double impulse);
	void Paint();
	void Tick(double deltaTime);

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	Type m_Type;
	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform;
	double m_Angle = 0;
	double m_Scale = 1;
	PhysicsActor * m_ActHUDPtr = nullptr;
	Bitmap * m_BmpHUDPtr = nullptr;
	static const int HUD_WIDTH = 30;
	static const int HUD_HEIGHT =70;
};

 
