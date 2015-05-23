//-----------------------------------------------------
// Name: Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
	
//---------------------------
// Includes
//---------------------------
#include "Camera.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Camera::Camera(int levelWidth, int levelHeight) 
: m_LevelWidth(levelWidth), m_LevelHeight(levelHeight) 
{
	m_CameraDimension.topLeft.x = m_Width / 2;
	m_CameraDimension.topLeft.y = m_Height / 2;
	m_CameraDimension.bottomRight.x = levelWidth - m_Width / 2;
	m_CameraDimension.bottomRight.y = levelHeight - m_Height / 2;
	m_CameraSize = DOUBLE2(m_Width, m_Height);
	
}

Camera::~Camera()
{

}

void Camera::Adjust()
{
	matCamRotate.SetAsRotate(m_CameraAngle);
	matCamTranslate.SetAsTranslate(m_CameraPos);
	matCamScale.SetAsScale(m_CameraScale);
	matPivot.SetAsTranslate(-GAME_ENGINE->GetWidth() / 2, -GAME_ENGINE->GetHeight() / 2);
	matCamera = matPivot* matCamScale * matCamRotate * matCamTranslate;
	matCamWorldTransform = matCamera.Inverse();
	GAME_ENGINE->SetViewMatrix(matCamWorldTransform);

}

void Camera::Tick(double deltaTime, DOUBLE2 newPos)
{
	if (m_CameraScale >= 0.4)
	{
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_PRIOR))
		{
			m_CameraScale -= 0.02;
			m_CameraSize = DOUBLE2(m_Width, m_Height) * m_CameraScale;
		}
	}
	if (m_CameraScale <= 0.8)
	{
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_NEXT))
		{
			m_CameraScale += 0.02;
			m_CameraSize = DOUBLE2(m_Width, m_Height) * m_CameraScale;
			OutputDebugString(String("m_CameraSize : ") + String(m_CameraScale) + String(" ") + String(m_CameraSize.y) + String(" ") + String(m_CameraScale) + String('\n'));
		}
	}
	if (((newPos.x + MAX_RIGHT) < m_LevelWidth) && ((newPos.x - MIN_LEFT) >= 0))
	{
		m_CameraPos.x = newPos.x;
	}

	m_CameraPos.y = newPos.y;

	if (m_CameraSize.y / m_CameraScale < m_Height)
	{
		m_CameraSize.y = m_Height;
		m_CameraScale = m_CameraSize.y / m_Height;
	}

	if (m_CameraPos.y < m_Height - m_CameraSize.y / 2)
	{
		m_CameraPos.y = m_CameraSize.y / 2;
	}
	if ((m_CameraPos.y + m_CameraSize.y / 2) > m_LevelHeight)
	{
		m_CameraPos.y = m_LevelHeight - m_CameraSize.y / 2;
	}

	if (m_CameraPos.x < m_CameraSize.x / 2)
	{
		m_CameraPos.x = m_CameraSize.x / 2;
	}

	if (m_CameraPos.x > m_LevelWidth- m_CameraSize.x / 2)
	{
		m_CameraPos.x = m_LevelWidth - m_CameraSize.x / 2;
	}

	if (m_CameraPos.y > m_LevelHeight - m_CameraSize.y / 2)
	{
		m_CameraPos.y = m_LevelHeight - m_CameraSize.y / 2;
	}

	Adjust();

}

DOUBLE2 Camera::GetCameraSize()
{
	return m_CameraSize;
}


DOUBLE2 Camera::GetCameraOrigin()
{
	return m_CameraPos;
}

//-------------------------------------------------------
// ContactListener overloaded member function definitions
//-------------------------------------------------------
//void Camera::BeginContact(PhCamerasicsActor *actThisPtr, PhCamerasicsActor *actOtherPtr)
//{
//
//}
//
//void Camera::EndContact(PhCamerasicsActor *actThisPtr, PhCamerasicsActor *actOtherPtr)
//{
//
//}
//
//void Camera::ContactImpulse(PhCamerasicsActor *actThisPtr, double impulse)
//{
//
//}


