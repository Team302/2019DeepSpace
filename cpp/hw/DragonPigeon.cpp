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
) : PigeonIMU( canID ),
    m_pigeon(new ctre::phoenix::sensors::PigeonIMU(canID))
{
    DragonPigeon::m_instance = this;
}

double DragonPigeon::GetPitch()
{
    double ypr[3];
    m_pigeon->GetYawPitchRoll(ypr);

    return ypr[1]; // yaw = 0 pitch = 1 roll = 2 
}
double DragonPigeon::GetRoll()
{
    double ypr[3];
    m_pigeon->GetYawPitchRoll(ypr);

    return ypr[2]; // yaw = 0 pitch = 1 roll = 2 
}
double DragonPigeon::GetYaw()
{
    double ypr[3];
    m_pigeon->GetYawPitchRoll(ypr);

    return ypr[0]; // yaw = 0 pitch = 1 roll = 2 
}

