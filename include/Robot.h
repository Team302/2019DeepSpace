/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/XboxController.h>
// Network Tables
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
// CTRE
#include <ctre/phoenix/ErrorCode.h>
#include <ctre/phoenix/MotorControl/CAN/TalonSRX.h>
#include <frc/XboxController.h>

//Dragon Includes
#include <subsys/vision/DragonLimelight.h>

using namespace ctre::phoenix;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  // Xbox Controller
  frc::XboxController* m_controller;
  // Network Tables
  std::shared_ptr<NetworkTable> table;
  // CTRE
  TalonSRX* m_rightMotor;
  TalonSRX* m_leftMotor;
  bool invert = false;
  double yaw;
  double throttle;
  double rSpeed;
  double lSpeed;
  const double SPEED_CONST = 0.7;
  // limelight Stuff
  DragonLimelight* m_limelight;
  double tv;
  double ty;
  double tx;
  double ts;
  double ta;
  double tl;
  bool camMode = false;
  bool visMode = false;
};
