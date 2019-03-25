/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsys/Arm.h"
#include "subsys/Wrist.h"
#include "subsys/Intake.h"
#include "subsys/HatchMechanism.h"
#include "subsys/MechanismFactory.h"

class IntakeGamePiece {
 public:
  enum INTAKE_STATE
  {
    INTAKE_SECOND_MECH,
    MOVING_ARM_AND_INTAKE_CARGO,
    INTAKE_CARGO,
    MOVING_ARM_AND_INTAKE_HATCH,
    INTAKE_HATCH,
    DONE
  };

  IntakeGamePiece();
  ~IntakeGamePiece() {};

  void Update();
  bool IsDone();
  void Cancel();
  void IntakeGameObject(bool cargo, bool flip, bool secondMech);

private:
    Arm* m_arm;
    Wrist* m_wrist;
    Intake* m_intake;
    HatchMechanism* m_hatchMech;

    bool m_cargo;
    bool m_flip;

    double m_elapsedTime;

    double m_armInitialAngle;
    double m_armAngleOffset;
    INTAKE_STATE m_state;

    const double ARM_ANGLE_CARGO_DELTA = -15;
    const double ARM_ANGLE_HATCH_DELTA = -8;
    const double ARM_INTAKE_THRESH = 5;

    const double CARGO_INTAKE_TIME = 0.25;
    const double HATCH_INTAKE_TIME = 0.25;
    const double HATCH_SECOND_MECH_TIME = 0.35;
    const double HATCH_SECOND_MECH_HOLD_POWER = 0.15;

    const double DONE_ARM_THRESH = 5;

    const double CARGO_INTAKE_SPEED = 1.0;
    const double HATCH_INTAKE_SPEED = -1.0;
};
