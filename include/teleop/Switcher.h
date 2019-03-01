#pragma once

// Dragon Includes
#include <subsys/Arm.h>
#include <subsys/Intake.h>
#include <subsys/Wrist.h>
#include <subsys/Climber.h>
#include <subsys/chassis/DragonChassis.h>
#include <teleop/TeleopControl.h>
#include <controllers/DragonXBox.h>
#include "hw/DragonSparkMax.h"
#include "subsys/vision/DragonLimelight.h"
#include <vector>

//Test include
#include "frc/XboxController.h"

class Switcher {
 public:
  Switcher();

  void DriveUpdate();       // updates chassis
  void GamepieceUpdate(bool cargo);   // updates arm, wrist, intake
  void ClimberUpdate();     // updates climber

  frc::XboxController* m_mainController;
  frc::XboxController* m_secondaryController;

private:
  Arm* m_arm;
  Intake* m_intake;
  Wrist* m_wrist;
  DragonChassis* m_chassis;
  Climber* m_climber;

  DragonLimelight* m_limelight;

  // CLIMBER THINGS
  double m_climbDriveSpeed;
  double m_climbElevSpeed;
  bool m_allowClimbDrive; 
  bool m_dropBuddyClimb;
  // DRIVER THINGS
  bool m_visionMode;
  bool m_camMode;
  bool m_holdMode;
  double m_leftTargetInches;
  double m_rightTargetInches;
  
  const double HOLD_MODE_MAX_INCHES_PER_SECOND_TURNING = 4.0;
  const double HOLD_MODE_MAX_INCHES_PER_SECOND_FORWARD = 6.0;

  const double ELEV_SPEED = 1.0;

};