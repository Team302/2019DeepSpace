#include "ChassisTest.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include "subsys/chassis/DragonChassis.h"

ChassisTest::ChassisTest ()
{
    DragonChassis::GetInstance();
    double m_targetCounts = 0;
    double m_counts = 0;
    bool m_isDone = false;
}

void ChassisTest::Init ()
{
    m_chassisPresets = ChassisTest::CHASSIS_STOP;
}

void ChassisTest::Execute ()
{
    double left = 0.0;
    double right = 0.0;
    switch (m_chassisPresets)
    {
        case CHASSIS_FORWARDS :
            left = .5;
            right = .5;
            m_targetCounts = 1500;
            
            break;

        case CHASSIS_BACKWARDS :
            left = -.5;
            right = -.5;
            m_targetCounts = 1500;
            
            break;

        case CHASSIS_LEFT : 
            left = -.5;
            right = .5;
            m_targetCounts = 750;
            
            break;

        case CHASSIS_RIGHT :
            left = .5;
            right = -.5;
            m_targetCounts = 750;
            
            break;

        case CHASSIS_STOP :
            left = 0;
            right = 0;
            break;

        default :
            break;
    }
    SetLeftRightMagnitudes(left, right);
    m_counts++;
    if (m_counts == m_targetCounts)
    {
        m_isDone = true;
    }
}
//TODO #1 Track draw
bool ChassisTest::IsDone ()
{
    if (m_isDone = true)
    {
        SetLeftRightMagnitudes(0, 0);
        printf ("Automated Systems Test Complete \n");
    }
}


