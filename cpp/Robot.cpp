/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <cameraserver/CameraServer.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "hw/DragonVision.h"
#include <thread>

#include <hw/IDragonMotorController.h>
#include <hw/DragonTalon.h>
#include <hw/DragonSparkMax.h>
#include <subsys/MechanismFactory.h>
#include <subsys/chassis/DragonChassis.h>
#include <driverassist/DriverAssist.h>
#include <subsys/Arm.h>
#include <hw/LED.h>
#include <hw/LEDFactory.h>
#include <math.h>

#include <xmlhw/RobotDefn.h>
using namespace frc;


void Robot::Vision()
{
  //initialize variables
  DragonVision dragonCamera1;
  cs::VideoSink server;
  cs::UsbCamera camera1;
 
  //set up camera's width and height
  int width = 320;
  int height = 240;
  
  //int radius= 40;
  //cv::Scalar lightgreen(0,255,0);
 
  camera1 = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);//"cam1",0);
  camera1.SetResolution(width,height);//640,480
  server = frc::CameraServer::GetInstance()->GetServer();
  server.SetSource(camera1);
 
  cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo(); //or ("cam1");
  cvSink.SetSource(camera1);
  cvSink.SetEnabled(true);

  cs::CvSource outputStream = frc::CameraServer::GetInstance()->PutVideo("cam1",width, height);
  server.SetSource(outputStream);


  cv::Mat source;
  


 while(true)
  {
    if (cvSink.GrabFrame(source) == 0)
    {
        outputStream.NotifyError(cvSink.GetError());
        continue;
    }
    
    dragonCamera1.showCircle(source, width, height);
    dragonCamera1.showCross(source, width, height);
    outputStream.PutFrame(source);
    
  }
  
}
void Robot::RobotInit() {
 
  // std::thread v1(&Robot::Vision,this);
  // v1.detach();

  // CameraServer* cameraServer = CameraServer::GetInstance();
  // cameraServer->SetSize(CameraServer::kSize320x240);
  // cameraServer->StartAutomaticCapture();
  // cameraServer->

  // Read the robot definition from the xml configuration files and
  // create the hardware (chassis + mechanisms along with their talons,
  // solenoids, digital inputs, analog inputs, etc.
  RobotDefn::ParseXML();


  m_arm = MechanismFactory::GetMechanismFactory()->GetArm();
  m_climber = MechanismFactory::GetMechanismFactory()->GetClimber();
  m_intake = MechanismFactory::GetMechanismFactory()->GetIntake();
  m_wrist = MechanismFactory::GetMechanismFactory()->GetWrist();
  m_hatchMech = MechanismFactory::GetMechanismFactory()->GetHatchMech();

  if (m_arm == nullptr)
    printf("arm is NULLPTR!!!!!!!\n");
  if (m_climber == nullptr)
    printf("climber is NULLPTR!!!!!!!\n");
  if (m_intake == nullptr)
    printf("intake is NULLPTR!!!\n");
  if (m_wrist == nullptr)
    printf("wrist is NULLPTR!!!!!!!!!!\n");
  printf("robot.cpp after gettin mechanisms\n");

  m_arm->SetLegalStartingPos();
  m_wrist->SetLegalStartingPos();
  printf("robot.cpp after set legal starting pos\n");

  printf("pointer to dragonchassis instance %p\n", (void*)DragonChassis::GetInstance());
   m_driverAssist = new DriverAssist();
   printf("done making driver assist\n");

  m_loopCount = 0;
  /*  
  
  printf("OMG WE DEPLOYED CODE 23\n");

  // arm extend difference between comp and practice bot: 0.825

  // PRAC BOT
  // DragonTalon* armMaster = new DragonTalon(IDragonMotorController::TALON_TYPE::ARM_MASTER, 2, 1024, 180/233.4375 ); //((11.0/17) * (90/70.0))
  // DragonTalon* armSlave = new DragonTalon(IDragonMotorController::TALON_TYPE::ARM_SLAVE, 13, 1024, 180/233.4375 );
  // DragonTalon* intake = new DragonTalon(IDragonMotorController::TALON_TYPE::INTAKE, 7, 1024, 1); //id 7 on practice, 6 on comp
  // DragonTalon* wrist = new DragonTalon(IDragonMotorController::TALON_TYPE::WRIST, 5, 1024, 180/235.6); //(11.0/17) * (180.0/164.2)
  // DragonTalon* armExtend = new DragonTalon(IDragonMotorController::TALON_TYPE::ARM_EXTENSION, 4, 1024, 1);
  // DragonTalon* elevDrive = new DragonTalon(IDragonMotorController::TALON_TYPE::ELEVATOR_DRIVE, 10, 1024, 1);
  // DragonTalon* elevClimb = new DragonTalon(IDragonMotorController::TALON_TYPE::ELEVATOR_WINCH, 6, 1024, 1); 

  // COMP BOT
  DragonTalon* armMaster = new DragonTalon(IDragonMotorController::TALON_TYPE::ARM_MASTER, 2, 1024, 180/233.4375 ); //((11.0/17) * (90/70.0))
  DragonTalon* armSlave = new DragonTalon(IDragonMotorController::TALON_TYPE::ARM_SLAVE, 13, 1024, 180/233.4375 );
  DragonTalon* intake = new DragonTalon(IDragonMotorController::TALON_TYPE::INTAKE, 6, 1024, 1); //id 7 on practice, 6 on comp
  DragonTalon* wrist = new DragonTalon(IDragonMotorController::TALON_TYPE::WRIST, 5, 1024, 180/235.6); //(11.0/17) * (180.0/164.2)
  DragonTalon* armExtend = new DragonTalon(IDragonMotorController::TALON_TYPE::ARM_EXTENSION, 4, 1024, 1);
  DragonTalon* elevDrive = new DragonTalon(IDragonMotorController::TALON_TYPE::ELEVATOR_DRIVE, 10, 1024, 1);
  DragonTalon* elevClimb = new DragonTalon(IDragonMotorController::TALON_TYPE::ELEVATOR_WINCH, 11, 1024, 1);

  m_armMasterMotor = armMaster;
  m_wristMotor = wrist;
  m_extenderMotor = armExtend;

  DragonSparkMax* frontL = new DragonSparkMax(16, IDragonMotorController::TALON_TYPE::FRONT_LEFT_DRIVE, CANSparkMax::MotorType::kBrushless, (1/5.0));
  DragonSparkMax* middleL = new DragonSparkMax(1, IDragonMotorController::TALON_TYPE::MIDDLE_LEFT_DRIVE, CANSparkMax::MotorType::kBrushless, (1/5.0));
  DragonSparkMax* backL = new DragonSparkMax(3, IDragonMotorController::TALON_TYPE::BACK_LEFT_DRIVE, CANSparkMax::MotorType::kBrushless, (1/5.0));
  DragonSparkMax* frontR = new DragonSparkMax(15, IDragonMotorController::TALON_TYPE::FRONT_RIGHT_DRIVE, CANSparkMax::MotorType::kBrushless, (1/5.0));
  DragonSparkMax* middleR = new DragonSparkMax(14, IDragonMotorController::TALON_TYPE::MIDDLE_RIGHT_DRIVE, CANSparkMax::MotorType::kBrushless, (1/5.0));
  DragonSparkMax* backR = new DragonSparkMax(12, IDragonMotorController::TALON_TYPE::BACK_RIGHT_DRIVE, CANSparkMax::MotorType::kBrushless, (1/5.0));

  // set followers
  frontL->Follow(middleL);
  backL->Follow(middleL);
  frontR->Follow(middleR);
  backR->Follow(middleR);

  // set PID stuff
  middleL->SetPIDF(m_P_POSITION, m_I_POSITION, m_D_POSITION, m_F_POSITION, 0);
  middleR->SetPIDF(m_P_POSITION, m_I_POSITION, m_D_POSITION, m_F_POSITION, 0);
  middleL->SetPIDF(m_P_VELOCITY, m_I_VELOCITY, m_D_VELOCITY, m_F_VELOCITY, 1);
  middleR->SetPIDF(m_P_VELOCITY, m_I_VELOCITY, m_D_VELOCITY, m_F_VELOCITY, 1);


  frontL->Invert(true);
  middleL->Invert(true);
  backL->Invert(true);
  frontR->Invert(false);
  middleR->Invert(false);
  backR->Invert(false);

  // frontL->Encoder

  armMaster->Invert(false);
  armSlave->Invert(true);
  armExtend->Invert(false);
  intake->Invert(true);
  wrist->Invert(true);
  elevDrive->Invert(true);
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

  wrist->SetPIDF(5, 0, 10.0, 0);
  wrist->SetSensorInverted(false); //was true
  wrist->SetRotationOffset(158.74 / 360.0); // 55.55
  wrist->ConfigMotionAcceleration(150);
  wrist->ConfigMotionCruiseVelocity(200);

  armExtend->SetPIDF(20, 0, 0, 0);
  //practice bot
  // armExtend->SetRotationOffset(6.8 / INCHES_PER_REVOLUTION);
  //comp bot
  armExtend->SetRotationOffset(0.0 / INCHES_PER_REVOLUTION);

  armMaster->SetRotationOffset((-167.00) / 360.0); //-137
  armMaster->SetPIDF(15, 0, 0, 0);
  armMaster->ConfigMotionAcceleration(60);
  armMaster->ConfigMotionCruiseVelocity(200);
  armMaster->SetSensorInverted(true);
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

  m_arm = dynamic_cast<Arm*>(MechanismFactory::GetMechanismFactory()->GetIMechanism(IMechanism::MECHANISM_TYPE::ARM));
  m_climber = dynamic_cast<Climber*>(MechanismFactory::GetMechanismFactory()->GetIMechanism(IMechanism::MECHANISM_TYPE::CLIMBER));
  m_intake = dynamic_cast<Intake*>(MechanismFactory::GetMechanismFactory()->GetIMechanism(IMechanism::MECHANISM_TYPE::INTAKE));
  m_wrist = dynamic_cast<Wrist*>(MechanismFactory::GetMechanismFactory()->GetIMechanism(IMechanism::MECHANISM_TYPE::WRIST));

  DragonChassis::CreateDragonChassis(tempMotors, 6.0, 1, 1);
  DragonChassis::GetInstance()->SetVoltageRamping(0.25, 0);

  m_driverAssist = new DriverAssist();  
  */

  frc::SmartDashboard::PutBoolean("Robot Fipped", false);
  frc::SmartDashboard::PutBoolean("Cargo mode", false);
  frc::SmartDashboard::PutNumber("Target position enum", false);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  m_loopCount++;
}

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
 
}

void Robot::AutonomousPeriodic()
{
  Robot::MainPeriodic();
}

void Robot::TeleopInit() {

}

void Robot::TeleopPeriodic() 
{
  Robot::MainPeriodic();
}

void Robot::MainPeriodic()
{
  m_driverAssist->Update();

  //TODO: put these prints in a debug mode or something... maybe
  // smartdashboard mechanisms
  frc::SmartDashboard::PutNumber("Arm Target Angle", m_arm->GetArmTargetAngle());
  frc::SmartDashboard::PutNumber("Arm Real Angle", m_arm->GetArmRealAngle());
  
  frc::SmartDashboard::PutNumber("Wrist Target Angle", m_wrist->GetWristTargetAngle());
  frc::SmartDashboard::PutNumber("Wrist Real Angle", m_wrist->GetWristRealAngle());

  frc::SmartDashboard::PutNumber("Extender Target Inches", m_arm->GetExtenderTargetInches());
  frc::SmartDashboard::PutNumber("Extender Real Inches", m_arm->GetExtenderRealInches());
}

void Robot::TestInit()
{
  // set offsets for test robot starting config
  m_arm->SetPracticeStartingPos();
  m_wrist->SetPracticeStartingPos();
  m_hatchMech->SetPracticeStartingPos();
}

void Robot::DisabledPeriodic()
{
  LED* back = LEDFactory::GetInstance()->GetLED(LEDFactory::LED_USAGE::UNDER_BACK);
  LED* front = LEDFactory::GetInstance()->GetLED(LEDFactory::LED_USAGE::UNDER_FRONT);
  LED* top = LEDFactory::GetInstance()->GetLED(LEDFactory::LED_USAGE::TOP);

  double fadingGreen = m_loopCount * 0.02;
  fadingGreen /= 3.0;

  double fadingFront = (std::sin(fadingGreen * M_PI_2) + 1.0) / 2.0;
  double fadingBack = (std::cos(fadingGreen * M_PI_2) + 1.0) / 2.0;
  double fadingTop = 1-fadingBack;

  fadingBack *= fadingBack * fadingBack;
  fadingFront *= fadingFront * fadingFront;
  fadingTop *= fadingTop * fadingTop;

  fadingBack *= 0.1;
  fadingFront *= 0.1;
  fadingTop *= 0.1;
  
  if (back != nullptr)
    back->SetRGB(0, fadingBack, 0);
  if (front != nullptr)
    front->SetRGB(0, fadingFront, 0);
  if (top != nullptr)
    top->SetRGB(fadingTop, fadingTop, fadingTop);
}



void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
