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
class Roguelight;
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

	HUD(Type type, Roguelight *game);
	virtual ~HUD();

	// C++11 make the class non-copHUDable
	HUD(const HUD&) = delete;
	HUD& operator=(const HUD&) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	//virtual void BeginContact(PhHUDsicsActor *actThisPtr, PhHUDsicsActor *actOtherPtr); 
	//virtual void EndContact(PhHUDsicsActor *actThisPtr, PhHUDsicsActor *actOtherPtr);   
	//virtual void ContactImpulse(PhHUDsicsActor *actThisPtr, double impulse);
	void Paint();

private:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	Type m_Type;
	MATRIX3X2 matTranslate, matRotate, matScale, matStartPos, matWorldTransform;
	double m_Angle = 0;
	double m_Scale = 1;
	DOUBLE2 m_Position,
		m_HealthPos,
		m_CoinsPos,
		m_AmmoPos;
	Bitmap * m_BmpHUDPtr = nullptr;
	static Bitmap *m_Bmp1UpPtr; 
	Roguelight * m_Game;
};


