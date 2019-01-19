/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include <iostream>
// FRC
#include <frc/smartdashboard/SmartDashboard.h>
// Network Tables
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  // Motor Declarations 
  m_rightMotor = new TalonSRX(1);
    m_rightMotor->SetInverted(true);
  m_leftMotor = new TalonSRX(2);
    m_leftMotor->SetInverted(false);

  m_limelight = new DragonLimelight();
  m_controller = new frc::XboxController(0);
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() 
{
  m_limelight->PrintValues();
  m_limelight->ToggleSnapshot(DragonLimelight::SNAPSHOT_MODE::SNAP_OFF);
  m_limelight->SetLEDMode(DragonLimelight::LED_MODE::LED_OFF);
}

void Robot::AutonomousPeriodic() 
{
  m_rightMotor->Set(ControlMode::PercentOutput, 0);
  m_leftMotor->Set(ControlMode::PercentOutput, 0);

  if(m_controller->GetAButtonPressed())
  {
    if(camMode)
    {
      camMode = !camMode;
      m_limelight->SetStreamMode(DragonLimelight::STREAM_MODE::STREAM_MAIN_AND_SECOND);
    }
    else
    {
      camMode = !camMode;
      m_limelight->SetStreamMode(DragonLimelight::STREAM_MODE::STREAM_SECOND_AND_MAIN);
    }
  }
}

void Robot::TeleopInit() 
{
  m_limelight->PrintValues();
  m_limelight->SetLEDMode(DragonLimelight::LED_MODE::LED_ON);
  m_limelight->SetStreamMode(DragonLimelight::STREAM_MODE::STREAM_MAIN_AND_SECOND);
}

void Robot::TeleopPeriodic() 
{ 
  if(m_controller->GetXButtonPressed())
    visMode = !visMode;
  
  if(visMode)
  {
    m_limelight->SetLEDMode(DragonLimelight::LED_MODE::LED_ON);
    m_limelight->SetCamMode(DragonLimelight::CAM_MODE::CAM_VISION );
    tx = m_limelight->GetTargetHorizontalOffset();
    ta = m_limelight->GetTargetArea();
    double offset = (22 - ta) * 0.01;

    if (ta > 0.0) {
      lSpeed = (-tx * 0.1) + offset;
      rSpeed = (tx * 0.1) + offset;
    }
    else{
      lSpeed = -0.02;
      rSpeed = -0.02;
    }
  }
  else
  {
    m_limelight->SetLEDMode(DragonLimelight::LED_MODE::LED_OFF);
    m_limelight->SetCamMode(DragonLimelight::CAM_MODE::CAM_DRIVER);

    if(m_controller->GetAButtonPressed())
    {
      if(camMode)
        m_limelight->SetStreamMode(DragonLimelight::STREAM_MODE::STREAM_MAIN_AND_SECOND);
      else
        m_limelight->SetStreamMode(DragonLimelight::STREAM_MODE::STREAM_SECOND_AND_MAIN);

      camMode = !camMode;
    }
    
    if(false)
      throttle = m_controller->GetY(frc::GenericHID::JoystickHand::kLeftHand);
    else
      throttle = -m_controller->GetY(frc::GenericHID::JoystickHand::kLeftHand);

      yaw = m_controller->GetX(frc::GenericHID::JoystickHand::kRightHand);
      rSpeed = throttle + yaw;
      lSpeed = throttle - yaw; 
  }
  frc::SmartDashboard::PutBoolean("Vis Mode", visMode);
  frc::SmartDashboard::PutBoolean("Cam mode", camMode);
  frc::SmartDashboard::PutNumber("Right Speed", rSpeed);
  frc::SmartDashboard::PutNumber("Left Speed", lSpeed);
  m_rightMotor->Set(ControlMode::PercentOutput, rSpeed);
  m_leftMotor->Set(ControlMode::PercentOutput, lSpeed);
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
