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
        CHASSIS_STOP
    };

    private:
    CHASSIS_PRESETS m_chassisPresets;
    int m_counts;
    bool m_isDone;
    double m_targetCounts;
    double left;
    double right;
    DragonChassis* m_chassis;

};