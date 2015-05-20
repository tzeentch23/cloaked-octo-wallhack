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
// PauseScreen Class									
//-----------------------------------------------------
class PauseScreen //: public ContactListener
{

public:
	PauseScreen( );
	virtual ~PauseScreen( );

	// C++11 make the class non-copPauseScreenable
	PauseScreen( const PauseScreen& ) = delete;
	PauseScreen& operator=( const PauseScreen& ) = delete;

	void Paint();
	void Tick(double deltaTime);
	bool IsActive();
	void SetActive(bool isActive);

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	Bitmap * m_BmpBannerPtr = nullptr;
	MATRIX3X2 matTranslate, matRotate, matScale, matPivot, matWorldTransform;
	double m_Scale = 1;
	double m_Angle = 0;
	bool m_IsActive = false;
};

 
