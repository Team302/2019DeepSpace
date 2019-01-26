/*
/*   Created by Austin Szczesniak
/*  Date: 1-19-2019
*/

#pragma once

// Team 302
#include <subsys/IMechanism.h>
#include <hw/DragonTalon.h> 
#include <subsys/PlacementHeights.h>

class Wrist : public IMechanism {
 public:
  Wrist();

  enum PLACEMENT_HEIGHT
  {
    FLOOR,
    HUMAN_PLAYER,
    CARGOSHIP,
    ROCKET_LOW,
    ROCKET_MID,
    ROCKET_HIGH,
    MAX_PLACEMENT_HEIGHTS
  };

  void MoveWristPresets(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo, bool flip);
  void MoveWristManualSpeed(double speed);
  void MoveWristManualAngle(double angle);

  double GetWristAngle();

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

  // Talons
  DragonTalon* m_wristMotor;
};
