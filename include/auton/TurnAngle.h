/*
 * TurnAngle.h
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */

#ifndef SRC_AUTON_TURNANGLE_H_
#define SRC_AUTON_TURNANGLE_H_

//includes
//Team302 includes
#include <subsys/chassis/DragonChassis.h>
#include <auton/IPrimitive.h>

class TurnAngle : public IPrimitive {
public:
	TurnAngle();
	virtual ~TurnAngle() = default;

    void Init(PrimitiveParams* params) override;
    void Run() override;
    bool IsDone() override;

protected:
    void SetTargetAngle
    (
        double angle
    );

private:
	const float PROPORTIONAL_COEFF  = 1.0; //0.5
	const float INTREGRAL_COEFF     = 0.0;
	const float DERIVATIVE_COEFF    = 0.0;
	const float FEET_FORWARD_COEFF  = 0.0;

    DragonChassis* m_chassis;
    float m_targetAngle;
    float m_targetDistance;
    float m_targetSpeed;
    float m_leftSpeed;
    float m_rightSpeed;
    float m_minTimeout;
    float m_maxTimeout;
    float m_speedMultiplier;
    float m_lastAngle;
    bool m_isDone;

    const float ANGLE_THRESH = 1; // +/- threshold for being at angle
    const float	MINIMUM_SPEED = 0.60; //0.55
    const float TURN_ANGLE_SPEED_MULTIPLIER = 0.000; //0.007
};

#endif /* SRC_AUTON_TURNANGLE_H_ */
