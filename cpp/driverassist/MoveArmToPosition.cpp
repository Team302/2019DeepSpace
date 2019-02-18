#include "driverassist/MoveArmToPosition.h"
#include "subsys/MechanismFactory.h"
#include "frc/SmartDashboard/SmartDashboard.h"

MoveArmToPosition::MoveArmToPosition()  :
m_arm( dynamic_cast<Arm*>(MechanismFactory::GetMechanismFactory()->GetIMechanism(IMechanism::MECHANISM_TYPE::ARM)) ),
m_wrist( dynamic_cast<Wrist*>(MechanismFactory::GetMechanismFactory()->GetIMechanism(IMechanism::MECHANISM_TYPE::WRIST)) )
{
    m_currentState = MOVE_STATE::DONE;
}

void MoveArmToPosition::SetTargetPosition(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo, bool flip)
{
    m_currentState = MOVE_STATE::PULL_IN;
    m_targetPos = height;
    m_cargo = cargo;
    m_flip = flip;
}

void MoveArmToPosition::Update()
{
    switch(m_currentState)
    {
        case MOVE_STATE::PULL_IN:
            m_arm->MoveExtensionInches(0);
            frc::SmartDashboard::PutBoolean("Arm at target (sequence)", false);
            frc::SmartDashboard::PutBoolean("Wrist at target (sequence)", false);
            frc::SmartDashboard::PutBoolean("Extend at target (sequence)", false);
            if(m_arm->GetExtenderRealInches() < SAFE_INCHES)
                m_currentState = MOVE_STATE::MOVE_WIRST_ARM_TO_POS;
            break;

        case MOVE_STATE::MOVE_WIRST_ARM_TO_POS:
            m_arm->MoveArmPreset(m_targetPos, m_cargo, m_flip);
            m_wrist->MoveWristPresets(m_targetPos, m_cargo, m_flip);
            if( std::abs(m_arm->GetArmRealAngle() - m_arm->GetArmTargetAngle()) < ARM_THRESH)
                m_currentState = MOVE_STATE::PUSH_OUT;
            break;

        case MOVE_STATE::PUSH_OUT:
        {
            m_arm->MoveExtentionPreset(m_targetPos, m_cargo);
            bool armDone = (std::abs(m_arm->GetArmRealAngle() - m_arm->GetArmTargetAngle()) < DONE_ARM_THRESH);
            bool wristDone = (std::abs(m_wrist->GetWristRealAngle() - m_wrist->GetWristTargetAngle()) < DONE_WRIST_THRESH);
            bool extendDone = std::abs(m_arm->GetExtenderRealInches() - m_arm->GetExtenderTargetInches()) < DONE_EXTEND_THRESH;
            frc::SmartDashboard::PutBoolean("Arm at target (sequence)", armDone);
            frc::SmartDashboard::PutBoolean("Wrist at target (sequence)", wristDone);
            frc::SmartDashboard::PutBoolean("Extend at target (sequence)", extendDone);
            if (armDone && wristDone && extendDone)
                m_currentState = MOVE_STATE::DONE;
        }
            break;

        case MOVE_STATE::DONE:
            break;

        default:
            break;
    }
}

void MoveArmToPosition::Cancel()
{
    m_currentState = MOVE_STATE::DONE;
}

bool MoveArmToPosition::IsDone()
{
    return (m_currentState == MOVE_STATE::DONE);
}