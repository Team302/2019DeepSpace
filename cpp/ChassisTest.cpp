#include "ChassisTest.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include "subsys/chassis/DragonChassis.h"

ChassisTest::ChassisTest ()
{
    m_chassis = new DragonChassis;
}

void ChassisTest::Init (CHASSIS_PRESETS)
{
    m_ChassisCounts = 0;

    m_isDone = false;

    double left = 0.0;
    double right = 0.0;
    m_chassisPresets = CHASSIS_PRESETS;
}

void ChassisTest::Execute ()
{
    switch (m_chassisPresets)
    {
        case CHASSIS_FORWARDS :
            left = .5;
            right = .5;
            break;

        case CHASSIS_BACKWARDS :
            left = -.5;
            right = -.5;
            break;

        case CHASSIS_LEFT : 
            left = -.5;
            right = .5;
            break;

        case CHASSIS_RIGHT :
            left = .5;
            right = -.5;
            break;

        case CHASSIS_STOP :
            left = 0;
            right = 0;
            break;

        default :
            break;
    }
    SetLeftRightMagnitudes(left, right);
}
//TODO #1 Use enum to set speeds based on what direction we need to move
bool ChassisTest::IsDone ()
{
    if (m_isDone = true)
    {
        SetLeftRightMagnitudes(0, 0);
        printf ("Automated Systems Test Complete \n");
    }
}



