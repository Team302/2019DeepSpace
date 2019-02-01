/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsys/Arm.h"
#include "hw/DragonTalon.h"

Arm::Arm(std::vector<IDragonMotorController*> motorControllers)
{
    for (int i = 0; i < motorControllers.size(); i++)
    {
        switch (motorControllers[i]->GetType())
        {
            case IDragonMotorController::TALON_TYPE::ARM_MASTER:
                m_armMaster = static_cast<DragonTalon*>(motorControllers[i]);
            break;

            case IDragonMotorController::TALON_TYPE::ARM_EXTENSION:
                m_extender = static_cast<DragonTalon*>(motorControllers[i]);
            break;

            default:
            break;
        }
    }
}

void Arm::MoveArmPresets(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo, bool flip)
{
    //TODO:
}

void Arm::MoveArmManualSpeed(double speed)
{
    m_armMaster->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
    m_armMaster->Set(speed);
}

void Arm::MoveArmManualAngle(double angle)
{
    m_armMaster->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::ROTATIONS);
    m_armMaster->Set(angle);
}

void Arm::MoveArmExtensionSpeed(double speed)
{
    m_extender->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
    m_extender->Set(speed);
}

void Arm::MoveArmExtensionInches(double inches)
{
    m_extender->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::ROTATIONS);
    m_extender->Set(inches); //TODO: multiply by a constant to convert inches to rotations
}

double Arm::GetArmCurrentRealAngle()
{
    return m_armMaster->GetRotations() * 360.0;
}

double Arm::GetArmCurrentTargetAngle()
{
    //TODO: this
    return 0.0;
}

IMechanism::MECHANISM_TYPE Arm::GetType() const
{
    return IMechanism::MECHANISM_TYPE::ARM;
}