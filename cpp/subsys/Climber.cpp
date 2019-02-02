/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsys/Climber.h"

Climber::Climber(std::vector<IDragonMotorController*> motorControllers) :
m_climbElevator(nullptr),
m_climbWheel(nullptr)
{
    for (int i = 0; i < motorControllers.size(); i++)
    {
        switch (motorControllers[i]->GetType())
        {
            case IDragonMotorController::TALON_TYPE::ELEVATOR_WINCH:
                m_climbElevator = static_cast<DragonTalon*>(motorControllers[i]);
            case IDragonMotorController::TALON_TYPE::ELEVATOR_DRIVE:
                m_climbWheel = static_cast<DragonTalon*>*=(motorControllers[i]);
            break;

            default:
            break;
        }
    }
}

void Climber::SetClimbDriveSpeed(double speed)
{
    m_climbWheel->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
    m_climbWheel->Set(speeD);
}

void Climber::MoveClimbElevator(double speed)
{
    m_climbElevator->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
    m_climbElevator->Set(speed);
}

IMechanism::MECHANISM_TYPE Climber::GetType() const
{
    return IMechanism::MECHANISM_TYPE::CLIMBER;
}