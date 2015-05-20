#pragma once
//-----------------------------------------------------
// Name: Kirkorova
// First name: Angelika
// Group: 1DAE2
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

	void Paint();
	void Tick(double deltaTime);

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	Bitmap * m_BmpBannerPtr = nullptr, * m_BmpTextPtr = nullptr;
	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform;
	double m_Scale = 1;
	double m_Angle = 0;
	double m_Time = 0;
	bool m_PrintText = false;

};

 
