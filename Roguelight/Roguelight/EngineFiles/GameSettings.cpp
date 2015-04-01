#include "stdafx.h"



//------------------------------------------------------------------------------
// GameSettings class definitions. Encapsulated the user defined game settings
//------------------------------------------------------------------------------
GameSettings::GameSettings() :
m_WindowTitle("Game Engine"),
m_WindowWidth(853),
m_WindowHeight(480),
m_bEnableConsole(false),
m_bVSync(true)
{

}

GameSettings::~GameSettings()
{

}

void GameSettings::SetWindowTitle(const String& titleRef)
{
	m_WindowTitle = String(titleRef);
}

void GameSettings::SetWindowWidth(int width)
{
	m_WindowWidth = width;
}

void GameSettings::SetWindowHeight(int height)
{
	m_WindowHeight = height;
}

void GameSettings::EnableConsole(bool state)
{
	m_bEnableConsole = state;
}

void GameSettings::EnableVSync(bool state)
{
	m_bVSync = state;
}

void GameSettings::EnableAntiAliasing(bool state)
{
	m_bEnableAntiAliasing = state;
}

//void GameSettings::EnablePhysicsDebugRendering(bool state)
//{
//	m_EnableDebugRendering = state;
//}

String GameSettings::GetWindowTitle()
{
	return m_WindowTitle;
}

int GameSettings::GetWindowWidth()
{
	return m_WindowWidth;
}

int GameSettings::GetWindowHeight()
{
	return m_WindowHeight;
}

bool GameSettings::IsConsoleEnabled()
{
	return m_bEnableConsole;
}

bool GameSettings::IsVSync()
{
	return m_bVSync;
}

bool GameSettings::IsAntiAliasingEnabled()
{
	return m_bEnableAntiAliasing;
}

//bool GameSettings::IsDebugRenderingEnabled()
//{
//	return m_EnableDebugRendering;
//}