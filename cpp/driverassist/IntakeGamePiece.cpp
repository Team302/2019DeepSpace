/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "driverassist/IntakeGamePiece.h"
#include "subsys/Arm.h"
#include "subsys/Wrist.h"
#include "subsys/Intake.h"
#include "subsys/IMechanism.h"
#include "subsys/MechanismFactory.h"


IntakeGamePiece::IntakeGamePiece() : m_arm(MechanismFactory::GetMechanismFactory()->GetArm()),
                                     m_wrist(MechanismFactory::GetMechanismFactory()->GetWrist()),
                                     m_intake(MechanismFactory::GetMechanismFactory()->GetIntake()),
                                     m_elapsedTime(0.0),
                                     m_armInitialAngle(0.0),
                                     m_armAngleOffset(0.0),
                                     m_state(INTAKE_STATE::DONE) 
{
}

void IntakeGamePiece::Update()
{
    switch (m_state)
    {
        case MOVING_ARM_AND_INTAKE_CARGO:
            m_arm->MoveArmMotionMagic(m_armInitialAngle + m_armAngleOffset);
            if (std::abs(m_arm->GetArmRealAngle() - m_arm->GetArmTargetAngle()) < ARM_INTAKE_THRESH)
            {
                m_state = INTAKE_CARGO;
            }
            break;
            
        case INTAKE_CARGO:
            m_elapsedTime += 0.02;
            m_intake->IntakeManual(CARGO_INTAKE_SPEED);
            if (m_elapsedTime > CARGO_INTAKE_TIME)
                m_state = DONE;
            break;

        case MOVING_ARM_AND_INTAKE_HATCH:
            m_arm->MoveArmMotionMagic(m_armInitialAngle + m_armAngleOffset);
            if (std::abs(m_arm->GetArmRealAngle() - m_arm->GetArmTargetAngle()) < ARM_INTAKE_THRESH)
            {
                m_state = INTAKE_CARGO;
            }
            break;

        case INTAKE_HATCH:
            m_elapsedTime += 0.02;
            m_intake->IntakeManual(HATCH_INTAKE_SPEED);
            if (m_elapsedTime > HATCH_INTAKE_TIME)
                m_state = DONE;
            break;

        case DONE:
            m_elapsedTime = 0;
            break;  

        default:
            break;
    }
}

bool IntakeGamePiece::IsDone()
{
    return m_state == DONE;
}

void IntakeGamePiece::IntakeGameObject(bool cargo, bool flip)
{
    m_state = cargo ? MOVING_ARM_AND_INTAKE_CARGO : MOVING_ARM_AND_INTAKE_HATCH;
    m_armAngleOffset = cargo ? ARM_ANGLE_CARGO_DELTA : ARM_ANGLE_HATCH_DELTA;
    m_armAngleOffset = flip ? -m_armAngleOffset : m_armAngleOffset;
}

void IntakeGamePiece::Cancel()
{
    m_state = DONE;
    m_elapsedTime = 0;
}