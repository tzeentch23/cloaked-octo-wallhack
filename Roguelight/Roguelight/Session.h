#pragma once
//-----------------------------------------------------
// Name:Kirkorova
// First name:Angelika
// Group: 1DAE2
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <fstream>
#include <map>
//#include "ContactListener.h"
//-----------------------------------------------------
// Session Class									
//-----------------------------------------------------
class Session //: public ContactListener
{
public:
	Session( );
	virtual ~Session( );

	// C++11 make the class non-copSessionable
	Session( const Session& ) = delete;
	Session& operator=( const Session& ) = delete;

	void Start(int health, int ammo);
	void Stop(int health, int coins, int ammo);
	void Dead(DOUBLE2 pos); //if elf is dead
	static Session * GetInstance();
private: 
	static Session * m_Instance;
	std::wofstream m_Output;

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	
};

 
