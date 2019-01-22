/*
/*   Created by Austin Szczesniak
/*   Date: 1-19-2019
*/

#include "subsys/Wrist.h"

Wrist::Wrist() :
    m_wristMotor(new DragonTalon(DragonTalon::TALON_TYPE::WRIST, 5, 0, 0)) // TODO: make this xml
{}

// TODO: Add a painting motion?

void Wrist::MoveWristManual(double speed)
{
    m_wristMotor->SetControlMode(DragonTalon::TALON_CONTROL_MODE::PERCENT);
}

void Wrist::MoveWristPresets(Wrist::PLACEMENT_HEIGHT height, bool cargo, bool flip)
{
    m_wristMotor->SetControlMode(DragonTalon::TALON_CONTROL_MODE::POSITION);
    double targetAngle = GetWristAngle();
    if(cargo)
    {   
        switch(height)
        {
            case Wrist::PLACEMENT_HEIGHT::FLOOR:
                targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_FLOOR];
                break;
            case Wrist::PLACEMENT_HEIGHT::CARGOSHIP:
                targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_SHIP];
                break;
            case Wrist::PLACEMENT_HEIGHT::HUMAN_PLAYER:
                targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_HP];
                break;
            case Wrist::PLACEMENT_HEIGHT::ROCKET_LOW:
                targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_LOW];
                break;
            case Wrist::PLACEMENT_HEIGHT::ROCKET_MID:
                targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_MID];
                break;
            case Wrist::PLACEMENT_HEIGHT::ROCKET_HIGH:
                targetAngle = cargoAngle[Wrist::CARGO_WRIST_PRESETS::CARGO_HIGH];
                break;
            default:
                targetAngle = GetWristAngle();
        }
    }
    else
    {
        switch(height)
        {
            case Wrist::PLACEMENT_HEIGHT::FLOOR:
                targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_FLOOR];
                break;
            case Wrist::PLACEMENT_HEIGHT::CARGOSHIP:
                targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_LOW];
                break;
            case Wrist::PLACEMENT_HEIGHT::HUMAN_PLAYER:
                targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_LOW];
                break;
            case Wrist::PLACEMENT_HEIGHT::ROCKET_LOW:
                targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_LOW];
                break;
            case Wrist::PLACEMENT_HEIGHT::ROCKET_MID:
                targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_MID];
                break;
            case Wrist::PLACEMENT_HEIGHT::ROCKET_HIGH:
                targetAngle = hatchAngle[Wrist::HATCH_WRIST_PRESETS::HATCH_HIGH];
                break;
            default:
                targetAngle = GetWristAngle();
        }
    }

    if(flip)
        targetAngle = -targetAngle;

    m_wristMotor->Set(targetAngle / 360); // Sets in rotations from degrees
}

/*
* Returns current wrist angle
*/
double Wrist::GetWristAngle()
{
    return m_wristMotor->GetRotations() * 360;
}