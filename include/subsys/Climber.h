/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <subsys/IMechanism.h>
#include <hw/DragonTalon.h> 

class Climber : public IMechanism {
public:
  Climber(std::vector<IDragonMotorController*> motorControllers);

  void SetClimbDriveSpeed(double speed);
  void MoveClimbElevator(double speed);

  IMechanism::MECHANISM_TYPE GetType() const override;

private:
  DragonTalon* m_climbElevator;
  DragonTalon* m_climbWheel;
};
