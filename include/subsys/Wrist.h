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
  void ResetTarget();

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

  void SetPracticeStartingPos();
  void SetLegalStartingPos();


 private:
  enum HATCH_WRIST_PRESETS
  {
    HATCH_KEEP_SAME = -1,
    HATCH_START_POSITION,
    HATCH_FLOOR,
    HATCH_HP_BELOW,
    HATCH_LOW,
    HATCH_MID,
    HATCH_HIGH,
    HATCH_HP_HOLE,
    HATCH_HP_ABOVE,
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
  };//                                                       
//                                 start  floor    hp     low     mid   high
  double hatchAngle[MAX_HATCH_POS] = { 0, 51.38, -66.88, 150.40, 90.54, 27.54, 83.00, 00.00 };
  //                               
  double cargoAngle[MAX_CARGO_POS] = { 0, -56.1, 64.03, -41.5, 17.86, -32.0, -48.30 };

  // Talons
  DragonTalon* m_wristMotor;

  double m_targetAngle;

  double m_wristTestStartingAngle;
  double m_wristLegalStartingAngle;
};
