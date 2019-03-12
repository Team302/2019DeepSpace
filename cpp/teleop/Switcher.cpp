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
#include <subsys/vision/DragonLimelight.h>

//TODO: xml baby
Switcher::Switcher() :
			m_arm( MechanismFactory::GetMechanismFactory()->GetArm() ),
			m_intake( MechanismFactory::GetMechanismFactory()->GetIntake() ),
			m_wrist( MechanismFactory::GetMechanismFactory()->GetWrist() ),
			m_chassis( DragonChassis::GetInstance() ),                     
            m_climber( MechanismFactory::GetMechanismFactory()->GetClimber() ),
            m_limelight(DragonLimelight::GetInstance()),
            m_allowClimbDrive(false),
			m_mainController( new frc::XboxController(0) ),
            m_secondaryController(new frc::XboxController(1)),
           	m_holdMode(false),
            m_leftTargetInches(0),
            m_rightTargetInches(0)
{
    m_visionMode = false;
    m_camMode = false;
}

void Switcher::DriveUpdate()
{
    // Hold to allow drive elevator motor
    if(m_mainController->GetAButtonPressed())
        m_allowClimbDrive = true;
    if (m_mainController->GetAButtonReleased())
        m_allowClimbDrive = false;

    // if (m_mainController->GetPOV() == 0)
    // {
    //     m_chassis->EnableBrakeMode(true);
    // }
    // else if (m_mainController->GetPOV() == 180)
    // {
    //     m_chassis->EnableBrakeMode(false);
    // }

    
    if(m_mainController->GetBButtonPressed())
        m_visionMode = !m_visionMode;
    if(m_mainController->GetXButtonPressed())
        m_camMode = !m_camMode;

    if(m_camMode)
    {
        m_limelight->SetStreamMode(DragonLimelight::STREAM_MODE::STREAM_MAIN_AND_SECOND);
    }
    else
    {
        m_limelight->SetStreamMode(DragonLimelight::STREAM_MODE::STREAM_SECOND_AND_MAIN);
    }

    if(m_visionMode)
    {
        m_limelight->SetLEDMode(DragonLimelight::LED_MODE::LED_ON);
    }
    else
    {
        m_limelight->SetLEDMode(DragonLimelight::LED_MODE::LED_OFF);
    }
        
    //TODO:
    // try smoothing only the forward backward value instead of both forward backward and turning
    // this might give extra control
    // also try voltage ramping
    m_chassis->SetDriveMode(DragonChassis::PERCENT_POWER);

    // double forwardSpeed = TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROBOT_Y_MAGNITUDE );
    // double turnSpeed = TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROBOT_X_MAGNITUDE ); // TODO: this should be ROBOT_TURN_MAGNITUDE, not ROBOT_X_MAGNITUDE
    double forwardSpeed = -m_mainController->GetRawAxis(1);
    double turnSpeed = m_mainController->GetRawAxis(4);

    // deadbands
    if (std::abs(forwardSpeed) < 0.11)
            forwardSpeed = 0.0;
    if (std::abs(turnSpeed) < 0.11)
            turnSpeed = 0.0;

    if(m_allowClimbDrive)
        m_climber->SetClimbDriveSpeed(forwardSpeed);
    else
        m_climber->SetClimbDriveSpeed(0.0);


    frc::SmartDashboard::PutNumber("real left inches", m_chassis->GetLeftMiddleDistance());
    frc::SmartDashboard::PutNumber("real right inches", m_chassis->GetRightMiddleDistance());

    forwardSpeed = std::pow(forwardSpeed, 3);
    turnSpeed = std::pow(turnSpeed, 3);

    // temp
    // apply scaling
    turnSpeed *= 0.7;

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

void Switcher::GamepieceUpdate(bool cargo)
{
    // double armSpeed = std::pow(-TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROTATE_ARM), 3) * 3.0;
    double armSpeed = -m_secondaryController->GetRawAxis(1) * 1.25;
    if (std::abs(armSpeed) < 0.1)
        armSpeed = 0;

    // m_extendSpeed = TeleopControl::GetInstance()->GetAxisValue( TeleopControl::EXTEND_ARM );
    double extendSpeed = m_secondaryController->GetRawAxis(0);
    if (std::abs(extendSpeed) < 0.1)
        extendSpeed = 0;
    // m_wristSpeed = -TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROTATE_WRIST );
    // m_wristSpeed = m_secondaryController->GetRawAxis(5);
    double wristSpeed = -m_secondaryController->GetRawAxis(5) * 1.5;
    if (std::abs(wristSpeed) < 0.1)
        wristSpeed = 0;
    // m_intakeSpeed = TeleopControl::GetInstance()->GetAxisValue( TeleopControl::INTAKE ) - TeleopControl::GetInstance()->GetAxisValue( TeleopControl::OUTAKE );
    double intakeSpeed = m_secondaryController->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand) - m_secondaryController->GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand);
    if(cargo)
        intakeSpeed = -intakeSpeed;

    // Send angles and speeds to mechanisms
    m_intake->IntakeManual(intakeSpeed);
    m_wrist->MoveWristManualAngle(m_wrist->GetWristTargetAngle() + wristSpeed); // offset target angle by speed
    m_arm->MoveExtensionSpeed(extendSpeed, false);                             // -0.171
    // m_arm->MoveExtensionInches(m_arm->GetExtenderTargetInches() + m_extendSpeed * 0.02);
    m_arm->MoveArmAngle(m_arm->GetArmTargetAngle() + armSpeed); // offset target angle by speed
}

void Switcher::ClimberUpdate()
{
    // if (TeleopControl::GetInstance()->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::CLIMB_ELEVATOR_UP))
    //     m_climbElevSpeed = ELEV_SPEED;
    // else if (TeleopControl::GetInstance()->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::CLIMB_ELEVATOR_DOWN))
    //     m_climbElevSpeed = -ELEV_SPEED;
    // else
    //     m_climbElevSpeed = 0.0;

    double armSpeed = -m_secondaryController->GetRawAxis(1) * 1.25;
    if (std::abs(armSpeed) < 0.1)
        armSpeed = 0;

    double wristSpeed = -m_secondaryController->GetRawAxis(5);
    if (std::abs(wristSpeed) < 0.12)
        wristSpeed = 0;
    wristSpeed -= 0.1; //This is nessesary because our wrist keeps flipping when we try to climb

    double extendSpeed = m_secondaryController->GetRawAxis(0);
    if (std::abs(extendSpeed) < 0.1)
        extendSpeed = 0;

    m_wrist->MoveWristManualSpeed(wristSpeed);
    m_arm->MoveArmAngle(m_arm->GetArmTargetAngle() + armSpeed);
    m_arm->MoveExtensionSpeed(extendSpeed + 0.5, true); //TODO: move 0.25 into a constant

    // m_climbElevSpeed = m_secondaryController->GetBumper(frc::GenericHID::JoystickHand::kLeftHand) - m_secondaryController->GetBumper(frc::GenericHID::JoystickHand::kRightHand);
    // m_dropBuddyClimb = TeleopControl::GetInstance()->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::DROP_BUDDY_CLIMB);

    if (m_secondaryController->GetBumper(frc::GenericHID::JoystickHand::kLeftHand))
    {
        m_climber->MoveClimbElevator(1);
    }
    else if (m_secondaryController->GetBumperReleased(frc::GenericHID::JoystickHand::kRightHand))
    {
        m_climber->MoveClimbElevator(-1);
    }
    else
    {
        m_climber->MoveClimbElevator(0);
    }
    

    // if (m_secondaryController->GetBumperReleased(frc::GenericHID::JoystickHand::kLeftHand) || m_secondaryController->GetBumperReleased(frc::GenericHID::JoystickHand::kLeftHand))
    //     m_climber->MoveClimbElevator(-0.1);
    // m_climber->DropBuddyClimb(m_dropBuddyClimb);
}

void Switcher::ExitClimbMode()
{
    m_wrist->MoveWristManualAngle(m_wrist->GetWristRealAngle()); // zero out wrist
}