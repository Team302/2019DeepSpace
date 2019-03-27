/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <subsys/chassis/DragonChassis.h>

class HoldDrivePosition {
 public:
  HoldDrivePosition();

  void RunHoldMode();
  void SetLeftRightTargetOffsetPosition(double leftOffsetTargetPosition, double rightOffsetTargetPosition);
  void ResetLeftRightTargetPosition();
  double GetLeftDistanceToTarget();
  double GetRightDistanceToTarget();

 private:
  DragonChassis* m_chassis;
  double m_leftTargetPosition;
  double m_rightTargetPosition;
};
