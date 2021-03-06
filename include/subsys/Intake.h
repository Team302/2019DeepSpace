/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <subsys/IMechanism.h>
#include <hw/DragonTalon.h> 

class Intake : public IMechanism  
{
 public:
  Intake(std::vector<IDragonMotorController*> motorControllers);
  void IntakePreset(bool cargo, bool outtake);
  void IntakeManual(double speed);
  void EnableBrakeMode(bool brakeEnabled);

  bool ObjectPresent();

  IMechanism::MECHANISM_TYPE GetType() const override;
  void SetParam
  (
      IMechanism::MECHANISM_PARAM_TYPE  param,          // <I> - parameter to set
      double                            value           // <I> - parameter value
  ) override;
  void SetPID
  (
      PIDData*        pid                 // <I> - PID control information
  ) override;



  
 private:
  DragonTalon* m_intakeMotor;

  // Speeds for intake/outtake. Cargo and Hatch intake speeds should be opposite signs
  double m_cargoIntakeSpeed  = 1.0;
  double m_cargoOuttakeSpeed = -1.0;
  double m_hatchIntakeSpeed  = -1.0;
  double m_hatchOuttakeSpeed = 1.0;
};
