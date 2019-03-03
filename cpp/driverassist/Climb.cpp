#include "driverassist/Climb.h"
#include "subsys/MechanismFactory.h"
#include <frc/smartdashboard/SmartDashboard.h>

Climb::Climb() :
m_state(DONE),
m_arm(MechanismFactory::GetMechanismFactory()->GetArm()),
m_wrist(MechanismFactory::GetMechanismFactory()->GetWrist()),
m_climber(MechanismFactory::GetMechanismFactory()->GetClimber()),
m_pigeon(DragonPigeon::GetPigeon()),
m_speed(0)
{
}

void Climb::Update()
{
    frc::SmartDashboard::PutNumber("Pigeon Roll", m_pigeon->GetRoll());
    frc::SmartDashboard::PutNumber("Pigeon Pitch", m_pigeon->GetPitch());
    frc::SmartDashboard::PutNumber("Pigeon Yaw", m_pigeon->GetYaw());

    //if pitch is positive, move arm down
    //if pitch is negative, more elevator down

    double angle = m_pigeon->GetPitch() + 1.5; // pitch offset
    switch (m_state)
    {
        case CLIMBING:
            // move extender out slowly
            m_arm->MoveExtensionSpeed(0.2);
            
            //negative on climber motor is down is down
            //right side of controller make it climb 
            if (std::abs(angle) < 1)
            {
                m_arm->MoveArmAngle(m_arm->GetArmTargetAngle() - (m_speed * 12 * 0.02));
                m_climber->MoveClimbElevator(-m_speed);
            }
            else if (m_speed > 0) //climbing up
            {
                if (angle > 0) 
                {
                    // arm down
                    m_arm->MoveArmAngle(m_arm->GetArmTargetAngle() - (m_speed * 12 * 0.02));
                    m_climber->MoveClimbElevator(0);
                }
                else
                {
                    //elevator down
                    m_climber->MoveClimbElevator(-m_speed);
                }
            }
            else //climbing down
            {
                if (angle > 0)
                {
                    //elevator up
                    m_climber->MoveClimbElevator(-m_speed);
                }
                else
                {
                    m_arm->MoveArmAngle(m_arm->GetArmTargetAngle() - (m_speed * 12 * 0.02));
                    m_climber->MoveClimbElevator(0);
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