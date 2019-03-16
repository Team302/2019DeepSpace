#pragma once

// Includes
#include "subsys/MechanismFactory.h"

// Mechanisms
#include "subsys/Arm.h"
#include "subsys/Wrist.h"
#include "subsys/Intake.h"
#include "subsys/HatchMechanism.h"

class DeployGamePiece
{
public:
    enum DeployState
    {
        SECOND_MECH_DEPLOY,
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
    void Deploy(bool cargo, bool flip, bool hatchPointingUp, bool secondMech);

private:
    Arm* m_arm;
    Wrist* m_wrist;
    Intake* m_intake;
    HatchMechanism* m_hatchMech;

    double m_elapsedTime;
    double m_wristInitialAngle;
    double m_angleOffset;
    DeployState m_state;

    const double CARGO_SHOOT_TIME = 0.75;
    const double SECOND_MECH_DEPLOY_TIME = 0.1;
    const double WRIST_ANGLE_DELTA = -80;
    const double OUTTAKE_ANGLE_THRESHOLD = 60;
    const double DONE_WRIST_THRESH = 8;

    const double CARGO_SHOOT_SPEED = -1.0;
    const double HATCH_OUTTAKE_SPEED = 0.50;
    
};