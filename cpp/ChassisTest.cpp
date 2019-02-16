#include "ChassisTest.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include "subsys/chassis/DragonChassis.h"

ChassisTest::ChassisTest ()
{
    m_chassis = new DragonChassis;
}

void ChassisTest::Init (CHASSIS_PRESETS)
{
    m_forwardCounts = 0;
    m_backwardsCounts = 0;
    m_leftCounts = 0;
    m_rightCounts = 0;

    m_isDoneForwards = false;
    m_isDoneBackwards = false;
    m_isDoneLeft = false;
    m_isDoneRight = false;

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

    if (SetLeftRightMagnitudes(.5, .5))
    {
        m_forwardCounts++;
        GetDistance((left+right) /2);
        if (m_forwardCounts == 1500);
        {
            printf("Driving Forwards complete \n");
        }
    }
    else if (SetLeftRightMagnitudes(-.5, -.5))
    {
        m_backwardsCounts++;
        GetDistance((left+right) /2);
        if (m_backwardsCounts == 1500);
        {
            printf("Driving Backwards complete \n");
        }
    }
    else if (SetLeftRightMagnitudes(-.5, .5))
    {
        m_leftCounts++;
        GetDistance((left+right) /2);
        if (m_leftCounts == 1500);
        {
            printf("Driving Left complete \n");
        }
    }
    else if (SetLeftRightMagnitudes(.5, -.5))
    {
        m_rightCounts++;
        GetDistance((left+right) /2);
        if (m_rightCounts == 1500);
        {
            printf("Driving Right complete \n");
        }
    }
}
//TODO #1 Use enum to set speeds based on what direction we need to move
bool ChassisTest::IsDone ()
{
    if (m_forwardCounts == true && m_backwardsCounts == true && m_leftCounts == true && m_rightCounts == true)
    {
        SetLeftRightMagnitudes(0, 0);
        printf ("Automated Systems Test Complete \n");
    }
}



