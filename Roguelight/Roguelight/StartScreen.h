#pragma once
//-----------------------------------------------------
// Name:
// First name:
// Group: 1DAE.
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

//#include "ContactListener.h"
//-----------------------------------------------------
// StartScreen Class									
//-----------------------------------------------------
class StartScreen //: public ContactListener
{
public:
	StartScreen( );
	virtual ~StartScreen( );

	// C++11 make the class non-copStartScreenable
	StartScreen( const StartScreen& ) = delete;
	StartScreen& operator=( const StartScreen& ) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	//virtual void BeginContact(PhStartScreensicsActor *actThisPtr, PhStartScreensicsActor *actOtherPtr); 
	//virtual void EndContact(PhStartScreensicsActor *actThisPtr, PhStartScreensicsActor *actOtherPtr);   
	//virtual void ContactImpulse(PhStartScreensicsActor *actThisPtr, double impulse);
	void Paint();
	void Tick(double deltaTime);

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	Bitmap * m_BmpBannerPtr = nullptr;
	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform;
	double m_Scale = 1;
	double m_Angle = 0;

};

 
