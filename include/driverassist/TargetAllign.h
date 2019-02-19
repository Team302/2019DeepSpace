/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "driverassist/HoldDrivePosition.h"
#include "subsys/vision/DragonLimelight.h"

class TargetAllign {
 public:
  enum ALLIGNMENT_STATE
  {
    ALLIGNING,
    DONE
  };

  void Init();
  void Update();
  bool IsDone();

  TargetAllign();
  ~TargetAllign() = default;

 private:
  HoldDrivePosition* m_holdDrivePositon;
  DragonLimelight* m_limelight;

  // Some Vars
  ALLIGNMENT_STATE m_currentState;
  const double DRIVE_SPEED = 4.0;
  const double DONE_TARGET_OFFSET = 1.0;
};
