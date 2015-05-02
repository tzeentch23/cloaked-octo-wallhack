//-----------------------------------------------------------------
// Game File
// C++ Source - Roguelight.cpp - version v2_16 jan 2015
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------
#include "stdafx.h"		// this include must be the first include line of every cpp file (due to using precompiled header)
//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Roguelight.h"					
#include "Elf.h"
#include "Enemy.h"
#include "Shadyguy.h"
#include "Moss.h"
#include "Spike.h"
#include "Collectible.h"
#include <fstream>
#include <string>
//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//-----------------------------------------------------------------
// Roguelight methods																				
//-----------------------------------------------------------------

Roguelight::Roguelight()
{

}

Roguelight::~Roguelight()																						
{

}

void Roguelight::GameInitialize(GameSettings &gameSettings)
{
	gameSettings.SetWindowTitle(String("Roguelight - Kirkorova Angelika, 1DAE2"));
	gameSettings.SetWindowWidth((int)(m_Width));
	gameSettings.SetWindowHeight((int)(m_Height));
	gameSettings.EnableConsole(false);
	gameSettings.EnableAntiAliasing(true);
}

void Roguelight::GameStart()
{
	m_ArrowArr.push_back(new Collectible(DOUBLE2(1777, 577), Collectible::Type::ARROWS));
	m_CoinArr.push_back(new Collectible(DOUBLE2(1777, 450), Collectible::Type::COINS));
	m_HeartArr.push_back(new Collectible(DOUBLE2(1777, 500), Collectible::Type::HEARTS));
	//dai da parse-nem collectibelite shtotot tam zapecnah
	//ne e li kato drugite? amiiii
	m_BmpLvlPtr = new Bitmap(String("./resources/levelmap.png"));

	m_ShadyGuyBmpPtr = new Bitmap(String("./resources/spritesElf.png"));
	DOUBLE2 elfSpawn(m_BmpLvlPtr->GetWidth()/2+200, 20);
	m_ElfPtr = new Elf(elfSpawn);
	
	m_ActLevelPtr = new PhysicsActor(DOUBLE2(0, 0), 0, BodyType::STATIC);	
	m_ActLevelPtr->AddSVGShape(String("./resources/LevelSVG.svg"), 0 ,0.2, 0);

	m_CameraDimension.topLeft.x = m_Width / 2;
	m_CameraDimension.topLeft.y = m_Height / 2;
	m_CameraDimension.bottomRight.x = m_BmpLvlPtr->GetWidth() - m_Width / 2;
	m_CameraDimension.bottomRight.y = m_BmpLvlPtr->GetHeight() - m_Height / 2;
	cameraSize = DOUBLE2(m_Width, m_Height);
	LoadMoss();
	LoadSpike();
	LoadCollectible(Collectible::ARROWS, String("./resources/Arrows_Positions.txt"), m_ArrowArr);
	LoadCollectible(Collectible::COINS, String("./resources/Coins_Positions.txt"), m_CoinArr);
	LoadCollectible(Collectible::HEARTS, String("./resources/Hearts_Positions.txt"), m_HeartArr);

	//LoadShadyguys();
	//ne e li onzi trup tam vdiasno? da amam ne pomnish li che v nachaloto skoka zatva ne raboteshe ne
	elfSpawn.x += 50;
	m_Enemies.push_back(new Shadyguy(elfSpawn, m_ShadyGuyBmpPtr));
}

void Roguelight::GameEnd()
{
	delete m_ActLevelPtr;
	m_ActLevelPtr = nullptr;
	delete m_BmpLvlPtr;
	m_BmpLvlPtr = nullptr;
	delete m_ElfPtr;
	m_ElfPtr = nullptr;
	delete m_ActLevelPtr;
	m_ActLevelPtr = nullptr;
	m_MossArr.clear();
	m_SpikeArr.clear();
	m_ArrowArr.clear();
	m_CoinArr.clear();
	m_HeartArr.clear();
}


void Roguelight::GameTick(double deltaTime)
{
	m_ElfPtr->Tick(deltaTime);
	m_ElfPos = m_ElfPtr->GetPosition();

	if (GAME_ENGINE->IsKeyboardKeyPressed('P'))
	{
		m_IsPhysicsDebudRendering = !m_IsPhysicsDebudRendering;
		GAME_ENGINE->EnablePhysicsDebugRendering(m_IsPhysicsDebudRendering);
	}

	//Camera
	
	
	/*	if (GAME_ENGINE->IsKeyboardKeyDown(VK_PRIOR))
		{
			m_CameraScale -= 0.05;
		}

		if (GAME_ENGINE->IsKeyboardKeyDown(VK_NEXT))
		{
			m_CameraScale += 0.05;
		}
	*/
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_UP))
		{
			m_CameraPos.y -= 5;
		}

		if (GAME_ENGINE->IsKeyboardKeyDown(VK_DOWN))
		{
			m_CameraPos.y += 5;
		}

		if (GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT))
		{
			m_CameraPos.x -= 5;
		}

		if (GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
		{
			m_CameraPos.x += 5;
		}
		if (GAME_ENGINE->IsKeyboardKeyDown('R'))
		{
			m_CameraAngle += 0.2;
		}
		if (GAME_ENGINE->IsKeyboardKeyDown('T'))
		{
			m_CameraAngle -= 0.2;
		}


		if (((m_ElfPos.x + MAX_RIGHT) < m_BmpLvlPtr->GetWidth()) && ((m_ElfPos.x - MIN_LEFT) >= 0))
		{
			m_CameraPos.x = m_ElfPos.x;
		}

		if (1 && (m_ElfPos.y < m_Height - cameraSize.y)) 
		{
			m_CameraPos.y = m_ElfPos.y;
		}

		cameraSize *= m_CameraScale;

		if (0 && cameraSize.y / m_CameraScale < m_Height) 
		{
			cameraSize.y = m_Height;
			m_CameraScale = cameraSize.y / m_Height;
		}

		if (m_CameraPos.y < m_Height - cameraSize.y / 2)
		{
			m_CameraPos.y = cameraSize.y / 2;
		}
		if (m_CameraPos.y > cameraSize.y / 2)
		{
			m_CameraPos.y = cameraSize.y / 2;
		}
		if (m_CameraPos.x < cameraSize.x / 2)
		{
			m_CameraPos.x = cameraSize.x / 2;
		}
		if (m_CameraPos.x > m_BmpLvlPtr->GetWidth() - cameraSize.x / 2)
		{
			m_CameraPos.x = m_BmpLvlPtr->GetWidth() - cameraSize.x / 2;
		}
		

		for (size_t i = 0; i < m_ArrowArr.size(); i++)
		{

			if (!m_ArrowArr[i]->IsConsumed())
			{
				m_ArrowArr[i]->Tick(deltaTime);
			}
		}
		for (size_t i = 0; i < m_CoinArr.size(); i++)
		{

			if (!m_CoinArr[i]->IsConsumed())
			{
				m_CoinArr[i]->Tick(deltaTime);
			}
		}
		for (size_t i = 0; i < m_HeartArr.size(); i++)
		{
			if (!m_HeartArr[i]->IsConsumed())
			{
				m_HeartArr[i]->Tick(deltaTime);
			}
		}
	}

void Roguelight::GamePaint(RECT rect)
{
	String Pos = String(m_ElfPos.x) + String(" ") + String(m_ElfPos.y);
	GAME_ENGINE->DrawBitmap(m_BmpLvlPtr, 0, 0);
	m_ElfPtr->Paint();
	Camera();

	for (size_t i = 0; i < m_MossArr.size(); i++)
	{
		m_MossArr[i]->Paint();
	}

	for (size_t i = 0; i < m_SpikeArr.size(); i++)
	{
		m_SpikeArr[i]->Paint();
	}

	for (size_t i = 0; i < m_ArrowArr.size(); i++)
	{
		if (!m_ArrowArr[i]->IsConsumed())
			m_ArrowArr[i]->Paint();
	}

	for (size_t i = 0; i < m_CoinArr.size(); i++)
	{
		if (!m_CoinArr[i]->IsConsumed())
			m_CoinArr[i]->Paint();
	}

	for (size_t i = 0; i < m_HeartArr.size(); i++)
	{
		if (!m_HeartArr[i]->IsConsumed())
			m_HeartArr[i]->Paint();
	}
	for (size_t i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies[i]->Paint();
	}
}

void Roguelight::Camera() 
{
	matCamRotate.SetAsRotate(m_CameraAngle);
	matCamTranslate.SetAsTranslate(m_ElfPos);
	matCamScale.SetAsScale(m_CameraScale);
	matPivot.SetAsTranslate(-GAME_ENGINE->GetWidth() / 2, -GAME_ENGINE->GetHeight() / 2);
	matCamera = matPivot* matCamScale * matCamRotate * matCamTranslate;
	matCamWorldTransform = matCamera.Inverse();
	GAME_ENGINE->SetViewMatrix(matCamWorldTransform);
	}


void Roguelight::LoadMoss() 
{
	std::wifstream ifileMoss;
	ifileMoss.open("./resources/Moss_Positions.txt");
	std::wstring extractedLine;
	while (ifileMoss.eof() == false)
	{
		std::getline(ifileMoss, extractedLine);
		int splitPos = extractedLine.find(',');
		if (splitPos == -1) 
		{

			OutputDebugString(String("Invalid coords:") + String(extractedLine.c_str()));
			continue;
		}
		double x = stod(extractedLine.substr(0, splitPos)); 
		double y = stod(extractedLine.substr(splitPos+1, extractedLine.length()));
		y += 30;
		m_MossArr.push_back(new Moss(DOUBLE2(x, y)));

	}
}
void Roguelight::LoadSpike()
{
	std::wifstream ifileSpike;
	ifileSpike.open("./resources/Spikes_Positions.txt");
	std::wstring extractedLine;
	while (ifileSpike.eof() == false)
	{
		std::getline(ifileSpike, extractedLine);
		int splitPos = extractedLine.find(',');
		if (splitPos == -1)
		{
			OutputDebugString(String("Invalid coords:") + String(extractedLine.c_str()));
			continue;
		}
		double x = stod(extractedLine.substr(0, splitPos));
		double y = stod(extractedLine.substr(splitPos + 1, extractedLine.length()));
		y += 17;
		m_SpikeArr.push_back(new Spike(DOUBLE2(x, y)));

	}
	OutputDebugString(String(m_SpikeArr.size()) + String("Spikes\n"));

}
void Roguelight::LoadCollectible(Collectible::Type type, String & file, std::vector<Collectible *> & arrayPtr)
{//ne bqh sigurna kak da go napravq po optimalen nachin
	std::wifstream ifileCollectible;

	std::wstring extractedLine;
	double x, y;
	

	ifileCollectible.open(file.C_str());
	while (ifileCollectible.eof() == false)
	{
		std::getline(ifileCollectible, extractedLine);
		int splitPos = extractedLine.find(',');
		if (splitPos == -1)
		{
			OutputDebugString(String("Invalid coords:") + String(extractedLine.c_str()));
			continue;
		}

		x = stod(extractedLine.substr(0, splitPos));
		y = stod(extractedLine.substr(splitPos + 1, extractedLine.length()));
		arrayPtr.push_back(new Collectible(DOUBLE2(x, y), type));
		
	}
	OutputDebugString(String(type) + String(" ") + String(arrayPtr.size()) + String("\n"));
}


bool readPos(std::wifstream & ifileCollectible, DOUBLE2 & res) 
{

	std::wstring extractedLine;
	std::getline(ifileCollectible, extractedLine);
	int splitPos = extractedLine.find(',');
	if (splitPos == -1)
	{
		OutputDebugString(String("Invalid coords:") + String(extractedLine.c_str()));
		return false;
	}//shtto nqma namespace stava taka chakaj malko de :)

	int x = stod(extractedLine.substr(0, splitPos));
	int y = stod(extractedLine.substr(splitPos + 1, extractedLine.length()));
	res.x = x;
	res.y = y;
	return true;
}

void Roguelight::LoadShadyguys() 

//napravo shte gi loadnem o t txt imash li gi?da ok.. samo sekunda predi ttova
{
	//taka po-malko copy/paste
	//niama namespace zashtoto .. moje i da mu slojish, no togava shte e ia obiavish i v header-a tazi funkcia
	//i tia stava chast ot klasa.. a v mommennta e samo lokalna za cpp-to, nikoj drug ne ia vixda..
	//ako te obyrkva - sloji i..baq (:
	//prosto v ediniat sluchaj e obiavena v headera, i tozi metod si e chast ot klasa..za
	//a/ /taka  e samo edna funkcia, hvyrchashta, vijda se samo tuk..qsmno ama shto samo s booleani satava
	//a tova e podloto.. poneje nas ni interesuva dali e uspeshno e parsnala reda si pravim DOUBLE2-to predvaritelno
	//i podavame & (reference)-a mu na funciata, tia ako parsne - popylva x-y na pos-a, ako ne - taka ili inache skipvame rounda--
	//ako ne te kefi - kopi/pejstni kakto predi, prosto mi pishna.. a shto ne metod readpos prosto normalen
	//shtoto ako ne e uspeshen kakvo shte vyrnem? ot
//ia pak vyprosa ? :) normalen metod s namespace? obiashinh po-gore.. principno e izlisheno.. ako iskash - sloji go.. no go napravi static.. moje da se polzva i niakyde drugade..
	//chakaj da vidim che raboti.. posle shte go promenim..
	//risuvame li gi? ne,, ama aktiorite trqbvashe da sa tam
	std::wifstream ifileCollectible;
	ifileCollectible.open("./resources/Shadyguy_Positions.txt");
	while (ifileCollectible.eof() == false)
	{
		DOUBLE2 pos;
		if (readPos(ifileCollectible, pos))
		{
			m_Enemies.push_back(new Shadyguy(pos, m_ShadyGuyBmpPtr));
		}
	}
//dai da probvame da gi risuvame, niama logika da e ot tova.. znam, ok, daj risunkata
	

}