#pragma once

#include "subsys/vision/DragonLimelight.h"
#include "subsys/chassis/DragonChassis.h"
#include "subsys/Arm.h"
#include "subsys/MechanismFactory.h"
#include "hw/LED.h"
#include "driverassist/HoldDrivePosition.h"

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
        COARSE_ADJUSTMENT_INIT,
        COARSE_ADJUSTMENT, 
        DONE
    };

    double RadToHeading(double rad);

    DragonLimelight* m_limelight;
    DragonChassis* m_chassis;
    HoldDrivePosition* m_hold;
    Arm* m_arm;
    STATE m_state;
    bool m_flip;
    double m_pHeadingCorrection;
    int m_coarseAdjustInitLoops;

    LED* m_frontLed;
    LED* m_backLed;
    LED* m_topLed;
    
    const double ROBOT_YAW_MULT = 0.02;
    const double ROCKET_YAW_MULT = 0.0; //don't use if not using 3d solve
    const double DRIVE_SPEED = 0.0;
    const double ROT_OVER_HEADING = 0.3844003452;
    const double EARLY_STOP_DISTANCE = 0.5;
    const double COARSE_DONE_DISTANCE_THRESHOLD = 1.0;

};