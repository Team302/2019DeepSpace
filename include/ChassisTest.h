#pragma once

#include <string>

#include <frc/timedrobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "subsys/chassis/DragonChassis.h"

class ChassisTest {
    public:
    ChassisTest();
    void Init();
    void Execute();
    bool IsDone();

    private:
    DragonChassis* m_chassis;
}