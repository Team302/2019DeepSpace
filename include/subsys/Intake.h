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
  Intake(std::vector<IDragonMotorController*> motorControllers);
  void IntakePreset(bool cargo, bool outtake);
  void IntakeManual(double speed);

  bool ObjectPresent();

  IMechanism::MECHANISM_TYPE GetType() const override;
  
 private:
  DragonTalon* m_intakeMotor;

  // Speeds for intake/outtake. Cargo and Hatch intake speeds should be opposite signs
  const double CARGO_INTAKE_SPEED = 1.0;
  const double CARGO_OUTTAKE_SPEED = -1.0;
  const double HATCH_INTAKE_SPEED = -1.0;
  const double HATCH_OUTTAKE_SPEED = 1.0;
};
