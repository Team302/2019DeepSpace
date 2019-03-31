#include "driverassist/DeployGamePiece.h"

DeployGamePiece::DeployGamePiece() :
    m_arm(MechanismFactory::GetMechanismFactory()->GetArm()),
    m_wrist(MechanismFactory::GetMechanismFactory()->GetWrist()),
    m_intake(MechanismFactory::GetMechanismFactory()->GetIntake()),
    m_hatchMech(MechanismFactory::GetMechanismFactory()->GetHatchMech()),
    m_elapsedTime(0.0),
    m_wristInitialAngle(0.0),
    m_angleOffset(0.0),
    m_state(DeployState::DONE)
{
}

void DeployGamePiece::Update()
{
    switch (m_state)
    {
        case SECOND_MECH_DEPLOY:
            m_hatchMech->SetState(false);
            m_elapsedTime += 0.02;
            if (m_elapsedTime > SECOND_MECH_DEPLOY_TIME)
                m_state = DONE;
        break;
        case MOVING_WRIST:
        {
            m_wrist->MoveWristMotionMagic(m_wristInitialAngle + m_angleOffset);
            m_intake->EnableBrakeMode(false);
            m_intake->IntakeManual(0);
            if (std::abs(m_wrist->GetWristRealAngle() - m_wrist->GetWristTargetAngle()) < OUTTAKE_ANGLE_THRESHOLD)
                m_state = MOVING_WRIST_AND_INTAKE;
        }
            break;

        case MOVING_WRIST_AND_INTAKE:
            m_intake->EnableBrakeMode(false);
            m_intake->IntakeManual(HATCH_OUTTAKE_SPEED);
            if (std::abs(m_wrist->GetWristRealAngle() - m_wrist->GetWristTargetAngle()) < DONE_WRIST_THRESH)
                m_state = DONE;
            break;

        case DONE:
            m_elapsedTime = 0;
            m_intake->EnableBrakeMode(true);
            break;

        case SHOOTING_CARGO:
            m_elapsedTime += 0.02;
            m_intake->IntakeManual(CARGO_SHOOT_SPEED);
            if (m_elapsedTime > CARGO_SHOOT_TIME)
                m_state = DONE;
            break;

        default:
            break;
    }
}

bool DeployGamePiece::IsDone()
{
    return m_state == DONE;
}

void DeployGamePiece::Deploy(bool cargo, bool flip, bool hatchPointingUp, bool secondMech)
{
    if (secondMech)
    {
        m_state = SECOND_MECH_DEPLOY;
    }
    else
    {
        m_state = cargo ? SHOOTING_CARGO : MOVING_WRIST;
        m_wristInitialAngle = m_wrist->GetWristTargetAngle();
        m_angleOffset = (flip != hatchPointingUp) ? WRIST_ANGLE_DELTA : -WRIST_ANGLE_DELTA;
    }
}

void DeployGamePiece::Cancel()
{
    if (m_state == MOVING_WRIST || m_state == MOVING_WRIST_AND_INTAKE)
    {
        m_wrist->MoveWristManualAngle(m_wrist->GetWristRealAngle());
        m_intake->IntakeManual(0);
    }
    m_state = DONE;
    m_elapsedTime = 0;
}