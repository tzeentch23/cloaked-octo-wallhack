//-----------------------------------------------------------------
// Game Engine Object
// C++ Header - version v2_16 jan 2015 
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

#pragma once

//=======================================================================================
// PrecisionTimer.h by Frank Luna (C) 2008 All Rights Reserved.
// Adapted for DAE by Bart Uyttenhove
//=======================================================================================
class PrecisionTimer
{
public:
	// -------------------------
	// Constructors & Destructor
	// -------------------------
	PrecisionTimer();
	virtual ~PrecisionTimer();

	// -------------------------
	// General Methods
	// -------------------------

	// Returns the total time elapsed since reset() was called, NOT counting any
	// time when the clock is stopped.	
	double GetGameTime() const;  // in seconds

	// Returns the elapsed time since Tick was called
	double GetDeltaTime() const; // in seconds

	// Resets all 
	void Reset(); // Call before message loop.
	// Stores the start time
	void Start(); // Call when unpaused.
	// Stores the current time
	void Stop();  // Call when paused.
	// Calculates the time difference between this frame and the previous.
	// Use GetDeltaTime to retrieve that time
	void Tick();  // Call every frame.
	// Returns the state
	bool IsStopped() const;

private:
	//---------------------------
	// Private methods
	//---------------------------
	double m_SecondsPerCount;
	double m_DeltaTime;

	//---------------------------
	// Datamembers
	//---------------------------
	__int64 m_BaseTime;
	__int64 m_PausedTime;
	__int64 m_StopTime;
	__int64 m_PrevTime;
	__int64 m_CurrTime;

	bool m_bStopped;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	PrecisionTimer(const PrecisionTimer& sRef);
	PrecisionTimer& operator=(const PrecisionTimer& sRef);
};