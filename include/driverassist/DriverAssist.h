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

#include "subsys/PlacementHeights.h"
#include "teleop/Switcher.h"
#include "driverassist/MoveArmToPosition.h"
#include "driverassist/DeployGamePiece.h"

class DriverAssist
{
public:
    void Update(); // runs everything lol

    DriverAssist();
    ~DriverAssist() = default;

private:

    //Litter Helper Method
    void GetDesiredHeight();
    void AttemptingGamePieceCancel();
    void AttemptingDriveCancel();

    Switcher* m_switcher;
    MoveArmToPosition* m_MoveArmToPos;
    DeployGamePiece* m_deployGamePiece;

    // queues
    bool m_deploy;
    bool m_climbMode;

    // helper Bools
    bool m_cargo;
    bool m_flip;
    PlacementHeights::PLACEMENT_HEIGHT m_height;
};