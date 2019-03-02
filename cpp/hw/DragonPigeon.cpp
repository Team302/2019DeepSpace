/*
 * DragonPigeon.cpp
 *
 *  Created on: Feb 3, 2018
 *      Author: team302
 */

#include <ctre/phoenix/Sensors/PigeonIMU.h>
#include <hw/DragonPigeon.h>
#include <iostream>
#include <frc/SmartDashboard/SmartDashboard.h>

using namespace frc;

using namespace ctre;
using namespace phoenix;
using namespace motorcontrol;
using namespace can;

DragonPigeon* DragonPigeon::m_instance = nullptr;
DragonPigeon* DragonPigeon::GetPigeon()
{
    return DragonPigeon::m_instance;
}

DragonPigeon::DragonPigeon
(
    int  canID
) : PigeonIMU( canID )
{
    DragonPigeon::m_instance = this;
}

