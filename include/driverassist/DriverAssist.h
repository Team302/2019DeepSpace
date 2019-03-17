/*
 * DriverAssist.h
 *
 *  Created on: Jan 25, 2019
 *      Author: jonah
 */

/*
Singleton class
Driver assist contains all sub driver assist thingys and allocates teleop control
*/

#pragma once

#include "subsys/chassis/DragonChassis.h"
#include "subsys/PlacementHeights.h"
#include "teleop/Switcher.h"
#include "driverassist/MoveArmToPosition.h"
#include "driverassist/DeployGamePiece.h"
#include "driverassist/IntakeGamePiece.h"
#include "driverassist/HoldDrivePosition.h"
#include "driverassist/TargetAllign.h"
#include "driverassist/DriveToTarget.h"
#include "driverassist/Climb.h"

class DriverAssist
{
public:
    void Update(); // runs everything lol

    DriverAssist();
    ~DriverAssist() = default;

private:

    //Litter Helper Method
    void UpdateSecondaryControls();
    void UpdateDriverControls();
    void AttemptingGamePieceCancel();
    void AttemptingDriveCancel();

    DragonChassis* m_chassis;
    Switcher* m_switcher;
    MoveArmToPosition* m_MoveArmToPos;
    DeployGamePiece* m_deployGamePiece;
    IntakeGamePiece* m_intakeGamePiece;
    HoldDrivePosition* m_holdDrivePositon;
    TargetAllign* m_targetAllign;
    DriveToTarget* m_driveToTarget;
    Climb* m_climb;

    // some bools
    bool m_deploy;
    bool m_intake;
    bool m_climbMode;
    bool m_holdMode;
    bool m_visionMode;
    bool m_wristForcePercentOutput;
    bool m_pMainControllerTriggerLeftHand; // previous bool values for triggers
    bool m_pMainControllerTriggerRightHand;

    // helper Bools
    bool m_cargo;
    bool m_flip;
    PlacementHeights::PLACEMENT_HEIGHT m_height;
    bool m_second;

    // Driver things
    const double HOLD_MODE_MAX_INCHES_PER_SECOND_TURNING = 5.0;
    const double HOLD_MODE_MAX_INCHES_PER_SECOND_FORWARD = 24.0;

    bool TriggerPressed(double value);
};