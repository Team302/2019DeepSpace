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
#include <cmath>

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
    m_initialRoll = GetRawRoll();
    m_initialPitch = GetRawPitch();
    m_initialYaw = GetRawYaw();
}

void DragonPigeon::CreatePigeon(int id)
{
    DragonPigeon::m_instance = new DragonPigeon(id);
}

double DragonPigeon::GetPitch()
{
    return GetRawPitch() - m_initialPitch;
}

double DragonPigeon::GetRoll()
{
    return GetRawRoll() - m_initialRoll;
}

double DragonPigeon::GetYaw()
{
    return GetRawYaw() - m_initialYaw;
}

double DragonPigeon::GetRawPitch()
{
    double ypr[3];
    m_pigeon->GetYawPitchRoll(ypr);

    // return ypr[1]; // yaw = 0 pitch = 1 roll = 2 
    return ypr[2];
}

double DragonPigeon::GetRawRoll()
{
    double ypr[3];
    m_pigeon->GetYawPitchRoll(ypr);

    // return ypr[2]; // yaw = 0 pitch = 1 roll = 2 
    return ypr[1];
}

double DragonPigeon::GetRawYaw()
{
    double ypr[3];
    m_pigeon->GetYawPitchRoll(ypr);

    return ypr[0]; // yaw = 0 pitch = 1 roll = 2 
}

