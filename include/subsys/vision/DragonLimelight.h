/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include <frc/smartdashboard/SmartDashboard.h>

using namespace nt;

class DragonLimelight {
 public:
  DragonLimelight();

  //Enums
  enum LED_MODE 
  {
    LED_DEFUALT,
    LED_OFF,
    LED_BLINK,
    LED_ON
  };

  enum CAM_MODE
  {
    CAM_VISION,
    CAM_DRIVER
  };

  enum STREAM_MODE
  {
    STREAM_DEFAULT,  // side by side if two cams
    STREAM_MAIN_AND_SECOND, // Second Cam bottom right of Main Cam
    STREAM_SECOND_AND_MAIN // Main Cam bottom right of Second Cam
  };

  enum SNAPSHOT_MODE
  {
    SNAP_OFF,
    SNAP_ON
  };

  // Getters
  double HasTarget();
  double GetTargetHorizontalOffset();
  double GetTargetVerticalOffset();
  double GetTargetArea();
  double GetTargetSkew();
  double GetPipelineLatency();
  // Setters
  void SetLEDMode
  (
    DragonLimelight::LED_MODE mode // 0-Default, 1-Off, 2-Blink, 3-On 
  );

  void SetCamMode
  (
    DragonLimelight::CAM_MODE mode // 0-Vision, 1-Driver
  );

  void SetPipeline
  (
    int pipeline // 0-9 
  );

  void SetStreamMode
  (
    DragonLimelight::STREAM_MODE mode // 0-Side By Side, 1-Second cam bottom right of main, 2-Main bottom right second
  );

  void ToggleSnapshot
  (
    DragonLimelight::SNAPSHOT_MODE toggle // 0-No snapshots 1- two snapshots/second: Max of 32 saved
  );

  void PrintValues(); // Prints out all values to ensure everything is working and connected

 private:
  std::shared_ptr<NetworkTable> table;

};
