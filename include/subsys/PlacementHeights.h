/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

class PlacementHeights {
 public:
  enum PLACEMENT_HEIGHT
  {
    START_POSITION,
    FLOOR,
    HUMAN_PLAYER,
    HUMAN_PLAYER_HOLE,
    CARGOSHIP,
    ROCKET_LOW,
    ROCKET_MID,
    ROCKET_HIGH,
    MAX_PLACEMENT_HEIGHTS
  };

  PlacementHeights() = delete;
};
