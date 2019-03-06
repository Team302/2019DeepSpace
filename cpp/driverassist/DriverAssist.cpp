/*
 * DriverAssist.cpp
 *
 *  Created on: Jan 25, 2019
 *      Author: Jonah Shader
 */

#include "driverassist/DriverAssist.h"
#include "SmartDashboard/SmartDashboard.h"

using namespace frc;

DriverAssist::DriverAssist() : m_chassis(DragonChassis::GetInstance()),
                               m_switcher(new Switcher()),
                               m_MoveArmToPos(new MoveArmToPosition()),
                               m_deployGamePiece(new DeployGamePiece()),
                               m_holdDrivePositon(new HoldDrivePosition()),
                               m_targetAllign(new TargetAllign()),
                               m_climb(new Climb()),
                               m_deploy(false),
                               m_climbMode(false),
                               m_holdMode(false),
                               m_visionMode(false),
                               m_cargo(false),
                               m_flip(false),
                               m_height(PlacementHeights::PLACEMENT_HEIGHT::FLOOR)
{
}

// The update method runs every periodic process of this class
void DriverAssist::Update()
{
    // Checks for vision, hold, and allows for switcher driving
    UpdateDriverControls();

    if(m_switcher->m_secondaryController->GetStartButtonPressed())
    {
        m_climbMode = !m_climbMode;
        if (!m_climbMode)
        {
            m_switcher->ExitClimbMode();
        }
    }
        

    DriverAssist::AttemptingDriveCancel();
    DriverAssist::AttemptingGamePieceCancel();
    // ask switcher if drivers are trying to move
    // if they are, cancel any overlapping driverassist processes
    // TODO: add these into switcher
    // they should have a high tolerance so that there aren't accidental
    // joystick movements that could cancel the processes

    // after we determine what we can run, run them below
    SmartDashboard::PutBoolean("Climb Mode", m_climbMode);
    if(m_climbMode)
    {
        double driverAssistClimbSpeed = -m_switcher->m_secondaryController->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand) + m_switcher->m_secondaryController->GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand);
        if (std::abs(driverAssistClimbSpeed) > 0.1)
        {
            m_climb->SetClimb(driverAssistClimbSpeed);
        }
        else
        {
            m_climb->Cancel();
            m_switcher->ClimberUpdate();
        }
        
        
    }
    else
    {
        UpdateSecondaryControls();
        if (m_MoveArmToPos->IsDone())
        {
            // printf("movearmtopos is done\n");
            if (m_deploy)
            {
                m_deployGamePiece->Deploy(m_cargo, false, true);
                m_deploy = false;
            }

            if (m_deployGamePiece->IsDone())
            {
                // printf("deploy game piece is done (run gamepiece update)\n");
                m_switcher->GamepieceUpdate(m_cargo);
            }
        }
    }
    
    m_MoveArmToPos->Update();
    m_deployGamePiece->Update();
    m_climb->Update();
    m_chassis->UpdateChassis();

    frc::SmartDashboard::PutBoolean("Robot Fipped", m_flip);
    frc::SmartDashboard::PutBoolean("Cargo mode", m_cargo);
    frc::SmartDashboard::PutNumber("Target position enum", m_height);
}

// Helper Methods

void DriverAssist::UpdateSecondaryControls()
{
    if (m_switcher->m_secondaryController->GetBumperPressed(frc::GenericHID::JoystickHand::kLeftHand))
        m_deploy = true;
    if (m_switcher->m_secondaryController->GetBButtonPressed())
        m_flip = !m_flip;
    if (m_switcher->m_secondaryController->GetYButtonPressed())
        m_cargo = !m_cargo;

    // if(m_switcher->m_mainController->GetPOV(180))
    // {
    //     m_height = PlacementHeights::PLACEMENT_HEIGHT::START_POSITION;
    //     m_MoveArmToPos->SetTargetPosition(m_height, m_cargo, m_flip);
    // }

    if (m_switcher->m_secondaryController->GetAButtonPressed())
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::FLOOR;
        m_MoveArmToPos->SetTargetPosition(m_height, m_cargo, m_flip);
    }
    if (m_switcher->m_secondaryController->GetXButtonPressed())
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER;
        m_MoveArmToPos->SetTargetPosition(m_height, m_cargo, m_flip);
    }
    if (m_switcher->m_secondaryController->GetPOV() == 180)
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP;
        m_MoveArmToPos->SetTargetPosition(m_height, m_cargo, m_flip);
    }
    if (m_switcher->m_secondaryController->GetPOV() == 270)
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW;
        m_MoveArmToPos->SetTargetPosition(m_height, m_cargo, m_flip);
    }
    if (m_switcher->m_secondaryController->GetPOV() == 0)
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID;
        m_MoveArmToPos->SetTargetPosition(m_height, m_cargo, m_flip);
    }
    if (m_switcher->m_secondaryController->GetPOV() == 90)
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH;
        m_MoveArmToPos->SetTargetPosition(m_height, m_cargo, m_flip);
    }
    if (m_switcher->m_secondaryController->GetBumperPressed(GenericHID::JoystickHand::kRightHand))
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER_HOLE;
        m_MoveArmToPos->SetTargetPosition(m_height, m_cargo, m_flip);
    }
}

void DriverAssist::UpdateDriverControls()
{
    if (m_switcher->m_mainController->GetBumperPressed(frc::GenericHID::JoystickHand::kLeftHand))
    {
        m_visionMode = true;
        m_holdMode = false;
        m_targetAllign->Init();
    }
    else if (m_switcher->m_mainController->GetBumperReleased(frc::GenericHID::JoystickHand::kLeftHand))
    {
        m_visionMode = false;
    }

    if(m_switcher->m_mainController->GetBumperPressed(frc::GenericHID::JoystickHand::kRightHand))
    {
        m_holdMode = true;
        m_visionMode = false;
        m_holdDrivePositon->ResetLeftRightTargetPosition();
    }
    else if (m_switcher->m_mainController->GetBumperReleased(frc::GenericHID::JoystickHand::kRightHand))
    {
        m_holdMode = false;
    }

    if(m_visionMode)
    {
        m_targetAllign->Update();
        if(m_targetAllign->IsDone())
            m_visionMode = false;
    }
    else if(m_holdMode)
    {    
        double forwardSpeed = - (m_switcher->m_mainController->GetRawAxis(1));
        double turnSpeed = (m_switcher->m_mainController->GetRawAxis(4));

        // deadbands
        if (std::abs(forwardSpeed) < 0.11)
                forwardSpeed = 0.0;
        if (std::abs(turnSpeed) < 0.11)
                turnSpeed = 0.0;

        forwardSpeed = std::pow(forwardSpeed, 3);
        turnSpeed = std::pow(turnSpeed, 3);

        forwardSpeed *= HOLD_MODE_MAX_INCHES_PER_SECOND_FORWARD;
        turnSpeed *= HOLD_MODE_MAX_INCHES_PER_SECOND_TURNING;
        double leftOffset = forwardSpeed + turnSpeed;
        double rightOffset = forwardSpeed - turnSpeed;
        leftOffset *= 0.02;
        rightOffset *= 0.02;

        m_holdDrivePositon->SetLeftRightTargetOffsetPosition(leftOffset, rightOffset);
        m_holdDrivePositon->RunHoldMode();
    }
    else
    {
        m_switcher->DriveUpdate();
    }
}

void DriverAssist::AttemptingGamePieceCancel()
{
    if (std::abs(m_switcher->m_secondaryController->GetRawAxis(0)) > 0.50)
        m_MoveArmToPos->Cancel();
    if (std::abs(m_switcher->m_secondaryController->GetRawAxis(2)) > 0.50)
        m_MoveArmToPos->Cancel();
    if (std::abs(m_switcher->m_secondaryController->GetRawAxis(3)) > 0.50)
        m_MoveArmToPos->Cancel();
    if (std::abs(m_switcher->m_secondaryController->GetRawAxis(4)) > 0.50)
        m_MoveArmToPos->Cancel();
}

void DriverAssist::AttemptingDriveCancel()
{
    // Global cancel
    // if(m_switcher->m_secondaryController->GetBumperPressed(frc::GenericHID::JoystickHand::kLeftHand))
    // m_approachTarget->Cancel();
}