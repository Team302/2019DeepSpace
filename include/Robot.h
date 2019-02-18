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
#include "driverassist/DriverAssist.h"

// include mechs for printing angles
#include "subsys/Arm.h"
#include "subsys/Climber.h"
#include "subsys/Intake.h"
#include "subsys/Wrist.h"


class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  void Vision();

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  DriverAssist* m_driverAssist;

  Arm* m_arm;
  Wrist* m_wrist;
  Intake* m_intake;
  Climber* m_climber;

  const double m_P_POSITION = 1.0;
  const double m_I_POSITION = 0.0; //1e-4
  const double m_D_POSITION = 0.1;
  const double m_F_POSITION = 0.0;
  const double m_MIN_POSITION = -1.0;
  const double m_MAX_POSITION = 1.0;
  
  const double m_P_VELOCITY = 5e-5;
  const double m_I_VELOCITY = 1e-6; //1e-6
  const double m_D_VELOCITY = 0.0;
  const double m_F_VELOCITY = 0.0;
  const double m_MIN_VELOCITY = -1.0;
  const double m_MAX_VELOCITY = 1.0;
};
