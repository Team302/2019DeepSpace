/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "teleop/Switcher.h"
#include "subsys/MechanismFactory.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <subsys/IMechanism.h>

//TODO: xml baby
Switcher::Switcher() :
m_arm( MechanismFactory::GetMechanismFactory()->GetArm() ),
m_intake( MechanismFactory::GetMechanismFactory()->GetIntake() ),
m_wrist( MechanismFactory::GetMechanismFactory()->GetWrist() ),
m_chassis( DragonChassis::GetInstance() ),
m_climber( MechanismFactory::GetMechanismFactory()->GetClimber() ),
m_mainController( new frc::XboxController(0) ),
m_secondaryController( new frc::XboxController(1) )
{
    m_armTargetPosition = m_arm->GetArmRealAngle();
    m_wristTargetPosition = m_wrist->GetWristAngle();
}

void Switcher::DriveUpdate()
{
    //TODO:
    // try smoothing only the forward backward value instead of both forward backward and turning
    // this might give extra control 
    // also try voltage ramping
    m_chassis->UpdateChassis();
    m_chassis->SetDriveMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);

    // double forwardSpeed = TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROBOT_Y_MAGNITUDE );
    double forwardSpeed = std::pow(m_mainController->GetRawAxis(1), 3);
    if(std::abs(forwardSpeed) < 0.001)
        forwardSpeed = 0.0;

    // double turnSpeed = TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROBOT_X_MAGNITUDE );
    double turnSpeed = std::pow(-m_mainController->GetRawAxis(4), 3);
    if(std::abs(turnSpeed) < 0.001)
        turnSpeed = 0.0;

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

    // printf("forward Speed: %f \n", forwardSpeed);
    // printf("turning speed: %f \n", turnSpeed);

    m_chassis->SetLeftRightMagnitudes(leftSpeed, rightSpeed);
}

void Switcher::GamepieceUpdate()
{
    // double armSpeed = std::pow(-TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROTATE_ARM), 3) * 3.0;
    double armSpeed = std::pow(-m_secondaryController->GetRawAxis(1), 3) * 1.0;
    if(std::abs(armSpeed) < 0.001)
        armSpeed = 0;
    m_armTargetPosition += armSpeed;
    // m_extendSpeed = TeleopControl::GetInstance()->GetAxisValue( TeleopControl::EXTEND_ARM );
    m_extendSpeed = std::pow(m_secondaryController->GetRawAxis(0), 3);
    // m_wristSpeed = -TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROTATE_WRIST );
    // m_wristSpeed = m_secondaryController->GetRawAxis(5);
    double wristSpeed = std::pow(-m_secondaryController->GetRawAxis(5), 3) * 3;
    // wristSpeed = std::abs(wristSpeed) > 0.1 ? wristSpeed * 1.0 : 0.0;
    m_wristTargetPosition += wristSpeed;
    // m_intakeSpeed = TeleopControl::GetInstance()->GetAxisValue( TeleopControl::INTAKE ) - TeleopControl::GetInstance()->GetAxisValue( TeleopControl::OUTAKE );
    m_intakeSpeed = m_secondaryController->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand) - m_secondaryController->GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand);

    m_extendSpeed -= 0.171;

    m_intake->IntakeManual( m_intakeSpeed );
    // m_wrist->MoveWristManualSpeed( 0.0 );
    m_wrist->MoveWristManualAngle(m_wristTargetPosition);
    m_arm->MoveExtensionSpeed( m_extendSpeed );
    m_arm->MoveArmAngle( m_armTargetPosition );

    frc::SmartDashboard::PutNumber("Wrist Real Angle", m_wrist->GetWristAngle());

    // frc::SmartDashboard::PutNumber("Arm Target Angle", m_armTargetPosition);
    // frc::SmartDashboard::PutNumber("Arm Real Angle", m_arm->GetArmRealAngle());
    // frc::SmartDashboard::PutNumber("Arm Speed", armSpeed);
    // m_arm->MoveArmSpeed(armSpeed);
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