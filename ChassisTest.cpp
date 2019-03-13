#include "ChassisTest.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include "subsys/chassis/DragonChassis.h"

ChassisTest::ChassisTest ()
{
    m_chassis = new DragonChassis;
}

void ChassisTest::Init ()
{
    m_ChassisCounts = 0;

    m_isDone = false;
}

void ChassisTest::Execute (CHASSIS_PRESETS)
{
    SetLeftRightMagnitudes(.5, .5);
    if (SetLeftRightMagnitudes(.5, .5))
    {
        m_ChassisCounts++;
    }

    if (m_ChassisCounts == 1500)
    {
        m_isDone = true;
    }
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



