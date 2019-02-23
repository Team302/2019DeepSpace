/*
/*   Created by Austin Szczesniak
/*   Date: 1-19-2019
*/

#include "subsys/Wrist.h"
#include <subsys/IMechanism.h>
#include <xmlhw/PIDData.h>

Wrist::Wrist(std::vector<IDragonMotorController*> motorControllers) :
    m_wristMotor(nullptr)
{
    for (int i = 0; i < motorControllers.size(); i++)
    {
        switch (motorControllers[i]->GetType())
        {
            case IDragonMotorController::TALON_TYPE::WRIST:
                m_wristMotor = static_cast<DragonTalon*>(motorControllers[i]);
            break;

            default:
            break;
        }
    }

    m_targetAngle = m_wristMotor->GetRotations() * 360.0;
}


void Wrist::MoveWristManualSpeed(double speed)
{
    m_wristMotor->SetControlMode(DragonTalon::TALON_CONTROL_MODE::PERCENT);
    m_wristMotor->Set(speed);
}

void Wrist::MoveWristManualAngle(double angle)
{
    m_wristMotor->SetControlMode(DragonTalon::TALON_CONTROL_MODE::POSITION);
    m_wristMotor->Set(angle / 360);
    m_targetAngle = angle;
}

void Wrist::MoveWristPresets(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo, bool flip)
{
    m_wristMotor->SetControlMode(DragonTalon::TALON_CONTROL_MODE::POSITION);
    if(cargo)
    {
        switch(height)
        {
            case PlacementHeights::PLACEMENT_HEIGHT::START_POSITION:
                m_targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_START_POSITION];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
                m_targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_FLOOR];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
                m_targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_SHIP];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
                m_targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_HP];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
                m_targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
                m_targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_MID];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
                m_targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_HIGH];
                break;
            default:
                break;
        }
    }
    else
    {
        switch(height)
        {
            case PlacementHeights::PLACEMENT_HEIGHT::START_POSITION:
                m_targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_START_POSITION];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
                m_targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_FLOOR];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
                m_targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
                m_targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_HP];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
                m_targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
                m_targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_MID];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
                m_targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_HIGH];
                break;
            default:
                break;
        }
    }

    if(flip)
        m_targetAngle = -m_targetAngle;

    m_wristMotor->SetControlMode(DragonTalon::TALON_CONTROL_MODE::MOTION_MAGIC);
    m_wristMotor->Set(m_targetAngle / 360.0); // Sets in rotations from degrees
}

void Wrist::MoveWristMotionMagic(double angle)
{
    m_targetAngle = angle;
    m_wristMotor->SetControlMode(DragonTalon::TALON_CONTROL_MODE::MOTION_MAGIC);
    m_wristMotor->Set(angle / 360);
}

void Wrist::ResetTarget()
{
    m_targetAngle = GetWristRealAngle();
}

/*
* Returns current wrist angle
*/
double Wrist::GetWristRealAngle()
{
    return m_wristMotor->GetRotations() * 360;
}

double Wrist::GetWristTargetAngle()
{
    return m_targetAngle;
}

IMechanism::MECHANISM_TYPE Wrist::GetType() const
{
    return IMechanism::MECHANISM_TYPE::WRIST;
}
void Wrist::SetParam
(
    IMechanism::MECHANISM_PARAM_TYPE    param,          // <I> - parameter to set
    double                              value           // <I> - parameter value
) 
{
    // TODO:  Override values
    switch(param)
    {
        case WRIST_ANGLE_OFFSET:
         
        break;

        case HATCH_LOW_ANGLE:
        hatchAngle[HATCH_LOW] = value;
        break;

        case HATCH_HP_ANGLE:
        hatchAngle[HATCH_FLOOR] = value;
        break;

        case HATCH_MID_ANGLE:
        hatchAngle[HATCH_MID] = value;
        break;

        case HATCH_HIGH_ANGLE:
        hatchAngle[HATCH_HIGH] = value;
        break;

        case CARGO_FLOOR_ANGLE:
        cargoAngle[CARGO_FLOOR] = value;
        break;

        case CARGO_HP_ANGLE:
        cargoAngle[CARGO_HP] = value;
        break;

        case CARGO_SHIP_ANGLE:
        cargoAngle[CARGO_SHIP] = value; 
        break;

        case CARGO_LOW_ANGLE:
        cargoAngle[CARGO_LOW] = value;
        break;

        case CARGO_MID_ANGLE:
        cargoAngle[CARGO_MID] = value;
        break;
        
        case CARGO_HIGH_ANGLE:
        cargoAngle[CARGO_HIGH] = value;
        break;

        default:
        printf(" Wrist.cpp is getting a value it shouldn't. Line 125 \n");
        break; 
    }
}
void Wrist::SetPID
(
    PIDData*        pid                 // <I> - PID control information
) 
{
    // TODO:  Override values
}




