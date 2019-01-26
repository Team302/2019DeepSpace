/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <subsys/IMechanism.h>
#include <hw/DragonTalon.h> 

class Intake : public IMechanism  {
 public:
  Intake();
  void IntakePreset(bool cargo);
  void IntakeManual(double speed);
 private:
  DragonTalon* m_intakeMotor;
};
