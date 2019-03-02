/*
 * TurnAngle.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */

//Includes
#include <cmath>
#include <frc/SmartDashboard/SmartDashboard.h>
//Team302 includes
#include <auton/TurnAngle.h>
#include <auton/PrimitiveFactory.h>
#include <subsys/chassis/DragonChassis.h>
//#include <subsys/ChassisFactory.h>
//#include <utils/LimitValue.h>

TurnAngle::TurnAngle() :
	//	m_chassis(ChassisFactory::GetIChassis()),
		m_chassis(nullptr),
		m_targetAngle(0.0),
		m_targetDistance(0.0),
		m_targetSpeed(0.0),
		m_leftSpeed(0.0),
		m_rightSpeed(0.0),
		m_minTimeout(1),
		m_maxTimeout(3),
		m_speedMultiplier(0.0),
		m_lastAngle(0.0),
		m_isDone(false)
{
}

void TurnAngle::Init(PrimitiveParams* params) {
	m_isDone = false;
	m_chassis->SetDriveMode( IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
	//m_targetAngle = m_chassis->GetTargetHeading() + params->GetHeading();
	m_targetDistance = m_chassis->GetDistance();
	//m_chassis->SetTargetHeading(m_targetAngle);
	m_speedMultiplier = TURN_ANGLE_SPEED_MULTIPLIER;

	m_chassis->EnableBrakeMode(false);

	m_minTimeout = 1;
	m_maxTimeout = 3.5;
}

void TurnAngle::Run() //best method ever. Does nothing, and should do nothing... NOT ANYMORE, BUDDY!
{
	//float deltaAngle = m_targetAngle - m_chassis->GetHeading();
	float deltaAngle = m_targetAngle;
	m_leftSpeed = deltaAngle * m_speedMultiplier;
	m_rightSpeed = -deltaAngle * m_speedMultiplier;

	float distanceError = m_chassis->GetDistance() - m_targetDistance;

	m_leftSpeed -= distanceError * 0.1;
	m_rightSpeed -= distanceError * 0.1;

	if (deltaAngle > 0) {
		m_leftSpeed += MINIMUM_SPEED;
		m_rightSpeed -= MINIMUM_SPEED;
	} else {
		m_leftSpeed -= MINIMUM_SPEED;
		m_rightSpeed += MINIMUM_SPEED;
	}

	//m_chassis->SetVelocityParams(PROPORTIONAL_COEFF, INTREGRAL_COEFF, DERIVATIVE_COEFF, FEET_FORWARD_COEFF, m_leftSpeed, m_rightSpeed);

	m_minTimeout -= IPrimitive::LOOP_LENGTH;
	m_maxTimeout -= IPrimitive::LOOP_LENGTH;
}

bool TurnAngle::IsDone() {
	if (!m_isDone) {
		//float absDeltaAngle = std::abs(m_targetAngle - m_chassis->GetHeading());
		float absDeltaAngle = std::abs(m_targetAngle);
		if (absDeltaAngle < ANGLE_THRESH) {
			m_isDone = true;
			m_lastAngle = m_targetAngle;
			m_chassis->SetDriveMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
			m_chassis->SetLeftRightMagnitudes( m_leftSpeed, m_rightSpeed );
		}
	}
	return (m_isDone && m_minTimeout < (IPrimitive::LOOP_LENGTH / 2)) || m_maxTimeout < (IPrimitive::LOOP_LENGTH / 2);
}


void TurnAngle::SetTargetAngle
(
    double      angle
)
{
    m_isDone = false;
    m_chassis->SetDriveMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
    //m_targetAngle = m_chassis->GetTargetHeading() + angle;
    m_targetAngle = angle;
    m_targetDistance = m_chassis->GetDistance();
    //m_chassis->SetTargetHeading(m_targetAngle);
    m_speedMultiplier = TURN_ANGLE_SPEED_MULTIPLIER;

}

