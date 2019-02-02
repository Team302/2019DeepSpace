/*
 * DragonUltrasonic.h
 *
 *  Created on: Feb 6, 2018
 *      Author: jonah
 */

#ifndef SRC_SUBSYS_COMPONENTS_DRAGONULTRASONIC_H_
#define SRC_SUBSYS_COMPONENTS_DRAGONULTRASONIC_H_

#include <frc/AnalogInput.h>
#include <hw/IDragonUltrasonic.h>

using namespace frc;

/*
 * This class takes an analog input signal on the roborio from an ultrasonic distance sensor and converts it to inches.
 * https://www.maxbotix.com/documents/HRLV-MaxSonar-EZ_Datasheet.pdf
 */

class DragonUltrasonic : public IDragonUltrasonic
{
public:
	DragonUltrasonic
	(
	    IDragonUltrasonic::ULTRASONIC_USAGE     usage,
	    int                                     analogInChannel
	);
	virtual ~DragonUltrasonic();
	double GetDistance() const override; // In inches
	IDragonUltrasonic::ULTRASONIC_USAGE GetUsage() const override;

private:
	AnalogInput*                                m_input;
	IDragonUltrasonic::ULTRASONIC_USAGE         m_usage;
};

#endif /* SRC_SUBSYS_COMPONENTS_DRAGONULTRASONIC_H_ */
