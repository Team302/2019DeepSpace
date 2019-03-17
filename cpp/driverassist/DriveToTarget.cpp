#include "driverassist/DriveToTarget.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <vector>
#include "subsys/chassis/DragonChassis.h"

DriveToTarget::DriveToTarget() :
    m_limelight(DragonLimelight::GetInstance()),
    m_chassis(DragonChassis::GetInstance()),
    m_arm(MechanismFactory::GetMechanismFactory()->GetArm()),
    m_state(DONE),
    m_flip(false),
    m_pHeadingCorrection(0)
{
}

void DriveToTarget::Init(bool flip)
{
    m_state = DRIVING_TO_TARGET;
    m_flip = flip;
}

void DriveToTarget::Update()
{
    // if(m_arm->GetArmRealAngle() < 0)
    //     //code
    // else

    

    switch (m_state)
    {
        case DRIVING_TO_TARGET:
        {
            m_limelight->SetCamMode(DragonLimelight::CAM_MODE::CAM_VISION);
            m_limelight->SetLEDMode(DragonLimelight::LED_ON);
            // std::vector<double> solution = m_limelight->Get3DSolve();
            // frc::SmartDashboard::PutNumber("3D X", solution[0]);
            // frc::SmartDashboard::PutNumber("3D Y", solution[1]);
            // frc::SmartDashboard::PutNumber("3D Y(z)", solution[2]); //distance 
            // frc::SmartDashboard::PutNumber("3D Pitch", solution[3]);
            // frc::SmartDashboard::PutNumber("3D Yaw", solution[4]);
            // frc::SmartDashboard::PutNumber("3D Roll", solution[5]);

            // double rocketHeading = RadToHeading(std::atan2(solution[2], solution[0]));

            // double headingCorrection = -(rocketHeading * ROCKET_YAW_MULT) + (solution[4] * ROBOT_YAW_MULT);
            // headingCorrection *= 0.01;
            // frc::SmartDashboard::PutNumber("3D Heading Correction", headingCorrection);

            double headingCorrection = m_limelight->GetTargetHorizontalOffset() * 0.01 * ROBOT_YAW_MULT;

            
            double delta = headingCorrection - m_pHeadingCorrection;
    
            m_pHeadingCorrection = headingCorrection;
            headingCorrection += delta * 250.0;

            if (headingCorrection > 0.7)
                headingCorrection = 0.7;
            else if (headingCorrection < -0.7)
                headingCorrection = -0.7;

            frc::SmartDashboard::PutNumber("vision delta", delta);

            frc::SmartDashboard::PutNumber("3D Heading Correction limited", headingCorrection);

            m_chassis->SetLeftRightMagnitudes((m_flip ? -DRIVE_SPEED : DRIVE_SPEED) + headingCorrection, (m_flip ? -DRIVE_SPEED : DRIVE_SPEED) - headingCorrection);
        }
            break;
        
        case DONE:
            m_limelight->SetCamMode(DragonLimelight::CAM_MODE::CAM_DRIVER);
            m_limelight->SetLEDMode(DragonLimelight::LED_OFF);
            break;

        default:

            break;
    }
}

void DriveToTarget::Cancel()
{
    m_state = DONE;
}

bool DriveToTarget::IsDone()
{
    return m_state == DONE;
}

double DriveToTarget::RadToHeading(double value)
{
    return (-value / M_PI) + 90.0;
}