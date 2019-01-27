/*
 * SuperDrive.h
 *
 *  Created on: Jan 18, 2018
 *      Author: jonah
 */

#ifndef SRC_AUTON_SUPERDRIVE_H_
#define SRC_AUTON_SUPERDRIVE_H_

//Includes
//Team302 includes
#include <subsys/chassis/DragonChassis.h>
#include <auton/IPrimitive.h>

class SuperDrive : public IPrimitive {
public:
	void Init(PrimitiveParams* params) override;
	void Run() override;
	bool IsDone() override;
	void SlowDown();
	bool ReachedTargetSpeed();
//	float GetAccelDecelTime();

	const float GYRO_CORRECTION_CONSTANT = 6; //2.3
	const float INCHES_PER_SECOND_SECOND = 120; //120
	const float MIN_SPEED_SLOWDOWN       = 13;

protected: //TODO: why is this protected?
	SuperDrive();
	virtual ~SuperDrive() = default;

private:
	//TODO: figure out where to get PID params
	const float PROPORTIONAL_COEFF  = 12.0; //16
	const float INTREGRAL_COEFF     = 0;
	const float DERIVATIVE_COEFF    = 0.0; //.16
	const float FEET_FORWARD_COEFF  = 0.0;

	DragonChassis* m_chassis;

	float m_targetSpeed;
	float m_currentSpeed;
	float m_speedOffset;

	float m_leftSpeed;
	float m_rightSpeed;

	float m_currentHeading;
	float m_startHeading;

	bool m_slowingDown;
	bool m_reachedTargetSpeed;
	float m_accelDecelTime;
	float m_currentTime;
	float m_minSpeedSlowdown;
};

#endif /* SRC_AUTON_SUPERDRIVE_H_ */
