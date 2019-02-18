#pragma once

// Includes
#include "subsys/MechanismFactory.h"

// Mechanisms
#include "subsys/Arm.h"
#include "subsys/Wrist.h"
#include "subsys/Intake.h"

class DeployGamePiece
{
public:
    enum DeployState
    {
        SHOOTING_CARGO,
        MOVING_WRIST,
        MOVING_WRIST_AND_INTAKE,
        DONE
    };

    DeployGamePiece();
    ~DeployGamePiece() {};

    void Update();
    bool IsDone();
    void Cancel();
    void Deploy(bool cargo, bool flip, bool hatchPointingUp);

private:
    Arm* m_arm;
    Wrist* m_wrist;
    Intake* m_intake;

    double m_elapsedTime;
    double m_wristInitialAngle;
    double m_angleOffset;
    DeployState m_state;

    const double CARGO_SHOOT_TIME = 0.75;
    const double WRIST_ANGLE_DELTA = -45;
    const double OUTTAKE_ANGLE_THRESHOLD = 37;
    const double DONE_WRIST_THRESH = 8;

    const double CARGO_SHOOT_SPEED = 0.25;
    const double HATCH_OUTTAKE_SPEED = -1;
    
};