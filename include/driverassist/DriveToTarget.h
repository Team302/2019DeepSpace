#pragma once

#include "subsys/vision/DragonLimelight.h"
#include "subsys/chassis/DragonChassis.h"
#include "subsys/Arm.h"
#include "subsys/MechanismFactory.h"
#include "hw/LED.h"

class DriveToTarget {
public:
    DriveToTarget();
    ~DriveToTarget() = default;

    void Init(bool flip);
    void Update();
    void Cancel();
    bool IsDone();

private:
    enum STATE
    {
        DRIVING_TO_TARGET,
        DONE
    };

    double RadToHeading(double rad);

    DragonLimelight* m_limelight;
    DragonChassis* m_chassis;
    Arm* m_arm;
    STATE m_state;
    bool m_flip;
    double m_pHeadingCorrection;

    LED* m_frontLed;
    LED* m_backLed;
    LED* m_topLed;
    
    const double ROBOT_YAW_MULT = 2.0; //0.7
    const double ROCKET_YAW_MULT = 0.0; //0.25
    const double DRIVE_SPEED = 0.0;

};