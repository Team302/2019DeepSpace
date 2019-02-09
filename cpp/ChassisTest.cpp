#include "ChassisTest.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include "subsys/chassis/DragonChassis.h"

ChassisTest::ChassisTest ()
{
    m_chassis = new DragonChassis;
}

void ChassisTest::Init ()
{
    
}

void ChassisTest::Execute ()
{
    SetLeftRightMagnitudes(.5, .5);
    
}

bool ChassisTest::IsDone ()
{

}



