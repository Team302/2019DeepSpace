/*
 * DragonUltrasonic.cpp
 *
 *  Created on: Feb 6, 2018
 *      Author: jonah
 */

#include <hw/DragonUltrasonic.h>
#include <hw/IDragonUltrasonic.h>
#include <frc/AnalogInput.h>

using namespace frc;

DragonUltrasonic::DragonUltrasonic
(
    IDragonUltrasonic::ULTRASONIC_USAGE     usage,
    int                                     analogInChannel
) : m_input( new AnalogInput( analogInChannel )),
    m_usage( usage )
{
}

DragonUltrasonic::~DragonUltrasonic()
{
    delete m_input;
}

double DragonUltrasonic::GetDistance() const {
	return ((m_input->GetVoltage() / 0.000977) * 0.393701) / 3.454; //Convert volts to centimeters and then to inches.
}

IDragonUltrasonic::ULTRASONIC_USAGE DragonUltrasonic::GetUsage() const {
	return m_usage;
}
