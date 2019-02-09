/*
/*   Created by Austin Szczesniak
/*   Date: 1-19-2019
*/

#include "subsys/Wrist.h"

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
}

// TODO: Add a painting motion?

void Wrist::MoveWristManualSpeed(double speed)
{
    m_wristMotor->SetControlMode(DragonTalon::TALON_CONTROL_MODE::PERCENT);
    m_wristMotor->Set(speed);
}

void Wrist::MoveWristManualAngle(double angle)
{
    m_wristMotor->SetControlMode(DragonTalon::TALON_CONTROL_MODE::POSITION);
    m_wristMotor->Set(angle / 360);
}

void Wrist::MoveWristPresets(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo, bool flip)
{
    m_wristMotor->SetControlMode(DragonTalon::TALON_CONTROL_MODE::POSITION);
    double targetAngle = GetWristAngle();
    if(cargo)
    {
        switch(height)
        {
            case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
                targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_FLOOR];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
                targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_SHIP];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
                targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_HP];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
                targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
                targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_MID];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
                targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_HIGH];
                break;
            default:
                targetAngle = GetWristAngle();
                break;
        }
    }
    else
    {
        switch(height)
        {
            case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
                targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_FLOOR];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
                targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
                targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
                targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_LOW];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
                targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_MID];
                break;
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
                targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_HIGH];
                break;
            default:
                targetAngle = GetWristAngle();
                break;
        }
    }

    if(flip)
        targetAngle = -targetAngle;

    m_wristMotor->Set(targetAngle / 360.0); // Sets in rotations from degrees
}

/*
* Returns current wrist angle
*/
double Wrist::GetWristAngle()
{
    return m_wristMotor->GetRotations() * 360;
}

IMechanism::MECHANISM_TYPE Wrist::GetType() const
{
    return IMechanism::MECHANISM_TYPE::WRIST;
}