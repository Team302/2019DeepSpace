/*
 * DriverAssist.cpp
 *
 *  Created on: Jan 25, 2019
 *      Author: Jonah Shader
 */

#include "driverassist/DriverAssist.h"
#include "frc/SmartDashboard/SmartDashboard.h"
#include "hw/LED.h"
#include "hw/LEDFactory.h"

using namespace frc;

DriverAssist::DriverAssist() : m_chassis(DragonChassis::GetInstance()),
                               m_switcher(new Switcher()),
                               m_MoveArmToPos(new MoveArmToPosition()),
                               m_deployGamePiece(new DeployGamePiece()),
                               m_intakeGamePiece(new IntakeGamePiece()),
                               m_holdDrivePositon(new HoldDrivePosition()),
                               m_targetAllign(new TargetAllign()),
                               m_driveToTarget(new DriveToTarget()),
                               m_climb(new Climb()),
                               m_frontLed(LEDFactory::GetInstance()->GetLED(LEDFactory::LED_USAGE::UNDER_FRONT)),
                               m_backLed(LEDFactory::GetInstance()->GetLED(LEDFactory::LED_USAGE::UNDER_BACK)),
                               m_topLed(LEDFactory::GetInstance()->GetLED(LEDFactory::LED_USAGE::TOP)),
                               m_deploy(false),
                               m_intake(false),
                               m_climbMode(false),
                               m_holdMode(false),
                               m_visionMode(false),
                               m_wristForcePercentOutput(false),
                               m_pMainControllerTriggerLeftHand(false),
                               m_pMainControllerTriggerRightHand(false),
                               m_cargo(false),
                               m_flip(false),
                               m_height(PlacementHeights::PLACEMENT_HEIGHT::FLOOR),
                               m_second(false)
{
}

// The update method runs every periodic process of this class
void DriverAssist::Update()
{
    // Checks for vision, hold, and allows for switcher driving
    UpdateDriverControls();

    // check climb mode button
    if (m_switcher->m_secondaryController->GetStartButtonPressed())
    {
        m_climbMode = !m_climbMode;
        if (!m_climbMode)
        {
            m_switcher->ExitClimbMode();
            // disable brake mode
            // m_chassis->EnableBrakeMode(false);
        }
        else
        {
            // enable brake mode
            // m_chassis->EnableBrakeMode(true);
        }
    }

    // check wrist force percent output mode button

    DriverAssist::AttemptingDriveCancel();
    DriverAssist::AttemptingGamePieceCancel();
    // ask switcher if drivers are trying to move
    // if they are, cancel any overlapping driverassist processes
    // TODO: add these into switcher //tomm bigg//
    // they should have a high tolerance so that there aren't accidental
    // joystick movements that could cancel the processes

    // after we determine what we can run, run them below
    SmartDashboard::PutBoolean("Climb Mode", m_climbMode);
    if (m_climbMode)
    {
        double driverAssistClimbSpeed = -m_switcher->m_secondaryController->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand) + m_switcher->m_secondaryController->GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand);
        if (std::abs(driverAssistClimbSpeed) > 0.1)
        {
            m_climb->SetClimb(driverAssistClimbSpeed);

            // make top leds correspond to climb speed
            if (m_topLed != nullptr)
                m_topLed->SetRGB(0, driverAssistClimbSpeed, 0);
        }
        else
        {
            m_climb->Cancel();
            int climbSpd = m_switcher->ClimberUpdate(m_climb->GetHoldPower());
            if (climbSpd == 1)
            {
                // cancel hold
                m_climb->CancelHold();
            }
            // else if (climbSpd == 0
        }

        // make bottom leds green all the time in climb mode
        if (m_frontLed != nullptr)
            m_frontLed->SetRGB(0, 1, 0);
        if (m_backLed != nullptr)
            m_backLed->SetRGB(0, 1, 0);
    }
    else
    {
        UpdateSecondaryControls();
        if (m_MoveArmToPos->IsDone())
        {
            // printf("movearmtopos is done\n");
            if (m_deploy)
            {
                m_deployGamePiece->Deploy(m_cargo, m_flip, true, m_second);
                m_deploy = false;
            }
            else if (m_intake)
            {
                m_intakeGamePiece->IntakeGameObject(m_cargo, m_flip, m_second);
                m_intake = false;
            }

            if (m_deployGamePiece->IsDone() && m_intakeGamePiece->IsDone())
            {
                // printf("deploy game piece is done (run gamepiece update)\n");
                m_switcher->GamepieceUpdate(m_cargo);
            }

            // make front/back leds correspond to m_flip
            if (m_flip)
            {
                if (m_backLed != nullptr)
                    m_backLed->SetRGB(0, 1, 0);
                if (m_frontLed != nullptr)
                    m_frontLed->SetRGB(0, 0, 0);
            }
            else
            {
                if (m_backLed != nullptr)
                    m_backLed->SetRGB(0, 0, 0);
                if (m_frontLed != nullptr)
                    m_frontLed->SetRGB(0, 1, 0);
            }

            // make top leds indicate new/old hatch, cargo mode
            if (m_cargo)
            {
                if (m_topLed != nullptr)
                    m_topLed->SetRGB(1, 0, 0); //red
            }
            else if (m_second)
            {
                if (m_topLed != nullptr)
                    m_topLed->SetRGB(1, 0.0, 1.0); //purple
            }
            else
            {
                if (m_topLed != nullptr)
                    m_topLed->SetRGB(0.1, 0.9, 0); //yellow
            }
        }
        else
        {
            // make top leds green when arm is moving to position
            if (m_topLed != nullptr)
                m_topLed->SetRGB(0, 1.0, 0);
        }
    }

    m_MoveArmToPos->Update();
    m_deployGamePiece->Update();
    m_intakeGamePiece->Update();
    m_driveToTarget->Update();
    m_climb->Update();
    m_chassis->UpdateChassis();

    frc::SmartDashboard::PutBoolean("Robot Fipped", m_flip);
    frc::SmartDashboard::PutBoolean("Cargo mode", m_cargo);
    frc::SmartDashboard::PutBoolean("Second intake mode", m_second);
    frc::SmartDashboard::PutNumber("Target position enum", m_height);
}

// Helper Methods

void DriverAssist::UpdateSecondaryControls()
{
    if (m_switcher->m_secondaryController->GetBumperPressed(frc::GenericHID::JoystickHand::kLeftHand))
        m_deploy = true;
    if (m_switcher->m_secondaryController->GetBumperPressed(frc::GenericHID::JoystickHand::kRightHand))
        m_intake = true;
    if (m_switcher->m_secondaryController->GetBButtonPressed())
        m_flip = !m_flip;
    if (m_switcher->m_secondaryController->GetYButtonPressed())
        m_cargo = !m_cargo;

    if (m_switcher->m_secondaryController->GetAButtonPressed())
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::FLOOR;
        m_second = false;
        m_MoveArmToPos->SetTargetPosition(m_height, m_cargo, m_flip, m_second);
    }
    if (m_switcher->m_secondaryController->GetXButtonPressed())
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER;
        m_second = true;
        m_MoveArmToPos->SetTargetPosition(m_height, m_cargo, m_flip, m_second);
    }
    if (m_switcher->m_secondaryController->GetPOV() == 180)
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP;
        m_MoveArmToPos->SetTargetPosition(m_height, m_cargo, m_flip, m_second);
    }
    if (m_switcher->m_secondaryController->GetPOV() == 270)
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW;
        m_MoveArmToPos->SetTargetPosition(m_height, m_cargo, m_flip, m_second);
    }
    if (m_switcher->m_secondaryController->GetPOV() == 0)
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID;
        m_MoveArmToPos->SetTargetPosition(m_height, m_cargo, m_flip, m_second);
    }
    if (m_switcher->m_secondaryController->GetPOV() == 90)
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH;
        m_MoveArmToPos->SetTargetPosition(m_height, m_cargo, m_flip, m_second);
    }
}

void DriverAssist::UpdateDriverControls()
{
    if (m_second)
    {
        if (m_switcher->m_mainController->GetBumperPressed(frc::GenericHID::JoystickHand::kLeftHand))
            // m_deploy = true;
            m_intake = true;

        if (m_switcher->m_mainController->GetBumperPressed(frc::GenericHID::JoystickHand::kRightHand))
            // m_intake = true;
            m_deploy = true;
    }
    if (DriverAssist::TriggerPressed(DriverAssist::TriggerPressed(m_switcher->m_mainController->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand))) && !m_pMainControllerTriggerLeftHand)
    {
        m_visionMode = true;
        m_holdMode = false;
        m_driveToTarget->Init(m_flip);
    }
    else if (!DriverAssist::TriggerPressed(DriverAssist::TriggerPressed(m_switcher->m_mainController->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand))) && m_pMainControllerTriggerLeftHand)
    {
        m_visionMode = false;
        m_driveToTarget->Cancel();
    }

    if (DriverAssist::TriggerPressed(DriverAssist::TriggerPressed(m_switcher->m_mainController->GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand))) && !m_pMainControllerTriggerRightHand)
    {
        m_holdMode = true;
        m_visionMode = false;
        m_driveToTarget->Cancel();
        m_holdDrivePositon->ResetLeftRightTargetPosition();
    }
    else if (DriverAssist::TriggerPressed(!DriverAssist::TriggerPressed(m_switcher->m_mainController->GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand))) && m_pMainControllerTriggerRightHand)
    {
        m_holdMode = false;
    }

    if (m_visionMode)
    {
        // m_targetAllign->Update();
        // if(m_targetAllign->IsDone())
        //     m_visionMode = false;
    }
    else if (m_holdMode)
    {
        double forwardSpeed = -(m_switcher->m_mainController->GetRawAxis(1));
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

    m_pMainControllerTriggerLeftHand = DriverAssist::TriggerPressed(m_switcher->m_mainController->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand));
    m_pMainControllerTriggerRightHand = DriverAssist::TriggerPressed(m_switcher->m_mainController->GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand));
}

void DriverAssist::AttemptingGamePieceCancel()
{
    if (!m_MoveArmToPos->IsDone())
    {
        bool tryCancel = false;
        if (std::abs(m_switcher->m_secondaryController->GetRawAxis(0)) > 0.50)
            tryCancel = true;
        if (std::abs(m_switcher->m_secondaryController->GetRawAxis(1)) > 0.50)
            tryCancel = true;
        if (std::abs(m_switcher->m_secondaryController->GetRawAxis(5)) > 0.50)
            tryCancel = true;
        // if (std::abs(m_switcher->m_secondaryController->GetRawAxis(4)) > 0.50)
        //     tryCancel = true;

        if (tryCancel)
        {
            m_MoveArmToPos->Cancel();
        }
    }

    // m_MoveArmToPos->Cancel();
}

void DriverAssist::AttemptingDriveCancel()
{
    // Global cancel
    // if(m_switcher->m_secondaryController->GetBumperPressed(frc::GenericHID::JoystickHand::kLeftHand))
    // m_approachTarget->Cancel();
}

bool DriverAssist::TriggerPressed(double value)
{
    return value > 0.75;
}