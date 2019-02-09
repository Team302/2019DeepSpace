/*
 * DriverAssist.cpp
 *
 *  Created on: Jan 25, 2019
 *      Author: Jonah Shader
 */

#include "driverassist/DriverAssist.h"

DriverAssist::DriverAssist() :
    m_switcher(new Switcher()),
    m_goingToPosition(false),
    m_goingToTarget(false),
    m_deploy(false)
{
}

// The update method runs every periodic process of this class
void DriverAssist::Update()
{
    
    // ask switcher if drivers are trying to move
    // if they are, cancel any overlapping driverassist processes
    // TODO: add these into switcher
    // they should have a high tolerance so that there aren't accidental
    // joystick movements that could cancel the processes
    // after we determine what we can run, run them below

    // go to target
    if (m_goingToTarget)
    {
        // run ApproachTarget until we are at the target,
        // then set m_goingToTarget to false
    }
    if (m_goingToPosition)
    {
        // if the arm is done moving to position,
        // move extender to position

        // if extender is to position,
        // done going to position
    }
    else if (m_deploy) // we can only deploy when we aren't going to the preset position
    {
        // deploy
        // set m_deploy to false when done deploying
    }

    // allow driver control when not running overlapping processes
    if (!m_goingToTarget)
    {
        m_switcher->DriveUpdate();
    }

    if (!m_deploy && !m_goingToPosition)
    {
        m_switcher->GamepieceUpdate();
        //m_switcher->ClimberUpdate();
    }
}

void DriverAssist::GoToPosition(PlacementHeights::PLACEMENT_HEIGHT placementHeight)
{
    // set arm to position
    // set wrist to position

    // stop intake??
    m_goingToPosition = true;
}

void DriverAssist::GoToTarget()
{
    // m_goingToTarget;
}