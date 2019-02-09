/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsys/Arm.h"
#include "hw/DragonTalon.h"
#include <hw/IDragonMotorController.h>

Arm::Arm(IDragonMotorControllerVector motorControllers) :
m_armTargetAngle(0.0),
m_extenderTargetRotations(0.0),
m_armMaster(nullptr),
m_extender(nullptr)
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
    // m_armMaster->ConfigMotionAcceleration(0.1);
    // m_armMaster->ConfigMotionCruiseVelocity(0.5);
    // m_armMaster->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
    // m_armMaster->Set(0);
}

void Arm::MoveArmPreset(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo, bool flip)
{
    if(cargo)
    {
        switch(height)
        {
            case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
                m_armTargetAngle = cargoAngle[Arm::CARGO_WRIST_PRESETS::CARGO_FLOOR];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
                m_armTargetAngle = cargoAngle[Arm::CARGO_WRIST_PRESETS::CARGO_SHIP];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
                m_armTargetAngle = cargoAngle[Arm::CARGO_WRIST_PRESETS::CARGO_HP];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
                m_armTargetAngle = cargoAngle[Arm::CARGO_WRIST_PRESETS::CARGO_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
                m_armTargetAngle = cargoAngle[Arm::CARGO_WRIST_PRESETS::CARGO_MID];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
                m_armTargetAngle = cargoAngle[Arm::CARGO_WRIST_PRESETS::CARGO_HIGH];
                break;
            default:
                // bad
                printf("Arm.cpp MoveArmPresets cargo switch default");
                break;
        }
    }
    else
    {
        switch(height)
        {
            case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
                m_armTargetAngle = hatchAngle[Arm::HATCH_WRIST_PRESETS::HATCH_FLOOR];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
                m_armTargetAngle = hatchAngle[Arm::HATCH_WRIST_PRESETS::HATCH_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
                m_armTargetAngle = hatchAngle[Arm::HATCH_WRIST_PRESETS::HATCH_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
                m_armTargetAngle = hatchAngle[Arm::HATCH_WRIST_PRESETS::HATCH_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
                m_armTargetAngle = hatchAngle[Arm::HATCH_WRIST_PRESETS::HATCH_MID];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
                m_armTargetAngle = hatchAngle[Arm::HATCH_WRIST_PRESETS::HATCH_HIGH];
                break;
            default:
                // bad
                printf("Arm.cpp MoveArmPresets hatch switch default");
                break;
        }
    }

    if(flip)
        m_armTargetAngle = -m_armTargetAngle;

    m_armMaster->SetControlMode(DragonTalon::TALON_CONTROL_MODE::MOTION_MAGIC);
    m_armMaster->Set(m_armTargetAngle / 360.0); // Sets in rotations from degrees
}

void Arm::MoveArmSpeed(double speed)
{
    m_armMaster->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
    m_armMaster->Set(speed);
}

void Arm::MoveArmAngle(double angle)
{
    m_armMaster->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::ROTATIONS);
    m_armMaster->Set(angle / 360.0);
}

void Arm::MoveExtentionPreset(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo)
{
    if(cargo)
    {
        switch(height)
        {
            case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
                m_extenderTargetRotations = extenderCargoRots[Arm::CARGO_WRIST_PRESETS::CARGO_FLOOR];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
                m_extenderTargetRotations = extenderCargoRots[Arm::CARGO_WRIST_PRESETS::CARGO_SHIP];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
                m_extenderTargetRotations = extenderCargoRots[Arm::CARGO_WRIST_PRESETS::CARGO_HP];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
                m_extenderTargetRotations = extenderCargoRots[Arm::CARGO_WRIST_PRESETS::CARGO_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
                m_extenderTargetRotations = extenderCargoRots[Arm::CARGO_WRIST_PRESETS::CARGO_MID];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
                m_extenderTargetRotations = extenderCargoRots[Arm::CARGO_WRIST_PRESETS::CARGO_HIGH];
                break;
            default:
                // bad
                printf("Arm.cpp MoveExtentionPresets cargo switch default");
                break;
        }
    }
    else
    {
        switch(height)
        {
            case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
                m_extenderTargetRotations = extenderHatchRots[Arm::HATCH_WRIST_PRESETS::HATCH_FLOOR];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
                m_extenderTargetRotations = extenderHatchRots[Arm::HATCH_WRIST_PRESETS::HATCH_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
                m_extenderTargetRotations = extenderHatchRots[Arm::HATCH_WRIST_PRESETS::HATCH_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
                m_extenderTargetRotations = extenderHatchRots[Arm::HATCH_WRIST_PRESETS::HATCH_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
                m_extenderTargetRotations = extenderHatchRots[Arm::HATCH_WRIST_PRESETS::HATCH_MID];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
                m_extenderTargetRotations = extenderHatchRots[Arm::HATCH_WRIST_PRESETS::HATCH_HIGH];
                break;
            default:
                // bad
                printf("Arm.cpp MoveExtentionPresets hatch switch default");
                break;
        }
    }

    m_extender->SetControlMode(DragonTalon::TALON_CONTROL_MODE::MOTION_MAGIC);
    m_extender->Set(m_extenderTargetRotations);
}

void Arm::MoveExtensionSpeed(double speed)
{
    m_extender->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
    m_extender->Set(speed);
}

void Arm::MoveExtensionInches(double inches)
{
    m_extender->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::ROTATIONS);
    m_extender->Set(inches); //TODO: multiply by a constant to convert inches to rotations
}

double Arm::GetArmRealAngle()
{
    return m_armMaster->GetRotations() * 360.0;
}

double Arm::GetArmTargetAngle()
{
    return m_armTargetAngle;
}

double Arm::GetExtenderRealRotations()
{
    return m_extender->GetRotations();
}

double Arm::GetExtenderTargetRotations()
{
    return m_extenderTargetRotations;
}

IMechanism::MECHANISM_TYPE Arm::GetType() const
{
    return IMechanism::MECHANISM_TYPE::ARM;
}