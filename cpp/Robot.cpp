/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
//#include "frc/WPILib.h"
#include "frc/WPILib.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <cameraserver/CameraServer.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <teleop/IDrive.h>
#include "Robot.h"
#include "hw/DragonVision.h"
#include <thread>
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
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  std::thread v1(&Robot::Vision,this);
  v1.detach();
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

void Robot::TeleopInit() {

}

void Robot::TeleopPeriodic() 
{
  /*
  frc::Joystick joy1{0};
  bool prevTrigger = false;
  if (joy1.GetTrigger() && !prevTrigger)
  {
    //printf("Setting camera 2\n");
    server.SetSource(camera2);
  } else if (!joy1.GetTrigger() && prevTrigger) 
  {
    //printf("Setting camera 1\n");
    server.SetSource(camera1);
  }
  prevTrigger = joy1.GetTrigger();
  */
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
