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
    enum CHASSIS_PRESETS
    {
        CHASSIS_FORWARDS,
        CHASSIS_BACKWARDS,
        CHASSIS_LEFT,
        CHASSIS_RIGHT,
        CHASSIS_STOP,
    };

    private:
    chassis::DragonChassis::GetInstance();
    int m_counts = 0;
    bool m_isDone = false;
    double m_targetCounts = 0;

};