//-----------------------------------------------------
// Name: Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------
#include "stdafx.h"		
#include <iostream>
	
//---------------------------
// Includes
//---------------------------
#include "Session.h"

//---------------------------
// Defines
//---------------------------
//#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Session * Session::m_Instance = nullptr;

Session::Session()
{
	m_Instance = this;
	m_Output.open("GameResults.txt", std::ios::out | std::ios::app);
}

Session::~Session()
{

}


void Session::Start(int health, int ammo)
{
	if (m_Output.is_open())
	{

		time_t rawtime;
		tm now;
		time(&rawtime);
 		localtime_s(&now, &rawtime);
		String date = String(now.tm_year + 1900) + String("-") + String(now.tm_mon + 1) + String("-") + String(now.tm_mday);
		String time = String(now.tm_hour) + String(":") + String(now.tm_min) + String(":") + String(now.tm_sec);

		m_Output << "<Session>" << std::endl
			<< "  <Start>" << std::endl
			<< "    <Date=\"" << date.C_str() << "\"/>" << std::endl
			<< "    <Time=\"" << time.C_str() << "\"/>" << std::endl
			<< "    <Health=\"" << health << "\"/>" << std::endl
			<< "    <Ammo=\"" << ammo << "\"/>" << std::endl
			<< "  </Start>" << std::endl;
	}
}

void Session::Stop(int health, int coins, int ammo)
{
	if (m_Output.is_open())
	{
		time_t rawtime;
		tm now;
		time(&rawtime);
		localtime_s(&now, &rawtime);
		
		String date = String(now.tm_year + 1900) + String("-") + String(now.tm_mon + 1) + String("-") + String(now.tm_mday);
		String time = String(now.tm_hour) + String(":") + String(now.tm_min) + String(":") + String(now.tm_sec);

		m_Output
			<< "  <End>" << std::endl
			<< "    <Date=\"" << date.C_str() << "\"/>" << std::endl
			<< "    <Time=\"" << time.C_str() << "\"/>" << std::endl
			<< "    <Health=\"" << health << "\"/>" << std::endl
			<< "    <Ammo=\"" << ammo << "\"/>" << std::endl
			<< "    <Coins=\"" << coins << "\"/>" << std::endl
			<< "  </End>" << std::endl
			<< "</Session>" << std::endl;

		m_Output.flush();

		m_Output.close();
	}
}

Session * Session::GetInstance()
{
	return m_Instance;
}
 