#pragma once
//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

//#include "ContactListener.h"
//-----------------------------------------------------
// Camera Class									
//-----------------------------------------------------
class Roguelight;
class Camera //: public ContactListener
{
public:
	Camera(int levelWidth, int levelHeight);
	virtual ~Camera( );

	// C++11 make the class non-copCameraable
	Camera( const Camera& ) = delete;
	Camera& operator=( const Camera& ) = delete;

	void Adjust();

	void Tick(double deltaTime, DOUBLE2 newPos); 
	DOUBLE2 GetCameraSize();
	DOUBLE2 GetCameraOrigin();
	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	//virtual void BeginContact(PhCamerasicsActor *actThisPtr, PhCamerasicsActor *actOtherPtr); 
	//virtual void EndContact(PhCamerasicsActor *actThisPtr, PhCamerasicsActor *actOtherPtr);   
	//virtual void ContactImpulse(PhCamerasicsActor *actThisPtr, double impulse);

	static const int GAME_WIDTH= 800;
	static const int GAME_HEIGHT = 600;

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	Roguelight *m_Game;
	MATRIX3X2 matTranslate, matRotate, matScale, matWorldTransform;

	MATRIX3X2 matCamera, matCamRotate, matCamTranslate,
		matCamScale, matPivot, matCamWorldTransform;

	double m_CameraAngle = 0;
	double m_CameraScale = 0.7;
	DOUBLE2  m_CameraPos;
	struct CameraDimension {
		DOUBLE2 topLeft;
		DOUBLE2 bottomRight;
	};

	CameraDimension m_CameraDimension;
	DOUBLE2 m_CameraSize;

	int m_Width = GAME_WIDTH;
	int m_Height = GAME_HEIGHT;

	int m_LevelWidth;
	int m_LevelHeight;

	static const int MIN_LEFT = GAME_WIDTH / 2;
	static const int MAX_RIGHT = GAME_WIDTH / 2;

};

 
