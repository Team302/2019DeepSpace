/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "teleop/Switcher.h"

//TODO: xml baby
Switcher::Switcher() :
m_arm( new Arm(std::vector<IDragonMotorController*>()) ),
m_intake( new Intake(std::vector<IDragonMotorController*>()) ),
m_wrist( new Wrist(std::vector<IDragonMotorController*>()) ),
m_chassis( new DragonChassis(std::vector<IDragonMotorController*>(), 6.0) ),
m_climber( new Climber(std::vector<IDragonMotorController*>(), std::vector<DragonServo*>()) )
{
}

void Switcher::DriveUpdate()
{
    //TODO:
    // try smoothing only the forward backward value instead of both forward backward and turning
    // this might give extra control 
    // also try voltage ramping
    m_chassis->UpdateChassis();
    m_chassis->SetDriveMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);

    double forwardSpeed = TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROBOT_Y_MAGNITUDE );
    double turnSpeed = TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROBOT_X_MAGNITUDE );

    double leftSpeed = forwardSpeed + turnSpeed;
    double rightSpeed = forwardSpeed - turnSpeed;

    // scale drive magnetudes into -1 to 1 range
    double maxValue = 1.0;
    if (std::abs(leftSpeed) > maxValue)
    {
        maxValue = std::abs(leftSpeed);
    }
    if (std::abs(rightSpeed) > maxValue)
    {
        maxValue = std::abs(rightSpeed);
    }

    leftSpeed /= maxValue;
    rightSpeed /= maxValue;

    m_chassis->SetLeftRightMagnitudes(leftSpeed, rightSpeed);
}

void Switcher::GamepieceUpdate()
{
    double armSpeed = std::pow(-TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROTATE_ARM), 3) * 3.0;
    m_armTargetPosition += armSpeed;
    m_extendSpeed = TeleopControl::GetInstance()->GetAxisValue( TeleopControl::EXTEND_ARM );
    m_wristSpeed = -TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROTATE_WRIST );
    m_intakeSpeed = TeleopControl::GetInstance()->GetAxisValue( TeleopControl::INTAKE ) - TeleopControl::GetInstance()->GetAxisValue( TeleopControl::OUTAKE );

    m_intake->IntakeManual( m_intakeSpeed );
    m_wrist->MoveWristManualSpeed( m_wristSpeed );
    m_arm->MoveExtensionSpeed( m_extendSpeed );
    m_arm->MoveArmAngle( m_armTargetPosition );
}

void Switcher::ClimberUpdate()
{
    if (TeleopControl::GetInstance()->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::CLIMB_ELEVATOR_UP))
        m_climbElevSpeed = ELEV_SPEED;
    else if (TeleopControl::GetInstance()->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::CLIMB_ELEVATOR_DOWN))
        m_climbElevSpeed = -ELEV_SPEED;
    else
        m_climbElevSpeed = 0.0;

    m_climbDriveSpeed = TeleopControl::GetInstance()->GetAxisValue( TeleopControl::FUNCTION_IDENTIFIER::CLIMB_DRIVE );
    m_allowClimbDrive = TeleopControl::GetInstance()->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::ALLOW_CLIMB_DRIVE );
    m_dropBuddyClimb = TeleopControl::GetInstance()->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::DROP_BUDDY_CLIMB );

    if(m_allowClimbDrive)
        m_climber->SetClimbDriveSpeed(m_climbDriveSpeed);
    else
        m_climber->SetClimbDriveSpeed(0.0);

    
    m_climber->MoveClimbElevator(m_climbElevSpeed);
    m_climber->DropBuddyClimb(m_dropBuddyClimb);
}