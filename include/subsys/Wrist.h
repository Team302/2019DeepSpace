/*
/*   Created by Austin Szczesniak
/*  Date: 1-19-2019
*/

#pragma once

// Team 302
#include <subsys/IMechanism.h>
#include <hw/DragonTalon.h>
#include <hw/IDragonMotorController.h>
#include <subsys/PlacementHeights.h>

class Wrist : public IMechanism {
 public:
  Wrist(std::vector<IDragonMotorController*> motorControllers);

  void MoveWristPresets(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo, bool flip);
  void MoveWristMotionMagic(double angle);
  void MoveWristManualSpeed(double speed);
  void MoveWristManualAngle(double angle);

  double GetWristRealAngle();
  double GetWristTargetAngle();

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
  enum HATCH_WRIST_PRESETS
  {
    HATCH_KEEP_SAME = -1,
    HATCH_START_POSITION,
    HATCH_FLOOR,
    HATCH_LOW,
    HATCH_MID,
    HATCH_HIGH,
    MAX_HATCH_POS
  };

  enum CARGO_WRIST_PRESETS
  {
    CARGO_KEEP_SAME = -1,
    CARGO_START_POSITION,
    CARGO_FLOOR,
    CARGO_HP,
    CARGO_SHIP,
    CARGO_LOW,
    CARGO_MID,
    CARGO_HIGH,
    MAX_CARGO_POS
  };

  double hatchAngle[MAX_HATCH_POS] = { 0, 48.6, 120, 90, 20 };
  double cargoAngle[MAX_CARGO_POS] = { 0, 48.6, 55.56, -52.65, 17.86, -32.0, -44 };

  // Talons
  DragonTalon* m_wristMotor;

  double m_targetAngle;
};
