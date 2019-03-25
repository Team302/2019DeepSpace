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
#include "DefnRobot.h"

Arm::Arm(IDragonMotorControllerVector motorControllers) : m_armTargetAngle(0.0),
                                                          m_previousArmRealAngle(0.0),
                                                          m_extenderTargetRotations(0.0),
                                                          m_armLegalStartingAngle(-167.00),
                                                          m_extenderLegalStartingInches(0),
                                                          m_armTestStartingAngle(-138.00),
                                                          m_extenderTestStartingInches(7.625),
                                                          m_extenderMinDistance(0.0),   // default value
                                                          m_extenderMaxDistance(7.625), // default value
                                                          m_armMaster(nullptr),
                                                          m_extender(nullptr)
{
    for (int i = 0; i < motorControllers.size(); i++)
    {
        switch (motorControllers[i]->GetType())
        {
        case IDragonMotorController::TALON_TYPE::ARM_MASTER:
            m_armMaster = dynamic_cast<DragonTalon *>(motorControllers[i]);
            break;

        case IDragonMotorController::TALON_TYPE::ARM_EXTENSION:
            m_extender = dynamic_cast<DragonTalon *>(motorControllers[i]);
            break;

        default:
            break;
        }
    }
    m_armTargetAngle = m_armMaster->GetRotations() * 360.0;
    m_extenderTargetRotations = m_extender->GetRotations();
}

void Arm::MoveArmPreset(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo, bool flip, bool second)
{
    if (cargo)
    {
        switch (height)
        {
        case PlacementHeights::PLACEMENT_HEIGHT::START_POSITION:
            m_armTargetAngle = cargoAngle[Arm::CARGO_ARM_PRESETS::CARGO_START_POSITION];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
            m_armTargetAngle = cargoAngle[Arm::CARGO_ARM_PRESETS::CARGO_FLOOR];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
            m_armTargetAngle = cargoAngle[Arm::CARGO_ARM_PRESETS::CARGO_SHIP];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
            m_armTargetAngle = cargoAngle[Arm::CARGO_ARM_PRESETS::CARGO_HP];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
            m_armTargetAngle = cargoAngle[Arm::CARGO_ARM_PRESETS::CARGO_LOW];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
            m_armTargetAngle = cargoAngle[Arm::CARGO_ARM_PRESETS::CARGO_MID];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
            m_armTargetAngle = cargoAngle[Arm::CARGO_ARM_PRESETS::CARGO_HIGH];
            break;

        default:
            // bad
            printf("Arm.cpp MoveArmPresets cargo switch default");
            break;
        }
        if (flip)
        {
            switch (height)
            {
                case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
                case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
                case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
                    m_armTargetAngle = -m_armTargetAngle;
                    break;

                default:
                    break;
            }
        }
    }
    else
    {
        switch (height)
        {
        case PlacementHeights::PLACEMENT_HEIGHT::START_POSITION:
            m_armTargetAngle = hatchAngle[Arm::HATCH_ARM_PRESETS::HATCH_START_POSITION];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
            m_armTargetAngle = hatchAngle[Arm::HATCH_ARM_PRESETS::HATCH_FLOOR];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
            m_armTargetAngle = hatchAngle[Arm::HATCH_ARM_PRESETS::HATCH_LOW];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
            m_armTargetAngle = hatchAngle[Arm::HATCH_ARM_PRESETS::HATCH_HP_SECOND];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
            m_armTargetAngle = second ? hatchAngle[Arm::HATCH_ARM_PRESETS::HATCH_LOW_SECOND] : hatchAngle[Arm::HATCH_ARM_PRESETS::HATCH_LOW];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
            m_armTargetAngle = second ? hatchAngle[Arm::HATCH_ARM_PRESETS::HATCH_MID_SECOND] : hatchAngle[Arm::HATCH_ARM_PRESETS::HATCH_MID];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
            m_armTargetAngle = second ? hatchAngle[Arm::HATCH_ARM_PRESETS::HATCH_HIGH_SECOND] : hatchAngle[Arm::HATCH_ARM_PRESETS::HATCH_HIGH];
            break;

        default:
            // bad
            printf("Arm.cpp MoveArmPresets hatch switch default");
            break;
        }

        if (flip)
        {
            switch (height)
            {
                case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
                case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
                    m_armTargetAngle = -m_armTargetAngle;
                    break;

                default:
                    break;
            }
        }
    }

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

void Arm::MoveExtentionPreset(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo, bool flip, bool second)
{
    if (cargo)
    {
        switch (height)
        {
        case PlacementHeights::PLACEMENT_HEIGHT::START_POSITION:
            m_extenderTargetRotations = extenderCargoInches[Arm::CARGO_ARM_PRESETS::CARGO_START_POSITION];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
            m_extenderTargetRotations = extenderCargoInches[Arm::CARGO_ARM_PRESETS::CARGO_FLOOR];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
            m_extenderTargetRotations = extenderCargoInches[Arm::CARGO_ARM_PRESETS::CARGO_SHIP];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
            m_extenderTargetRotations = extenderCargoInches[Arm::CARGO_ARM_PRESETS::CARGO_HP];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
            m_extenderTargetRotations = extenderCargoInches[Arm::CARGO_ARM_PRESETS::CARGO_LOW];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
            m_extenderTargetRotations = extenderCargoInches[Arm::CARGO_ARM_PRESETS::CARGO_MID];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
            m_extenderTargetRotations = extenderCargoInches[Arm::CARGO_ARM_PRESETS::CARGO_HIGH];
            break;

        default:
            // bad
            printf("Arm.cpp MoveExtentionPresets cargo switch default");
            break;
        }
    }
    else
    {
        switch (height)
        {
        case PlacementHeights::PLACEMENT_HEIGHT::START_POSITION:
            m_extenderTargetRotations = extenderHatchInches[Arm::HATCH_ARM_PRESETS::HATCH_START_POSITION];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
            m_extenderTargetRotations = extenderHatchInches[Arm::HATCH_ARM_PRESETS::HATCH_FLOOR];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
            m_extenderTargetRotations = extenderHatchInches[Arm::HATCH_ARM_PRESETS::HATCH_LOW];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
            m_extenderTargetRotations = !flip ? extenderHatchInches[Arm::HATCH_ARM_PRESETS::HATCH_HP_SECOND] : -extenderHatchInches[Arm::HATCH_ARM_PRESETS::HATCH_HP_SECOND];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
            m_extenderTargetRotations = second ? extenderHatchInches[Arm::HATCH_ARM_PRESETS::HATCH_LOW_SECOND] : extenderHatchInches[Arm::HATCH_ARM_PRESETS::HATCH_LOW];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
            m_extenderTargetRotations = second ? extenderHatchInches[Arm::HATCH_ARM_PRESETS::HATCH_MID_SECOND] : extenderHatchInches[Arm::HATCH_ARM_PRESETS::HATCH_MID];
            break;

        case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
            m_extenderTargetRotations = second ? extenderHatchInches[Arm::HATCH_ARM_PRESETS::HATCH_HIGH_SECOND] : extenderHatchInches[Arm::HATCH_ARM_PRESETS::HATCH_HIGH];
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

void Arm::MoveExtensionSpeed(double speed, bool climbMode)
{
    speed += EXTENDER_HOLD_POWER;
    m_extender->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
    CorrectExtenderPower(speed, climbMode); //if we are gonna be out of bounds, pull in
    m_extender->Set(speed);
}

void Arm::MoveExtensionInches(double inches)
{
    m_extender->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::ROTATIONS);
    m_extender->Set(inches);
    m_extenderTargetRotations = inches;
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
    return m_extender->GetRotations();
}

double Arm::GetExtenderTargetInches()
{
    return m_extenderTargetRotations;
}

IMechanism::MECHANISM_TYPE Arm::GetType() const
{
    return IMechanism::MECHANISM_TYPE::ARM;
}

double Arm::OurDegreesToRads(double ourDegrees)
{
    return -((ourDegrees / 360.0) - (1 / 4.0)) * 2 * M_PI;
}

void Arm::CorrectExtenderPower(double &power, bool climbMode)
{
    double degreesPerSecond = GetArmRealAngle() - m_previousArmRealAngle;
    degreesPerSecond / 0.02;

    double correctedAngle = GetArmRealAngle() + degreesPerSecond * 0.5;
    // double maxLegalExtender = (1-std::abs(cos(OurDegreesToRads(m_armTargetAngle)))) * 7.625;
    double realRads = OurDegreesToRads(GetArmRealAngle());
    double predictedRads = OurDegreesToRads(correctedAngle);

#if ROBOT == PRAC_BOT
    double realMaxLegalExtender = Map(std::abs(cos(realRads)), 1, 0.76, 1.175, m_extenderMaxDistance); //BIG TODO: make MAX_EXTENDER_DISTANCE constant
    double predictedMaxLegalExtender = Map(std::abs(cos(predictedRads)), 1, 0.76, 1.175, m_extenderMaxDistance);
#endif
#if ROBOT == COMP_BOT
    double realMaxLegalExtender = Map(std::abs(cos(realRads)), 1, 0.76, 1.25, m_extenderMaxDistance); //BIG TODO: make MAX_EXTENDER_DISTANCE constant
    double predictedMaxLegalExtender = Map(std::abs(cos(predictedRads)), 1, 0.76, 1.25, m_extenderMaxDistance);
#endif

    // frc::SmartDashboard::PutNumber("Max Legal Inches", maxLegalExtender);

    // frc::SmartDashboard::PutNumber("")
    if (GetExtenderRealInches() > realMaxLegalExtender || GetExtenderRealInches() > predictedMaxLegalExtender)
    {
        if (power >= EXTENDER_HOLD_POWER)
            power = climbMode ? EXTENDER_HOLD_POWER : -1;
    }
    else if (GetExtenderRealInches() < 0.0)
        power = power > EXTENDER_HOLD_POWER ? power : EXTENDER_HOLD_POWER;
        // power = power > 0 ? power : 0;

    if (GetExtenderRealInches() > m_extenderMaxDistance)
        power = power > 0 ? 0 : power;

    m_previousArmRealAngle = GetArmRealAngle();
}

double Arm::Map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Arm::SetParam(
    IMechanism::MECHANISM_PARAM_TYPE param, // <I> - parameter to set
    double value                            // <I> - parameter value
)
{
    switch (param)
    {
    // starting angle offsets
    case LEGAL_STARTING_ANGLE:
        m_armLegalStartingAngle = value;
        break;

    case TEST_STARTING_ANGLE:
        m_armTestStartingAngle = value;
        break;
    // starting extender inch offsets
    case EXTENDER_LEGAL_STARTING_INCHES:
        m_extenderLegalStartingInches = value;
        break;

    case EXTENDER_TEST_STARTING_INCHES:
        m_extenderTestStartingInches = value;
        break;
    // arm hatch angles
    case HATCH_FLOOR_ANGLE:
        hatchAngle[HATCH_FLOOR] = value;
        break;

    case HATCH_HP_SECOND_ANGLE:
        hatchAngle[HATCH_HP_SECOND] = value;
        break;

    case HATCH_LOW_ANGLE:
        hatchAngle[HATCH_LOW] = value;
        break;

    case HATCH_MID_ANGLE:
        hatchAngle[HATCH_MID] = value;
        break;

    case HATCH_HIGH_ANGLE:
        hatchAngle[HATCH_HIGH] = value;
        break;

    case HATCH_LOW_SECOND_ANGLE:
        hatchAngle[HATCH_LOW_SECOND] = value;
        break;

    case HATCH_MID_SECOND_ANGLE:
        hatchAngle[HATCH_MID_SECOND] = value;
        break;

    case HATCH_HIGH_SECOND_ANGLE:
        hatchAngle[HATCH_HIGH_SECOND] = value;
        break;

    // arm cargo angles
    case CARGO_FLOOR_ANGLE:
        cargoAngle[CARGO_FLOOR] = value;
        break;

    case CARGO_HP_ANGLE:
        cargoAngle[CARGO_HP] = value;
        break;

    case CARGO_SHIP_ANGLE:
        cargoAngle[CARGO_SHIP] = value;
        break;

    case CARGO_LOW_ANGLE:
        cargoAngle[CARGO_LOW] = value;
        break;

    case CARGO_MID_ANGLE:
        cargoAngle[CARGO_MID] = value;
        break;

    case CARGO_HIGH_ANGLE:
        cargoAngle[CARGO_HIGH] = value;
        break;

    // extender hatch inches
    case HATCH_FLOOR_EXTENSION:
        extenderHatchInches[HATCH_FLOOR] = value;
        break;

    case HATCH_HP_SECOND_EXTENSION:
        extenderHatchInches[HATCH_HP_SECOND] = value;
        break;

    case HATCH_LOW_EXTENSION:
        extenderHatchInches[HATCH_LOW] = value;
        break;

    case HATCH_MID_EXTENSION:
        extenderHatchInches[HATCH_MID] = value;
        break;

    case HATCH_HIGH_EXTENSION:
        extenderHatchInches[HATCH_HIGH] = value;
        break;

    case HATCH_LOW_SECOND_EXTENSION:
        extenderHatchInches[HATCH_LOW_SECOND] = value;
        break;

    case HATCH_MID_SECOND_EXTENSION:
        extenderHatchInches[HATCH_MID_SECOND] = value;
        break;

    case HATCH_HIGH_SECOND_EXTENSION:
        extenderHatchInches[HATCH_HIGH_SECOND] = value;
        break;

    // extender cargo inches
    case CARGO_FLOOR_EXTENSION:
        extenderCargoInches[CARGO_FLOOR] = value;
        break;

    case CARGO_HP_EXTENSION:
        extenderCargoInches[CARGO_HP] = value;
        break;

    case CARGO_SHIP_EXTENSION:
        extenderCargoInches[CARGO_SHIP] = value;
        break;

    case CARGO_LOW_EXTENSION:
        extenderCargoInches[CARGO_LOW] = value;
        break;

    case CARGO_MID_EXTENSION:
        extenderCargoInches[CARGO_MID] = value;
        break;

    case CARGO_HIGH_EXTENSION:
        extenderCargoInches[CARGO_HIGH] = value;
        break;

    default:
        printf("Arm.cpp error: recieving unexpected arm parameter. %d \n", param);
        break;
    }
}

void Arm::SetPID(
    PIDData *pid // <I> - PID control information
)
{
    if (pid->GetPidTarget() == PIDData::PID_TARGET::ARM)
    {
        m_armMaster->SetPIDF(pid->GetP(), pid->GetI(), pid->GetD(), pid->GetF());
        if (pid->GetMode() == PIDData::MOTION_MAGIC)
        {
            m_armMaster->ConfigMotionAcceleration(pid->GetMaxAcceleration());
            m_armMaster->ConfigMotionCruiseVelocity(pid->GetCruiseVelocity());
        }
    }
    else if (pid->GetPidTarget() == PIDData::PID_TARGET::EXTENDER)
    {
        m_extender->SetPIDF(pid->GetP(), pid->GetI(), pid->GetD(), pid->GetF());
        if (pid->GetMode() == PIDData::MOTION_MAGIC)
        {
            m_extender->ConfigMotionAcceleration(pid->GetMaxAcceleration());
            m_extender->ConfigMotionCruiseVelocity(pid->GetCruiseVelocity());
        }
    }
}

void Arm::SetPracticeStartingPos()
{
    m_armMaster->SetRotationOffset(m_armTestStartingAngle / 360.0);
    m_extender->SetRotationOffset(m_extenderTestStartingInches);

    ResetTarget();
}

void Arm::SetLegalStartingPos()
{
    m_armMaster->SetRotationOffset(m_armLegalStartingAngle / 360.0);
    m_extender->SetRotationOffset(m_extenderLegalStartingInches);

    ResetTarget();
}