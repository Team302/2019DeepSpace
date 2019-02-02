/*
 * DragonAnalogInput.cpp
 */

#include <hw/DragonAnalogInput.h>

DragonAnalogInput::DragonAnalogInput
(
	ANALOG_SENSOR_TYPE			type,
	int 						analogID,
	float						voltageMin,
	float						voltageMax,
	float 						outputMin,
	float						outputMax
) : AnalogInput( analogID),
    m_type( type ),
	m_voltMin( voltageMin ),
	m_voltMax( voltageMax ),
	m_outMin( outputMin ),
	m_outMax( outputMax )
{
}

DragonAnalogInput::~DragonAnalogInput()
{
}

float DragonAnalogInput::GetInterpolatedValue() const
{
    float output = 0.0;
    float volts = GetVoltage();
    output = ( volts / (m_voltMax - m_voltMin) ) * (m_outMax - m_outMin) + m_outMin;
    return output;
}

