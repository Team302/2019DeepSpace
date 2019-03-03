#pragma once

#include "subsys/Arm.h"
#include "subsys/Wrist.h"
#include "subsys/Climber.h"
#include "hw/DragonPigeon.h"


class Climb
{
public:
    Climb();
    ~Climb() = default;

    enum CLIMB_STATE
    {
        CLIMBING,
        DONE
    };

    void Update();
    void Cancel();
    void SetClimb(double speed); //positive is climb, negative is unclimb
    bool IsDone();

private:
    CLIMB_STATE m_state;

    Arm* m_arm;
    Wrist* m_wrist;
    Climber* m_climber;
    DragonPigeon* m_pigeon;

    double m_speed;

    const double ARM_SPEED_MULTIPLIER = 15;
    const double BOTH_UP_THRESHOLD = 1.5;
    const double ANGLE_OFFSET = 1.5;

};