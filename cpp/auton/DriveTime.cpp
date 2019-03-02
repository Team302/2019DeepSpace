/*
 * DriveTime.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */

//Includes
//Team302 includes
#include <auton/DriveTime.h>
#include <auton/PrimitiveFactory.h>
#include <auton/PrimitiveParams.h>

DriveTime::DriveTime() :
		SuperDrive(),
		m_timeRemaining(0.0)       //Value will changed in init

{
}

void DriveTime::Init(PrimitiveParams* params) {
	SuperDrive::Init(params);
	//Get timeRemaining from m_params
	m_timeRemaining = params->GetTime();
}

bool DriveTime::IsDone() {
	m_timeRemaining -= LOOP_LENGTH;						// Decrement time remaining
	return ((m_timeRemaining <= (LOOP_LENGTH / 2.0)));	// Return true when time runs out
}
