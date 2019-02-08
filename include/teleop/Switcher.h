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
#include <vector>

//Test include
#include "frc/XboxController.h"

class Switcher {
 public:
  Switcher();

  void DriveUpdate();       // updates chassis
  void GamepieceUpdate();   // updates arm, wrist, intake
  void ClimberUpdate();     // updates climber

private:
  Arm* m_arm;
  Intake* m_intake;
  Wrist* m_wrist;
  DragonChassis* m_chassis;
  Climber* m_climber;

  const bool FRONT_LEFT_SPARK_INVERTED = false;
  const bool MIDDLE_LEFT_SPARK_INVERTED = false;
  const bool BACK_LEFT_SPARK_INVERTED = false;
  const bool FRONT_RIGHT_SPARK_INVERTED = true;
  const bool MIDDLE_RIGHT_SPARK_INVERTED = true;
  const bool BACK_RIGHT_SPARK_INVERTED = true;

private:
  // GAMEPIECE THINGS
  double m_armTargetPosition;
  double m_intakeSpeed;
  double m_wristTargetPosition; // This might get used
  double m_wristSpeed;
  double m_extendSpeed;
  // CLIMBER THINGS
  double m_climbDriveSpeed;
  double m_climbElevSpeed;
  bool m_allowClimbDrive; 
  bool m_dropBuddyClimb;

  const double ELEV_SPEED = 1.0;

  // Test things, need to be replaced soon
  frc::XboxController* m_mainController;
  frc::XboxController* m_secondaryController;
};