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

class DriverAssist
{
public:
    static DriverAssist* GetDriverAssist();  // singleton class get method
    void Update(); // runs everything lol

    ~DriverAssist() = default;

private:
    enum DriverAssistMode
    {
        APPROACH_TARGET,
        DEPLOY
    };

    DriverAssist() {}; // empty constructor

    void GoToPosition(PlacementHeights::PLACEMENT_HEIGHT placementHeight);

    static DriverAssist* m_driverAssist;
};