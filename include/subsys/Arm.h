/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsys/IMechanism.h"
#include <hw/DragonTalon.h> 
#include <subsys/PlacementHeights.h>

class Arm : public IMechanism 
{
public:
  Arm(std::vector<IDragonMotorController*> motorControllers);
  
  void MoveArmPresets(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo, bool flip);
  void MoveArmManualSpeed(double speed);
  void MoveArmManualAngle(double angle);

  void MoveArmExtensionInches(double inches);
  void MoveArmExtensionSpeed(double speed);

  double GetArmCurrentRealAngle();
  double GetArmCurrentTargetAngle();

  IMechanism::MECHANISM_TYPE GetType() const override;

private: 
  enum HATCH_WRIST_PRESETS
  {
    HATCH_KEEP_SAME = -1,
    HATCH_FLOOR,
    HATCH_LOW,
    HATCH_MID,
    HATCH_HIGH,
    MAX_HATCH_POS
  };

  enum CARGO_WRIST_PRESETS
  {
    CARGO_KEEP_SAME = -1,
    CARGO_FLOOR,
    CARGO_HP,
    CARGO_SHIP,
    CARGO_LOW,
    CARGO_MID,
    CARGO_HIGH,
    MAX_CARGO_POS
  };

  double hatchAngle[MAX_HATCH_POS] = { 1, 2, 3, 4 };
  double cargoAngle[MAX_CARGO_POS] = { 1, 2, 3, 4, 5, 6 };
  
  DragonTalon* m_armMaster;
  DragonTalon* m_extender;
};
