/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#include <hw/IDragonMotorController.h>
#include <hw/DragonTalon.h>
#include <hw/DragonSparkMax.h>
#include <subsys/MechanismFactory.h>
#include <subsys/chassis/DragonChassis.h>
#include <driverassist/DriverAssist.h>

#include <xmlhw/RobotDefn.h>


void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  // Read the robot definition from the xml configuration files and
  // create the hardware (chassis + mechanisms along with their talons,
  // solenoids, digital inputs, analog inputs, etc.
  RobotDefn::ParseXML();
  /*
  DragonTalon* armMaster = new DragonTalon(IDragonMotorController::TALON_TYPE::ARM_MASTER, 2, 1024, ((11.0/17) * (90/70.0)) );
  DragonTalon* armSlave = new DragonTalon(IDragonMotorController::TALON_TYPE::ARM_SLAVE, 13, 1024, ((11.0/17) * (90/70.0)) );
  DragonTalon* intake = new DragonTalon(IDragonMotorController::TALON_TYPE::INTAKE, 7, 1024, 1);
  DragonTalon* wrist = new DragonTalon(IDragonMotorController::TALON_TYPE::WRIST, 5, 1024, (11.0/17) * (180.0/164.2));
  DragonTalon* armExtend = new DragonTalon(IDragonMotorController::TALON_TYPE::ARM_EXTENSION, 4, 1024, 1);
  DragonTalon* elevDrive = new DragonTalon(IDragonMotorController::TALON_TYPE::ELEVATOR_DRIVE, 10, 1024, 1);
  DragonTalon* elevClimb = new DragonTalon(IDragonMotorController::TALON_TYPE::ELEVATOR_WINCH, 6, 1024, 1);

  DragonSparkMax* frontL = new DragonSparkMax(0, IDragonMotorController::TALON_TYPE::FRONT_LEFT_DRIVE, CANSparkMax::MotorType::kBrushless);
  DragonSparkMax* middleL = new DragonSparkMax(1, IDragonMotorController::TALON_TYPE::MIDDLE_LEFT_DRIVE, CANSparkMax::MotorType::kBrushless);
  DragonSparkMax* backL = new DragonSparkMax(3, IDragonMotorController::TALON_TYPE::BACK_LEFT_DRIVE, CANSparkMax::MotorType::kBrushless);
  DragonSparkMax* frontR = new DragonSparkMax(15, IDragonMotorController::TALON_TYPE::FRONT_RIGHT_DRIVE, CANSparkMax::MotorType::kBrushless);
  DragonSparkMax* middleR = new DragonSparkMax(14, IDragonMotorController::TALON_TYPE::MIDDLE_RIGHT_DRIVE, CANSparkMax::MotorType::kBrushless);
  DragonSparkMax* backR = new DragonSparkMax(12, IDragonMotorController::TALON_TYPE::BACK_RIGHT_DRIVE, CANSparkMax::MotorType::kBrushless);

  frontL->Invert(false);
  middleL->Invert(false);
  backL->Invert(false);
  frontR->Invert(true);
  middleR->Invert(true);
  backR->Invert(true);

  armMaster->Invert(false);
  armSlave->Invert(true);
  armExtend->Invert(false);
  intake->Invert(false);
  wrist->Invert(true);
  elevDrive->Invert(false);
  elevClimb->Invert(false);

  frontL->EnableBrakeMode(false);
  middleL->EnableBrakeMode(false);
  backL->EnableBrakeMode(false);
  frontR->EnableBrakeMode(false);
  middleR->EnableBrakeMode(false);
  backR->EnableBrakeMode(false);

  armMaster->EnableBrakeMode(true);
  armSlave->EnableBrakeMode(true);
  armExtend->EnableBrakeMode(true);
  intake->EnableBrakeMode(true);
  wrist->EnableBrakeMode(true);
  elevDrive->EnableBrakeMode(true);
  elevClimb->EnableBrakeMode(true);

  wrist->SetPIDF(5, 0, 0, 0);
  wrist->SetSensorInverted(true);
  wrist->SetRotationOffset(50.37 / 360);

  armMaster->SetRotationOffset( (-118.2 / 360) * (90/70.0) - (5.557 / 360) );
  armMaster->SetPIDF(15, 0, 0, 0);
  armSlave->SetAsSlave(2);

  IDragonMotorControllerVector tempMotors;
  tempMotors.emplace_back(armMaster);
  tempMotors.emplace_back(armSlave);
  tempMotors.emplace_back(armExtend);
  tempMotors.emplace_back(intake);
  tempMotors.emplace_back(wrist);
  tempMotors.emplace_back(elevDrive);
  tempMotors.emplace_back(elevClimb);
  
  tempMotors.emplace_back(frontL);
  tempMotors.emplace_back(middleL);
  tempMotors.emplace_back(backL);
  tempMotors.emplace_back(frontR);
  tempMotors.emplace_back(middleR);
  tempMotors.emplace_back(backR);

  DragonDigitalInputVector tempDigital;
  DragonAnalogInputVector tempAnalog;
  DragonServoVector tempServo;

  MechanismFactory::GetMechanismFactory()->CreateMechanism(IMechanism::MECHANISM_TYPE::ARM, tempMotors, tempDigital, tempAnalog, tempServo);
  MechanismFactory::GetMechanismFactory()->CreateMechanism(IMechanism::MECHANISM_TYPE::CLIMBER, tempMotors, tempDigital, tempAnalog, tempServo);
  MechanismFactory::GetMechanismFactory()->CreateMechanism(IMechanism::MECHANISM_TYPE::INTAKE, tempMotors, tempDigital, tempAnalog, tempServo);
  MechanismFactory::GetMechanismFactory()->CreateMechanism(IMechanism::MECHANISM_TYPE::WRIST, tempMotors, tempDigital, tempAnalog, tempServo);

  DragonChassis::CreateDragonChassis(tempMotors, 6.0);
  */

  m_driverAssist = new DriverAssist();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic()
{
  m_driverAssist->Update();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
