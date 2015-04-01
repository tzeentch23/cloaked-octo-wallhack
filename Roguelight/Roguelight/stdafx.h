//-----------------------------------------------------------------
// Game Engine Object
// C++ Header - version v2_16 jan 2015 
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
//#define WINDOWS7

#include <windows.h>

#undef MessageBox

#include "../Resource.h"	

// std lib includes
#include <vector>			// std lib vector
#include <string>			// std lib to_string
#include <sstream>			// std lib stringstream
#include <fstream>			// SVGParser
#include <iostream>
#include <iomanip>			// precision
#include <io.h>				// console

// WindowsSDK
#include <dwrite.h>			// Draw Text
#include <wincodec.h>		// WIC: image loading
#include <d2d1.h>
#include <d2d1helper.h>

// libs used for Direct2D
#pragma comment(lib, "d2d1.lib")			// Direct2D
#pragma comment(lib, "WindowsCodecs.lib")	// Image Loading
#pragma comment(lib, "dwrite.lib")			// Draw Text
using namespace D2D1;

// Box2D 
// copy the headers box2d map in a folder with somename:  projectdir/somepath/box2d
// additional include directories: do NOT add ./ to make this include <> work, use ./somepath instead -> bug in vs2013?
#include <Box2D/Box2D.h>
#if defined(DEBUG) | defined(_DEBUG)
#pragma comment(lib, "Box2DDebug.lib")		
#else
#pragma comment(lib, "Box2DRelease.lib")		
#endif

//! BodyType enumeration
//! @enum Box2D enumerations
enum class BodyType
{
	STATIC, DYNAMIC, KINEMATIC
};

// Define M_PI and other constants
#define _USE_MATH_DEFINES 
#include "math.h"

// Unicode defs for svg parsing
#ifdef _UNICODE
#define tstring std::wstring
#define tstringstream std::wstringstream
#else
#define tstring std::string
#define tstringstream std::stringstream
#endif

#include "EngineFiles/String.h"
#include "EngineFiles/Structs.h"
#include "EngineFiles/Box2DDebugRenderer.h"
#include "EngineFiles/InputManager.h"
#include "EngineFiles/PrecisionTimer.h"
#include "EngineFiles/GameSettings.h"
#include "EngineFiles/GameEngine.h"
#include "EngineFiles/Font.h"
#include "EngineFiles/AudioSystem.h"
#include "EngineFiles/AudioDecoder.h"
#include "EngineFiles/Bitmap.h"
#include "EngineFiles/GUIBase.h"
#include "EngineFiles/TextBox.h"
#include "EngineFiles/Button.h"
#include "EngineFiles/SVGParser.h"
#include "EngineFiles/Sound.h"
#include "EngineFiles/PhysicsActor.h"
#include "EngineFiles/PhysicsRevoluteJoint.h"
#include "EngineFiles/PhysicsPrismaticJoint.h"
#include "EngineFiles/PhysicsDistanceJoint.h"



