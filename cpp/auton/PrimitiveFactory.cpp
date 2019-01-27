/*
 * PrimitiveFactory.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */

#include <auton/PrimitiveFactory.h>
#include <frc/SmartDashboard/SmartDashboard.h>
//Team 302 includes
#include <auton/DriveDistance.h>
#include <auton/DriveToLidarDistance.h>
#include <auton/DriveTime.h>
#include <auton/PrimitiveEnums.h>
#include <auton/PrimitiveParser.h>
#include <auton/DoNothing.h>
#include <auton/HoldPosition.h>
#include <auton/TurnAngle.h>
#include <auton/DriveToWall.h>
#include <auton/IPrimitive.h>

PrimitiveFactory* PrimitiveFactory::m_instance = nullptr;

PrimitiveFactory* PrimitiveFactory::GetInstance() {
	if (PrimitiveFactory::m_instance == nullptr) {					//If we do not have an instance
		PrimitiveFactory::m_instance = new PrimitiveFactory();		//Create a new instance
	}
	return PrimitiveFactory::m_instance;							//Return said instance
}

PrimitiveFactory::PrimitiveFactory() :
				m_doNothing(nullptr),
				m_driveTime(nullptr),
				m_driveDistance(nullptr),
				m_turnAngle(nullptr),
				m_holdPosition(nullptr),
				m_driveToWall(nullptr),
				m_driveLidarDistance( nullptr )
{
}

PrimitiveFactory::~PrimitiveFactory() {
	PrimitiveFactory::m_instance = nullptr; //todo: do we have to delete this pointer?
}

IPrimitive* PrimitiveFactory::GetIPrimitive(PrimitiveParams* primitivePasser)
{
	IPrimitive* primitive = nullptr;
	switch (primitivePasser->GetID())				//Decides which primitive to get or make
	{
	case DO_NOTHING:
		if (m_doNothing == nullptr)
		{
			m_doNothing = new DoNothing();
		}
		primitive =  m_doNothing;
		break;

	case DRIVE_TIME:
		if (m_driveTime == nullptr)
		{
			m_driveTime = new DriveTime();
		}
		primitive = m_driveTime;
		break;

	case DRIVE_DISTANCE:
		if (m_driveDistance == nullptr)
		{
			m_driveDistance = new DriveDistance();
		}
		primitive = m_driveDistance;
		break;

    case TURN_ANGLE_ABS:
        if (m_turnAngle == nullptr)
        {
            m_turnAngle = new TurnAngle();
        }
        primitive = m_turnAngle;
        break;

    case TURN_ANGLE_REL:
        // TODO: need new primitive
        if (m_turnAngle == nullptr)
        {
            m_turnAngle = new TurnAngle();
        }
        primitive = m_turnAngle;
        break;

	case HOLD_POSITION:
		if (m_holdPosition == nullptr)
		{
			m_holdPosition = new HoldPosition();
		}
		primitive = m_holdPosition;
		break;

    case DRIVE_TO_WALL:
        if (m_driveToWall == nullptr)
        {
            m_driveToWall = new DriveToWall();
        }
        primitive = m_driveToWall;
        break;

    case DRIVE_LIDAR_DISTANCE:
        if (m_driveLidarDistance == nullptr)
        {
            m_driveLidarDistance = new DriveToLidarDistance();
        }
        primitive = m_driveLidarDistance;
        break;

	default:
		break;
	}
	return primitive;

}
