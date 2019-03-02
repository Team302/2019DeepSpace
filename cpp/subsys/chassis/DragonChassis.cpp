/*
* DragonChassis.cpp
*
* Date Created: Jan 21, 2019
* Author: Jonah Shader
*/

#include "subsys/chassis/DragonChassis.h"
#include <iostream>
#include <cmath>

DragonChassis* DragonChassis::m_dragonChassis = nullptr;

DragonChassis::DragonChassis(IDragonMotorControllerVector motorControllers, double wheelDiameter) :
m_frontLeft(nullptr),
m_middleLeft(nullptr),
m_backLeft(nullptr),
m_frontRight(nullptr),
m_middleRight(nullptr),
m_backRight(nullptr),
m_wheelDiameter(wheelDiameter),
m_leftDistanceOffset(0.0),
m_rightDistanceOffset(0.0)
{
    // Get all of the motors from the motorControllers vector into the specific motors
    for (int i = 0; i < motorControllers.size(); i++)
    {
        IDragonMotorController* element = motorControllers[i];
        switch (element->GetType())
        {
            case IDragonMotorController::FRONT_LEFT_DRIVE:
                m_frontLeft = element;
                break;

            case IDragonMotorController::MIDDLE_LEFT_DRIVE:
                m_middleLeft = element;
                break;

            case IDragonMotorController::BACK_LEFT_DRIVE:
                m_backLeft = element;
                break;

            case IDragonMotorController::FRONT_RIGHT_DRIVE:
                m_frontRight = element;
                break;

            case IDragonMotorController::MIDDLE_RIGHT_DRIVE:
                m_middleRight = element;
                break;

            case IDragonMotorController::BACK_RIGHT_DRIVE:
                m_backRight = element;
                break;

            default:
                break;
        }
    }
    // Zero out the encoder values right away
    ResetChassis();
}

void DragonChassis::CreateDragonChassis(IDragonMotorControllerVector motorControllers, double wheelDiameter)
{
    if (DragonChassis::m_dragonChassis == nullptr)
        DragonChassis::m_dragonChassis = new DragonChassis(motorControllers, wheelDiameter);
}

DragonChassis* DragonChassis::GetInstance()
{
    return DragonChassis::m_dragonChassis;
}

double DragonChassis::GetVelocity() const
{
    return (GetLeftVelocity() + GetRightVelocity()) / 2.0;
}

double DragonChassis::GetLeftVelocity() const
{
    double bestValue = GetBestValue(m_frontLeft->GetRPS(), m_middleLeft->GetRPS(), m_backLeft->GetRPS());
    return bestValue * m_wheelDiameter * M_PI;
}

double DragonChassis::GetRightVelocity() const
{
    double bestValue = GetBestValue(m_frontRight->GetRPS(), m_middleRight->GetRPS(), m_backRight->GetRPS());
    return bestValue * m_wheelDiameter * M_PI;
}

double DragonChassis::GetDistance() const
{
    double leftDistance = GetLeftDistance() - m_leftDistanceOffset;
    double rightDistance = GetRightDistance() - m_rightDistanceOffset;
    return (leftDistance + rightDistance) / 2.0;
}

double DragonChassis::GetBestValue(double a, double b, double c) const
{
    double average = (a + b + c) / 3.0;
    int closest = 0;
    double closestValue = abs(average - a);

    if (abs(average - b) < closestValue)
    {
        closest = 1;
        closestValue = abs(average - b);
    }
    if (abs(average - c) < closestValue)
    {
        closest = 2;
    }

    switch (closest)
    {
        case 0:
            return a;
        case 1:
            return b;
        case 2:
            return c;
        default:
            return 0;
    }
}

double DragonChassis::GetLeftDistance() const
{
    double bestValue = GetBestValue(m_frontLeft->GetRotations(), m_middleLeft->GetRotations(), m_backLeft->GetRotations());
    return bestValue * m_wheelDiameter * M_PI;
}

double DragonChassis::GetRightDistance() const
{
    double bestValue = GetBestValue(m_frontRight->GetRotations(), m_middleRight->GetRotations(), m_backRight->GetRotations());
    return bestValue * m_wheelDiameter * M_PI;
}

void DragonChassis::EnableBrakeMode(bool enabled)
{
    m_frontLeft->EnableBrakeMode(enabled);
    m_middleLeft->EnableBrakeMode(enabled);
    m_backLeft->EnableBrakeMode(enabled);
    m_frontRight->EnableBrakeMode(enabled);
    m_middleRight->EnableBrakeMode(enabled);
    m_backRight->EnableBrakeMode(enabled);
}

void DragonChassis::SetDriveMode(IDragonMotorController::DRAGON_CONTROL_MODE controlMode)
{
    m_frontLeft->SetControlMode(controlMode);
    m_middleLeft->SetControlMode(controlMode);
    m_backLeft->SetControlMode(controlMode);
    m_frontRight->SetControlMode(controlMode);
    m_middleRight->SetControlMode(controlMode);
    m_backRight->SetControlMode(controlMode);
}

void DragonChassis::SetLeftRightMagnitudes(double left, double right)
{
    m_frontLeft->Set(left);
    m_middleLeft->Set(left);
    m_backLeft->Set(left);

    m_frontRight->Set(right);
    m_middleRight->Set(right);
    m_backRight->Set(right);
}

void DragonChassis::UpdateChassis()
{
    // unused at the moment
}

void DragonChassis::EnableCurrentLimiting(bool enabled)
{
    // TODO:
}

void DragonChassis::ResetChassis()
{
    m_leftDistanceOffset = GetLeftDistance();
    m_rightDistanceOffset = GetRightDistance();
}