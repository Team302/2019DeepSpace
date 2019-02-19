/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "driverassist/TargetAllign.h"
#include "frc/smartdashboard/SmartDashboard.h"

TargetAllign::TargetAllign() :  m_holdDrivePositon(new HoldDrivePosition()),
                                m_limelight(DragonLimelight::GetInstance()),
                                m_currentState(ALLIGNING)
{
    m_limelight->SetLEDMode(DragonLimelight::LED_MODE::LED_OFF);
    m_limelight->SetCamMode(DragonLimelight::CAM_MODE::CAM_DRIVER);
}


void TargetAllign::Init()
{
    printf("TA Init\n");
    m_currentState = ALLIGNING;
    m_holdDrivePositon->ResetLeftRightTargetPosition();
    m_limelight->SetLEDMode(DragonLimelight::LED_MODE::LED_ON);
    m_limelight->SetCamMode(DragonLimelight::CAM_MODE::CAM_VISION);
}

void TargetAllign::Update()
{
    frc::SmartDashboard::PutNumber("TA Target X", m_limelight->GetTargetHorizontalOffset());
    switch(m_currentState)
    {
        case ALLIGNING:
            if (m_limelight->HasTarget() < 0.5)
            {
                printf("NO TARGET \n");
                m_currentState = DONE;
            }
            else if (std::abs(m_limelight->GetTargetHorizontalOffset() < DONE_TARGET_OFFSET))
            {
                printf("REACHED TARGET\n");
                m_currentState = DONE;
            }
            else if (m_limelight->GetTargetHorizontalOffset() < 0)
            {
                printf("TURNING LEFT \n");
                m_holdDrivePositon->SetLeftRightTargetOffsetPosition(-DRIVE_SPEED * 0.02, DRIVE_SPEED * 0.02);
            }
            else
            {
                printf("TURNING RIGHT \n");
                m_holdDrivePositon->SetLeftRightTargetOffsetPosition(DRIVE_SPEED * 0.02, -DRIVE_SPEED * 0.02);
            }
            m_holdDrivePositon->RunHoldMode();
            break;
        case DONE:
            printf("TA DONE\n");
            m_limelight->PrintValues();
            m_limelight->SetLEDMode(DragonLimelight::LED_MODE::LED_OFF);
            m_limelight->SetCamMode(DragonLimelight::CAM_MODE::CAM_DRIVER);
           
            break;
        default:
            printf("TARGET ALLIGN WRONG STATE");

            break;
    }
}

bool TargetAllign::IsDone()
{
    return m_currentState = DONE;
}
