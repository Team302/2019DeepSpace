/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsys/Arm.h"
#include <subsys/IMechanism.h>
#include <xmlhw/PIDData.h>
#include "hw/DragonTalon.h"
#include <hw/IDragonMotorController.h>
#include <cmath>
#include "frc/smartdashboard/SmartDashboard.h"

Arm::Arm(IDragonMotorControllerVector motorControllers) :
m_armTargetAngle(0.0),
m_previousArmRealAngle(0.0),
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
    m_armTargetAngle = m_armMaster->GetRotations() * 360.0;
    m_extenderTargetRotations = m_extender->GetRotations();
}

void Arm::MoveArmPreset(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo, bool flip)
{
    if(cargo)
    {
        switch(height)
        {
            case PlacementHeights::PLACEMENT_HEIGHT::START_POSITION:
                m_armTargetAngle = cargoAngle[Arm::CARGO_WRIST_PRESETS::CARGO_START_POSITION];
                break;
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
            case PlacementHeights::PLACEMENT_HEIGHT::START_POSITION:
                m_armTargetAngle = hatchAngle[Arm::HATCH_WRIST_PRESETS::HATCH_START_POSITION];
                break;            
            case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
                m_armTargetAngle = hatchAngle[Arm::HATCH_WRIST_PRESETS::HATCH_FLOOR];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
                m_armTargetAngle = hatchAngle[Arm::HATCH_WRIST_PRESETS::HATCH_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
                m_armTargetAngle = hatchAngle[Arm::HATCH_WRIST_PRESETS::HATCH_HP];
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
    m_previousArmRealAngle = GetArmRealAngle();
}

void Arm::MoveArmMotionMagic(double angle)
{
    m_armMaster->Set(DragonTalon::TALON_CONTROL_MODE::MOTION_MAGIC);
    m_armMaster->Set(angle / 360); // Sets in rotations from degrees
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
    m_armTargetAngle = angle; // update target angle
}

void Arm::ResetTarget()
{
    m_armTargetAngle = GetArmRealAngle();
}

void Arm::MoveExtentionPreset(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo)
{
    if(cargo)
    {
        switch(height)
        {
            case PlacementHeights::PLACEMENT_HEIGHT::START_POSITION:
                m_extenderTargetRotations = extenderCargoInches[Arm::CARGO_WRIST_PRESETS::CARGO_START_POSITION] / INCHES_PER_REVOLUTION;
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
                m_extenderTargetRotations = extenderCargoInches[Arm::CARGO_WRIST_PRESETS::CARGO_FLOOR] / INCHES_PER_REVOLUTION;
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
                m_extenderTargetRotations = extenderCargoInches[Arm::CARGO_WRIST_PRESETS::CARGO_SHIP] / INCHES_PER_REVOLUTION;
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
                m_extenderTargetRotations = extenderCargoInches[Arm::CARGO_WRIST_PRESETS::CARGO_HP] / INCHES_PER_REVOLUTION;
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
                m_extenderTargetRotations = extenderCargoInches[Arm::CARGO_WRIST_PRESETS::CARGO_LOW] / INCHES_PER_REVOLUTION;
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
                m_extenderTargetRotations = extenderCargoInches[Arm::CARGO_WRIST_PRESETS::CARGO_MID] / INCHES_PER_REVOLUTION;
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
                m_extenderTargetRotations = extenderCargoInches[Arm::CARGO_WRIST_PRESETS::CARGO_HIGH];
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
            case PlacementHeights::PLACEMENT_HEIGHT::START_POSITION:
                m_extenderTargetRotations = extenderHatchInches[Arm::HATCH_WRIST_PRESETS::HATCH_START_POSITION] / INCHES_PER_REVOLUTION;
            case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
                m_extenderTargetRotations = extenderHatchInches[Arm::HATCH_WRIST_PRESETS::HATCH_FLOOR] / INCHES_PER_REVOLUTION;
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
                m_extenderTargetRotations = extenderHatchInches[Arm::HATCH_WRIST_PRESETS::HATCH_LOW] / INCHES_PER_REVOLUTION;
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
                m_extenderTargetRotations = extenderHatchInches[Arm::HATCH_WRIST_PRESETS::HATCH_HP] / INCHES_PER_REVOLUTION;
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
                m_extenderTargetRotations = extenderHatchInches[Arm::HATCH_WRIST_PRESETS::HATCH_LOW] / INCHES_PER_REVOLUTION;
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
                m_extenderTargetRotations = extenderHatchInches[Arm::HATCH_WRIST_PRESETS::HATCH_MID] / INCHES_PER_REVOLUTION;
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
                m_extenderTargetRotations = extenderHatchInches[Arm::HATCH_WRIST_PRESETS::HATCH_HIGH] / INCHES_PER_REVOLUTION;
                break;
            default:
                // bad
                printf("Arm.cpp MoveExtentionPresets hatch switch default \n");
                break;
        }
    }

    m_extender->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::ROTATIONS);
    m_extender->Set(m_extenderTargetRotations);
}

void Arm::MoveExtensionSpeed(double speed)
{
    speed += EXTENDER_HOLD_POWER;
    m_extender->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
    CorrectExtenderPower(speed); //if we are gonna be out of bounds, pull in
    m_extender->Set(speed);
}

void Arm::MoveExtensionInches(double inches)
{
    m_extender->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::ROTATIONS);
    m_extender->Set(inches / INCHES_PER_REVOLUTION); //TODO: multiply by a constant to convert inches to rotations
    m_extenderTargetRotations = inches / INCHES_PER_REVOLUTION;
}

double Arm::GetArmRealAngle()
{
    return m_armMaster->GetRotations() * 360.0;
}

double Arm::GetArmTargetAngle()
{
    return m_armTargetAngle;
}

double Arm::GetExtenderRealInches()
{
    return m_extender->GetRotations() * INCHES_PER_REVOLUTION;
}

double Arm::GetExtenderTargetInches()
{
    return m_extenderTargetRotations * INCHES_PER_REVOLUTION;
}

IMechanism::MECHANISM_TYPE Arm::GetType() const
{
    return IMechanism::MECHANISM_TYPE::ARM;
}

double Arm::OurDegreesToRads(double ourDegrees)
{
    return - ((ourDegrees / 360.0) - (1/4.0)) * 2 * M_PI;
}

void Arm::CorrectExtenderPower(double &power)
{
    double degreesPerSecond = GetArmRealAngle() - m_previousArmRealAngle;
    degreesPerSecond / 0.02;

    double correctedAngle = GetArmRealAngle() + degreesPerSecond * 0.5;
    // double maxLegalExtender = (1-std::abs(cos(OurDegreesToRads(m_armTargetAngle)))) * 7.625;
    double realRads = OurDegreesToRads(GetArmRealAngle());
    double predictedRads = OurDegreesToRads(correctedAngle);

    //practice bot
    // double realMaxLegalExtender = Map(std::abs(cos(realRads)), 1, 0.76, 1.175, 6.8); //BIG TODO: make MAX_EXTENDER_DISTANCE constant
    // double predictedMaxLegalExtender = Map(std::abs(cos(predictedRads)), 1, 0.76, 1.175, 6.8);

    // comp bot
    double realMaxLegalExtender = Map(std::abs(cos(realRads)), 1, 0.76, 2.0, 7.625); //BIG TODO: make MAX_EXTENDER_DISTANCE constant
    double predictedMaxLegalExtender = Map(std::abs(cos(predictedRads)), 1, 0.76, 2.0, 7.625);

    // frc::SmartDashboard::PutNumber("Max Legal Inches", maxLegalExtender);

    // frc::SmartDashboard::PutNumber("")
    if (GetExtenderRealInches() > realMaxLegalExtender || GetExtenderRealInches() > predictedMaxLegalExtender)
    {
        power = -1;
    }
    else if (GetExtenderRealInches() < 0.0)
        power = EXTENDER_HOLD_POWER;

    m_previousArmRealAngle = GetArmRealAngle();
}

double Arm::Map(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Arm::SetParam
(
    IMechanism::MECHANISM_PARAM_TYPE    param,          // <I> - parameter to set
    double                              value           // <I> - parameter value
) 
{
    // TODO:  Override values
}
void Arm::SetPID
(
    PIDData*        pid                 // <I> - PID control information
) 
{
    // TODO:  Override values
}




