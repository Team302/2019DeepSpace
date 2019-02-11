#include "Test/WristTest.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

#include "subsys/Wrist.h"


WristTest::WristTest ()
{
    m_wrist = new Wrist ();
    m_prevhgt = Wrist::PLACEMENT_HEIGHT::MAX_PLACEMENT_HEIGHTS;
}


void WristTest::Run(Wrist::PLACEMENT_HEIGHT hgt) 
{
    if (hgt != m_prevhgt)
    {
        m_wrist -> Set(hgt);
        m_counts = 0;
        m_isDone = false;
    }
    else
    {
        m_counts++;
    }

    if (m_counts > 9)
    {
        double angle = m_wrist -> Get();
        m_isDone = true;
        printf ("Target %d Angle %g \n", hgt, angle);
    }
    m_prevhgt = hgt;
    
}

bool WristTest::IsDone() 
{
    if (m_isDone = true)
    {
    printf ("Automated Systems Test Completed \n");
    }
}

//#ifndef RUNNING_FRC_TESTS
//int main() { return frc::StartRobot<Robot>(); }
//#endif
