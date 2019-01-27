/*
 * DragonUltrasonicPWM.cpp
 *
 *  Created on: Feb 15, 2018
 *      Author: jonah
 */

#include <hw/DragonUltrasonicPWM.h>
#include <frc/Counter.h>

DragonUltrasonicPWM::DragonUltrasonicPWM(IDragonUltrasonic::ULTRASONIC_USAGE usage, int digitalPinChannel) :
m_pulseWidthCounter(new frc::Counter(digitalPinChannel)),
	m_usage(usage)
{
	m_pulseWidthCounter->SetSemiPeriodMode(true);
}

DragonUltrasonicPWM::~DragonUltrasonicPWM() {
	delete m_pulseWidthCounter;
}

double DragonUltrasonicPWM::GetDistance() const {
	return m_pulseWidthCounter->GetPeriod() * 100000.0 * 0.393701;
}

IDragonUltrasonic::ULTRASONIC_USAGE DragonUltrasonicPWM::GetUsage() const {
	return m_usage;
}
