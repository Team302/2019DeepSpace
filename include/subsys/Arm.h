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
  
  void MoveArmPreset(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo, bool flip, bool second);
  void MoveArmMotionMagic(double angle);
  void MoveArmSpeed(double speed);
  void MoveArmAngle(double angle);
  void ResetTarget();

  void MoveExtentionPreset(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo, bool flip, bool second);
  void MoveExtensionSpeed(double speed, bool climbMode);
  void MoveExtensionInches(double inches);

  double GetArmRealAngle();
  double GetArmTargetAngle();

  double GetExtenderRealInches();
  double GetExtenderTargetInches();

  IMechanism::MECHANISM_TYPE GetType() const override;
  void SetParam 
  (
      IMechanism::MECHANISM_PARAM_TYPE  param,          // <I> - parameter to set
      double                            value           // <I> - parameter value
  ) override;
  void SetPID
  (
      PIDData*       pid                 // <I> - PID control information
  ) override;

  void SetPracticeStartingPos();
  void SetLegalStartingPos();
  

private: 
  //TODO: rename these to HATCH_ARM_PRESETS and CARGO_ARM_PRESETS... not wrist
  enum HATCH_ARM_PRESETS
  {
    HATCH_KEEP_SAME = -1,
    HATCH_START_POSITION,
    HATCH_FLOOR,
    HATCH_HP_SECOND,
    HATCH_LOW,
    HATCH_MID,
    HATCH_HIGH,
    HATCH_LOW_SECOND,
    HATCH_MID_SECOND,
    HATCH_HIGH_SECOND,
    MAX_HATCH_POS
  };

  enum CARGO_ARM_PRESETS
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

  double OurDegreesToRads(double degrees);
  void CorrectExtenderPower(double &power, bool climbMode);
  double Map(double x, double in_min, double in_max, double out_min, double out_max);
                                            //0,  1,    2,      3,     4,      5,      6,       7, 8
  double hatchAngle[MAX_HATCH_POS] =        { 0, -140, -85.77, -148.1, -83.33, -23.76, -120.30, 0, 0 };
  double cargoAngle[MAX_CARGO_POS] =        { 0, -110.6, -94.13, -64.7, -99.5, -50.73 -13.75 };

  //practice bot
  // double extenderHatchInches[MAX_HATCH_POS] = { 0, 6.8, 0, 0.925, 0, 0 };
  // double extenderCargoInches[MAX_CARGO_POS] = { 0, 0.0, 0, 0, 0, 0, 6.8 };

  // comp bot                                   0, 1,     2,    3,    4, 5, 6, 7, 8
  double extenderHatchInches[MAX_HATCH_POS] = { 0, 7.625, 6.55, 1.75, 0, 0, 0, 0, 0 };
  double extenderCargoInches[MAX_CARGO_POS] = { 0, 0, 0, 0, 0, 0, 7.625 };

  double m_armTargetAngle;
  double m_previousArmRealAngle;
  double m_extenderTargetRotations;

  // legal match starting configuration
  double m_armLegalStartingAngle;
  double m_extenderLegalStartingInches;
  
  // starting config for testing; intake flush with floor
  double m_armTestStartingAngle;
  double m_extenderTestStartingInches;

  double m_extenderMinDistance; // i wish i could make these const :///
  double m_extenderMaxDistance;
  
  DragonTalon* m_armMaster;
  DragonTalon* m_extender;

  const double EXTENDER_HOLD_POWER = -0.1;
};

// const double INCHES_PER_REVOLUTION = 8 / 6.7578125;
// const double INCHES_PER_REVOLUTION = 8 / 6.3578125;
  // const double INCHES_PER_REVOLUTION = 1.0;
// const double INCHES_PER_REVOLUTION = 8 / 8.849609375;


// const double INCHES_PER_REVOLUTION = 7.625 / 9.28515625; //big ol' todo here. fix where it crashes when builds