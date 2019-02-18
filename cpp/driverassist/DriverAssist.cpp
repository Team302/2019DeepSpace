/*
 * DriverAssist.cpp
 *
 *  Created on: Jan 25, 2019
 *      Author: Jonah Shader
 */

#include "driverassist/DriverAssist.h"
#include "frc/SmartDashboard/SmartDashboard.h"

using namespace frc;

DriverAssist::DriverAssist() : m_switcher(new Switcher()),
                               m_MoveArmToPos(new MoveArmToPosition()),
                               m_deployGamePiece(new DeployGamePiece()),
                               m_deploy(false),
                               m_cargo(false),
                               m_flip(false),
                               m_height(PlacementHeights::PLACEMENT_HEIGHT::FLOOR)
{
}

// The update method runs every periodic process of this class
void DriverAssist::Update()
{
    DriverAssist::AttemptingDriveCancel();
    DriverAssist::AttemptingGamePieceCancel();
    GetDesiredHeight();
    // ask switcher if drivers are trying to move
    // if they are, cancel any overlapping driverassist processes
    // TODO: add these into switcher
    // they should have a high tolerance so that there aren't accidental
    // joystick movements that could cancel the processes
    // after we determine what we can run, run them below
    if (m_MoveArmToPos->IsDone())
    {
        if (m_deploy)
        {
            m_deployGamePiece->Deploy(m_cargo, m_flip, true);
            m_deploy = false;
        }

        if (m_deployGamePiece->IsDone())
        {
            m_switcher->GamepieceUpdate(m_cargo);
            // m_switcher->ClimberUpdate();
        }
    }

    // allow driver control when not running overlapping processes
    if (true) // TODO: dont check if true, check of m_approachTarget->IsDone();
    {
        m_switcher->DriveUpdate();
    }

    m_MoveArmToPos->Update();
    m_deployGamePiece->Update();

    frc::SmartDashboard::PutBoolean("Robot Fipped", m_flip);
    frc::SmartDashboard::PutBoolean("Cargo mode", m_cargo);
    frc::SmartDashboard::PutNumber("Target position enum", m_height);
}

// Helper Methods

void DriverAssist::GetDesiredHeight()
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
    }
    else if (m_switcher->m_secondaryController->GetXButtonPressed())
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::HUMAN_PLAYER;
    }
    else if (m_switcher->m_secondaryController->GetPOV() == 180)
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::CARGOSHIP;
    }
    else if (m_switcher->m_secondaryController->GetPOV() == 270)
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::ROCKET_LOW;
    }
    else if (m_switcher->m_secondaryController->GetPOV() == 0)
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::ROCKET_MID;
    }
    else if (m_switcher->m_secondaryController->GetPOV() == 90)
    {
        m_height = PlacementHeights::PLACEMENT_HEIGHT::ROCKET_HIGH;
    }
    m_MoveArmToPos->SetTargetPosition(m_height, m_cargo, m_flip);
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