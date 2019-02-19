/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "driverassist/HoldDrivePosition.h"

HoldDrivePosition::HoldDrivePosition() :    m_chassis(DragonChassis::GetInstance())
{
    m_leftTargetPosition = m_chassis->GetLeftMiddleDistance();
    m_rightTargetPosition = m_chassis->GetRightMiddleDistance();
}

void HoldDrivePosition::RunHoldMode()
{
    m_chassis->SetDriveMode(DragonChassis::DRIVE_MODE::POSITION_INCHES);
    m_chassis->SetLeftRightMagnitudes(m_leftTargetPosition, m_rightTargetPosition);
}

void HoldDrivePosition::SetLeftRightTargetOffsetPosition(double leftOffsetTargetPosition, double rightOffsetTargetPosition)
{
    m_leftTargetPosition += leftOffsetTargetPosition;
    m_rightTargetPosition += rightOffsetTargetPosition;
}

void HoldDrivePosition::ResetLeftRightTargetPosition()
{
    m_leftTargetPosition = m_chassis->GetLeftMiddleDistance();
    m_rightTargetPosition = m_chassis->GetRightMiddleDistance();
}
