/*
 * DragonUltrasonicPWM.h
 *
 *  Created on: Feb 15, 2018
 *      Author: jonah
 */

#ifndef SRC_SUBSYS_COMPONENTS_DRAGONULTRASONICPWM_H_
#define SRC_SUBSYS_COMPONENTS_DRAGONULTRASONICPWM_H_

#include <hw/IDragonUltrasonic.h>
#include <frc/Counter.h>

class DragonUltrasonicPWM : public IDragonUltrasonic {
public:
	DragonUltrasonicPWM(IDragonUltrasonic::ULTRASONIC_USAGE usage, int digitalPinChannel);
	virtual ~DragonUltrasonicPWM();

	double GetDistance() const override;
	IDragonUltrasonic::ULTRASONIC_USAGE GetUsage() const override;

private:
	frc::Counter* m_pulseWidthCounter;
	IDragonUltrasonic::ULTRASONIC_USAGE m_usage;
};

#endif /* SRC_SUBSYS_COMPONENTS_DRAGONULTRASONICPWM_H_ */
