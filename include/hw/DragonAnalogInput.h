/*
 * DragonAnalogInput.h
 */

#ifndef SRC_SUBSYS_COMPONENTS_DRAGONANALOGINPUT_H_
#define SRC_SUBSYS_COMPONENTS_DRAGONANALOGINPUT_H_

#include <vector>
#include <frc/AnalogInput.h>

using namespace frc;

class DragonAnalogInput : AnalogInput
{
	public:
		enum ANALOG_SENSOR_TYPE
		{
			UNKNOWN_ANALOG_TYPE = -1,
			ANALOG_GENERAL,
			ANALOG_GYRO,
			POTENTIOMETER,
			PRESSURE_GAUGE,
			MAX_ANALOG_TYPES
		};


		DragonAnalogInput
		(
			ANALOG_SENSOR_TYPE			type,
			int 						analogID,
		    float						voltageMin,
		    float						voltageMax,
		    float 						outputMin,
		    float						outputMax
		);
		virtual ~DragonAnalogInput();
		float GetInterpolatedValue() const;

	private:
		ANALOG_SENSOR_TYPE				m_type;
		float							m_voltMin;
		float							m_voltMax;
		float							m_outMin;
		float							m_outMax;
};
typedef std::vector<DragonAnalogInput*> DragonAnalogInputVector;

#endif /* SRC_SUBSYS_COMPONENTS_DRAGONANALOGINPUT_H_ */
