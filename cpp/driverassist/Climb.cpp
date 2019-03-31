#include "driverassist/Climb.h"
#include "subsys/MechanismFactory.h"
#include <frc/smartdashboard/SmartDashboard.h>

Climb::Climb() :
m_state(DONE),
m_arm(MechanismFactory::GetMechanismFactory()->GetArm()),
m_wrist(MechanismFactory::GetMechanismFactory()->GetWrist()),
m_climber(MechanismFactory::GetMechanismFactory()->GetClimber()),
m_pigeon(DragonPigeon::GetPigeon()),
m_holdClimber(false),
m_speed(0)
{
}

void Climb::Update()
{
    // frc::SmartDashboard::PutNumber("Pigeon Roll", m_pigeon->GetRoll());
    frc::SmartDashboard::PutNumber("Pigeon Pitch", m_pigeon->GetPitch());
    // frc::SmartDashboard::PutNumber("Pigeon Yaw", m_pigeon->GetYaw());

    //if pitch is positive, move arm down
    //if pitch is negative, more elevator down

    double angle = m_pigeon->GetPitch() + ANGLE_OFFSET; // pitch offset
    switch (m_state)
    {
        case CLIMBING:
            // move extender out slowly
            m_arm->MoveExtensionSpeed(0.5, true);
            //negative on climber motor is down is down
            //right side of controller make it climb 
            if (std::abs(angle) < 1)
            {
                m_arm->MoveArmAngle(m_arm->GetArmTargetAngle() - (m_speed * ARM_SPEED_MULTIPLIER * 0.02));
                m_climber->MoveClimbElevator(-m_speed);
                frc::SmartDashboard::PutNumber("automated climb stat", 0);
            }
            else if (m_speed > 0) //climbing up
            {
                if (angle > 0) 
                {
                    // arm down
                    m_arm->MoveArmAngle(m_arm->GetArmTargetAngle() - (m_speed * ARM_SPEED_MULTIPLIER * 0.02));
                    m_climber->MoveClimbElevator(-CLIMBER_HOLD_POWER);
                    frc::SmartDashboard::PutNumber("automated climb stat (1 is arm catching up)", 1);
                    m_holdClimber = true;
                }
                else
                {
                    //elevator down
                    m_climber->MoveClimbElevator(-m_speed);
                    frc::SmartDashboard::PutNumber("automated climb stat (1 is arm catching up)", -1);
                    m_holdClimber = true;
                }
                
            }
            else //climbing down
            {
                if (angle > 0)
                {
                    //elevator up
                    m_climber->MoveClimbElevator(-m_speed);
                    m_holdClimber = true;
                }
                else
                {
                    m_arm->MoveArmAngle(m_arm->GetArmTargetAngle() - (m_speed * ARM_SPEED_MULTIPLIER * 0.02));
                    m_climber->MoveClimbElevator(0);
                    m_holdClimber = true;
                }
            }
            
            break;

        case DONE:

            break;
        default:
            break;
    }
}

void Climb::Cancel()
{
    m_state = DONE;
}

void Climb::SetClimb(double speed)
{
    m_speed = speed;

    // if arm is not all the way down, set state to CLIMBING
    m_state = CLIMBING;

}

bool Climb::IsDone()
{
    return m_state == DONE;
}

double Climb::GetHoldPower()
{
    if (m_holdClimber)
    {
        return -CLIMBER_HOLD_POWER;
    }
    else
    {
        return CLIMBER_HOLD_UP_POWER;
    }
}

void Climb::CancelHold()
{
    m_holdClimber = false;
}

void Climb::HoldUp()
{
    m_climber->MoveClimbElevator(CLIMBER_HOLD_UP_POWER);
}