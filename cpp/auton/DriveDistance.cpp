/*
 * DriveDistance.cpp
 *
 *  Created on: Jan 18, 2018
 *      Author: jonah
 */

//Includes
#include <cmath>
#include <frc/SmartDashboard/SmartDashboard.h>

//Team302 includes
#include <auton/DriveDistance.h>
//#include <subsys/ChassisFactory.h>
#include <subsys/chassis/DragonChassis.h>

DriveDistance::DriveDistance() :
	SuperDrive(),
	m_params(nullptr),
	m_targetDistance(0),
	m_initialDistance(0),
	m_timeRemaining(0),
	m_minSpeedCountTime(0), //will be changed in init
	m_underSpeedCounts(0),
	m_startHeading(0),
	m_endHeading(0),
	m_minSpeed(0),
	m_arcing(false)
{
}

void DriveDistance::Init(PrimitiveParams* params) {
	SuperDrive::Init(params);
	m_arcing = std::abs(params->GetHeading()) > 0.1;
	m_startHeading = 0.0; //ChassisFactory::GetIChassis()->GetTargetHeading();
	m_endHeading = m_startHeading + params->GetHeading();

	m_minSpeedCountTime = MIN_SPEED_COUNT_TIME;
	m_underSpeedCounts = 0;
	m_params = params;
	//Get parameters from params
	m_targetDistance = params->GetDistance();
	m_initialDistance = 0.0; //ChassisFactory::GetIChassis()->GetDistance();
//	m_timeRemaining = (params->GetDistance() / params->GetDriveSpeed()) * TIMEOUT_MULTIPIER; //TODO: physically test this this
}

void DriveDistance::Run() {
	SuperDrive::Run();

	if (m_arcing) {
		//Calculate progress from 0 to 1
		float progress = 1.0;//std::abs(ChassisFactory::GetIChassis()->GetDistance() - m_initialDistance);
		progress /= std::abs(m_targetDistance); //progress = progress / targetDistance

		float newTargetHeading = 0;
		//Linear interpolation between start heading and end heading based on progress
		newTargetHeading += (1.0 - progress) * m_startHeading;// newTargetheading = newTargetHeading + (1.0 - progress) * m_startHeading
		newTargetHeading += (progress) * m_endHeading;
		//ChassisFactory::GetIChassis()->SetTargetHeading(newTargetHeading);
	}

//	frc::SmartDashboard::PutBoolean("arcing", m_arcing);
//	frc::SmartDashboard::PutNumber("THIS SHOULD BE 0 DURNING SWITCH", m_params->GetHeading());

	CalculateSlowDownDistance();

	if (m_minSpeedCountTime <= 0) {
		//if (std::abs(ChassisFactory::GetIChassis()->GetVelocity()) < SPEED_THRESHOLD) {
		//	m_underSpeedCounts++;
		//}
	}
	m_minSpeedCountTime -= IPrimitive::LOOP_LENGTH;
}

bool DriveDistance::IsDone() {
	float progress = 1.0; //ChassisFactory::GetIChassis()->GetDistance() - m_initialDistance;
	bool reachedTarget = std::abs(progress) > std::abs(m_targetDistance);
	m_timeRemaining -= IPrimitive::LOOP_LENGTH;

	bool notMoving = m_underSpeedCounts >= UNDER_SPEED_COUNT_THRESHOLD;
	bool done = reachedTarget || notMoving;
	if (done) {
		//ChassisFactory::GetIChassis()->SetTargetHeading(m_endHeading);
	}
	return done;
}

void DriveDistance::CalculateSlowDownDistance() {

	float currentVel = 1.0;// ChassisFactory::GetIChassis()->GetVelocity();
	float decelTime = currentVel / SuperDrive::INCHES_PER_SECOND_SECOND;

	float decelDist = std::abs(((currentVel - m_minSpeed)) * decelTime * DECEL_TIME_MULTIPLIER);
	float currentDistance = 1.0; //std::abs(ChassisFactory::GetIChassis()->GetDistance() - m_initialDistance);
	float distanceRemaining = std::abs(m_targetDistance - currentDistance);

	if (distanceRemaining <= decelDist)
	{
		SuperDrive::SlowDown();
	}
}

void DriveDistance::SetDistance
(
    double distance
)
{
    m_targetDistance = distance;
}

