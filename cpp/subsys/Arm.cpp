#include "subsys/Arm.h"
#include "subsys/PlacementHeights.h"
#include "hw/DragonTalon.h"
#include "ctre/Phoenix.h"
#include "frc/smartdashboard/SmartDashboard.h"
Arm::Arm() 
{
    m_leftArmRotationMotor = new DragonTalon(IDragonMotorController::TALON_TYPE::ARM_LEFT, 2, 4096, 60); //need to change gear ratio
    m_rightArmRotationMotor = new DragonTalon(IDragonMotorController::TALON_TYPE::ARM_RIGHT, 13, 4096, 60); //need to change gear ratio and counts per rev
    m_armExtensionMotor = new DragonTalon(IDragonMotorController::TALON_TYPE::ARM_EXTENSION, 8, 4096, 60); //need to change gear ratio
    m_canifier1 = new CANifier(1); //need to change device ID
    m_canifier2 = new CANifier(55); //need to change device ID

    m_leftArmRotationMotor->SetInverted(false);
    m_rightArmRotationMotor->SetInverted(true);
    m_armExtensionMotor->SetInverted(false);

    m_leftArmRotationMotor->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
    //m_rightArmRotationMotor->ConfigSelectedFeedbackSensor(DragonTalon::TALON_SENSOR_TYPE::UNKNOWN_SENSOR, 0, 0); //need to change sensor type
    m_armExtensionMotor->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);

    //m_leftArmRotationMotor->ConfigMotionCruiseVelocity(ROTATION_ARM_MAX_CRUISE_VELOCITY);
    //m_rightArmRotationMotor->ConfigMotionCruiseVelocity(ROTATION_ARM_MAX_CRUISE_VELOCITY);
    //m_armExtensionMotor->ConfigMotionCruiseVelocity(EXTENSION_MAX_CRUISE_VELOCITY);

    //m_leftArmRotationMotor->ConfigMotionAcceleration(ROTATION_ARM_MAX_ACCELERATION);
    //m_rightArmRotationMotor->ConfigMotionAcceleration(ROTATION_ARM_MAX_ACCELERATION);
    //m_armExtensionMotor->ConfigMotionAcceleration(EXTENSION_MAX_ACCELERATION);

    m_leftArmRotationMotor->ConfigPeakOutput(1.0);
    m_rightArmRotationMotor->ConfigPeakOutput(1.0);
    //m_armExtensionMotor->ConfigPeakOutput(1.0);

    m_leftArmRotationMotor->ConfigNominalOutput(0.0);
    m_rightArmRotationMotor->ConfigNominalOutput(0.0);
    //m_armExtensionMotor->ConfigNominalOutput(0.0);

    m_leftArmRotationMotor->SetPIDF(ARM_P,ARM_I,ARM_D,ARM_F);
    m_rightArmRotationMotor->SetPIDF(ARM_P,ARM_I,ARM_D,ARM_F);
    //m_armExtensionMotor->SetPIDF(EXTEND_P,EXTEND_I,EXTEND_D,EXTEND_F);

    m_startPosition = GetArmRotations();
    m_rotationForwardMax = m_startPosition + MAX_ARM_ROTATION_FORWARD;
    m_rotationReverseMax = m_startPosition + MAX_ARM_ROTATION_REVERSE;

    m_leftArmRotationMotor->SetControlMode(DragonTalon::TALON_CONTROL_MODE::PERCENT);
    m_rightArmRotationMotor->SetControlMode(DragonTalon::TALON_CONTROL_MODE::PERCENT);

    
}

Arm::~Arm()
{
    
}

void Arm::RotateArmJoystick(double joystickVal)
{
    double power = joystickVal * JOYSTICK_ROTATION_ARM_CONSTANT;
    
    RotateArmPercentOutput(power);
}

void Arm::ExtendArmJoystick(double joystickVal)
{
    double power = joystickVal * JOYSTICK_EXTENSION_CONSTANT;

    ExtendArmPercentOutput(power);
}
void Arm::MoveArmToPosition(PlacementHeights::PLACEMENT_HEIGHT armHeight, bool cargo)
{
   if(cargo)
   {
        switch(armHeight)
        {
            case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
            RotateArmToPosition(CARGO_POSITIONS[PlacementHeights::PLACEMENT_HEIGHT::FLOOR]);
            break;

            case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
            RotateArmToPosition(CARGO_POSITIONS[PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER]);
            break;

            case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
            RotateArmToPosition(CARGO_POSITIONS[PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP]);
            break;

            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
            RotateArmToPosition(CARGO_POSITIONS[PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW]);
            break;

            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
            RotateArmToPosition(CARGO_POSITIONS[PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID]);
            break;

            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
            RotateArmToPosition(CARGO_POSITIONS[PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH]);
            break;

            case PlacementHeights::PLACEMENT_HEIGHT::MAX_PLACEMENT_HEIGHTS:
            RotateArmToPosition(CARGO_POSITIONS[PlacementHeights::PLACEMENT_HEIGHT::MAX_PLACEMENT_HEIGHTS]);
            break;
            
        }
    }
    else
    {
        switch(armHeight)
        {
            case PlacementHeights::PLACEMENT_HEIGHT::FLOOR:
            RotateArmToPosition(HATCH_POSITIONS[PlacementHeights::PLACEMENT_HEIGHT::FLOOR]);
            break;
            
            case PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER:
            case PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP:
            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW:
            RotateArmToPosition(HATCH_POSITIONS[PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER]);
            break;

            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID:
            RotateArmToPosition(HATCH_POSITIONS[PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID]);
            break;

            case PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH:
            RotateArmToPosition(HATCH_POSITIONS[PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH]);
            break;

            case PlacementHeights::PLACEMENT_HEIGHT::MAX_PLACEMENT_HEIGHTS:
            RotateArmToPosition(HATCH_POSITIONS[PlacementHeights::PLACEMENT_HEIGHT::MAX_PLACEMENT_HEIGHTS]);
            break;
        }
    }
   
}
bool Arm::IsOverRotated()
{
    bool overRotated = false;
    double currentRotation = GetArmRotations();
    if(currentRotation > m_rotationForwardMax || currentRotation < m_rotationReverseMax)
    {
        overRotated = true;
    }
    else
    {
        overRotated = false;
    }

    frc::SmartDashboard::PutBoolean("Is arm overrotated", overRotated);
    return overRotated;
}
void Arm::RotateArmPercentOutput(double armPower)
{
    /*if(!IsOverRotated())
    {
        m_leftArmRotationMotor->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
        m_rightArmRotationMotor->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
        m_leftArmRotationMotor->Set(armPower);
        m_rightArmRotationMotor->Set(armPower);
    }
    else
    {
        //returns to position within range of motion
        //RotateArmToPosition()
        
    } 
    */
    m_leftArmRotationMotor->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
    m_rightArmRotationMotor->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
    m_leftArmRotationMotor->Set(armPower);
    m_rightArmRotationMotor->Set(armPower);
    
}
void Arm::RotateArmToPosition(double position)
{
    m_leftArmRotationMotor->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::ROTATIONS);
    m_rightArmRotationMotor->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::ROTATIONS);
    m_leftArmRotationMotor->Set(position);
    m_rightArmRotationMotor->Set(position);
}
void Arm::ExtendArmPercentOutput(double extendArmPower)
{
    m_armExtensionMotor->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);

    m_armExtensionMotor->Set(extendArmPower);
}

void Arm::ExtendArmPosition(double position)
{
    m_armExtensionMotor->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::ROTATIONS);

    m_armExtensionMotor->Set(position);
}

bool Arm::GetTalonTach(Arm::TALON_TACH talonTach)
{
    switch(talonTach)
    {
        case TALON_TACH::LOW_FRONT_TACH:
        return m_canifier1->GetGeneralInput(ctre::phoenix::CANifier::GeneralPin::QUAD_A);
        break;

        case TALON_TACH::HIGH_FRONT_TACH:
        return m_canifier1->GetGeneralInput(ctre::phoenix::CANifier::GeneralPin::LIMR);
        break;

        case TALON_TACH::LOW_REAR_TACH:
        return m_canifier2->GetGeneralInput(ctre::phoenix::CANifier::GeneralPin::QUAD_A);
        break;

        case TALON_TACH::HIGH_REAR_TACH:
        return m_canifier1->GetGeneralInput(ctre::phoenix::CANifier::GeneralPin::LIMF);
        break;

        default:
        return -1;
    }
}

double Arm::GetArmRotations()
{
    double currentRotation = m_leftArmRotationMotor->GetRotations();
    frc::SmartDashboard::PutNumber("Arm Rotation", currentRotation);
    return currentRotation;
}

//returns in rotations per second
double Arm::GetArmVelocity() 
{
    return m_leftArmRotationMotor->GetRPS();
}