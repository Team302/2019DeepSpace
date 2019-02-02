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

class DriverAssist
{
public:
    void Update(); // runs everything lol

    DriverAssist();
    ~DriverAssist() = default;

private:
    void GoToPosition(PlacementHeights::PLACEMENT_HEIGHT placementHeight);
    void GoToTarget();

    Switcher* m_switcher;

    bool m_goingToPosition;
    bool m_goingToTarget;
    bool m_deploy;


};