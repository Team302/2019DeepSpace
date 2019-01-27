/*
 * DriverAssist.cpp
 *
 *  Created on: Jan 25, 2019
 *      Author: Jonah Shader
 */

#include "driverassist/DriverAssist.h"

// make the class instance variable nullptr initially
DriverAssist* DriverAssist::m_driverAssist = nullptr;

DriverAssist* DriverAssist::GetDriverAssist()
{
    if (DriverAssist::m_driverAssist == nullptr)
    {
        DriverAssist::m_driverAssist = new DriverAssist();
    }
    return DriverAssist::m_driverAssist;
}

// The update method runs every periodic process of this class
void DriverAssist::Update()
{

}

void DriverAssist::GoToPosition(PlacementHeights::PLACEMENT_HEIGHT placementHeight)
{
    // set arm to position
    // set wrist to position

    // stop intake??
}