#include "WristTest.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

WristTest::WristTest ()
{
    Wrist = new Wrist;
}

void WristTest::Run(PLACEMENT_HEIGHT hgt) 
{
    if (hgt != m_prevhgt)
    {
        Wrist -> Set(hgt);
        m_counts = 0;
        m_isDone = false;
    }
    else
    {
        m_counts++;
    }

    if (m_counts > 9)
    {
        double angle = Wrist -> Get();
        m_isDone = true;
        printf ("Target %d Angle %g \n", hgt, angle);
    }
    m_prevhgt = hgt;
    
}

bool WristTest::IsDone() 
{
    if (m_isDone = true)
    {
    printf ('Automated Systems Test Completed');
    }
}

//#ifndef RUNNING_FRC_TESTS
//int main() { return frc::StartRobot<Robot>(); }
//#endif
