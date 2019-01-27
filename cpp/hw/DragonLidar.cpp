/*
 * DragonLidar.cpp
 *
 *  Created on: Feb 6, 2018
 *      Author: jonah
 */

#include <hw/DragonLidar.h>

#include <frc/Counter.h>
#include <frc/DigitalInput.h>
#include <frc/DigitalOutput.h>

using namespace frc;

DragonLidar::DragonLidar
(
    LIDAR_USAGE usage,
    int         inputPin,
    int         triggerPin
)  : m_usage( usage ),
    m_pulseWidthCounter(new Counter(inputPin) ),	//Construct the counter with the desired digital input
    m_trigger( new DigitalOutput(triggerPin) )
{
	m_pulseWidthCounter->SetSemiPeriodMode(true);
	m_trigger->Set(true);
}

DragonLidar::~DragonLidar()
{
	delete m_pulseWidthCounter;
}

double DragonLidar::GetDistance()
{ // Returns distance in inches
	m_trigger->Set(false);
	return m_pulseWidthCounter->GetPeriod() * 100000.0 * 0.393701; //Converting from period to centimeters, and then to inches
}

DragonLidar::LIDAR_USAGE DragonLidar::GetUsage() const
{
    return m_usage;
}

