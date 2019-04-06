#include "driverassist/DriveToTarget.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <vector>
#include "subsys/chassis/DragonChassis.h"
#include "hw/LED.h"
#include "hw/LEDFactory.h"

DriveToTarget::DriveToTarget() : m_limelight(DragonLimelight::GetInstance()),
                                 m_chassis(DragonChassis::GetInstance()),
                                 m_hold(new HoldDrivePosition()),
                                 m_arm(MechanismFactory::GetMechanismFactory()->GetArm()),
                                 m_state(DONE),
                                 m_flip(false),
                                 m_pHeadingCorrection(0),
                                 m_coarseAdjustInitLoops(0),
                                 m_frontLed(LEDFactory::GetInstance()->GetLED(LEDFactory::LED_USAGE::UNDER_FRONT)),
                                 m_backLed(LEDFactory::GetInstance()->GetLED(LEDFactory::LED_USAGE::UNDER_BACK)),
                                 m_topLed(LEDFactory::GetInstance()->GetLED(LEDFactory::LED_USAGE::TOP))
{
}

void DriveToTarget::Init(bool flip)
{
    m_state = COARSE_ADJUSTMENT_INIT; //DRIVING_TO_TARGET
    m_flip = flip;
    m_coarseAdjustInitLoops = 0;
    frc::SmartDashboard::PutString("DriveToTarget state", "Init");
    m_chassis->SetDriveMode(DragonChassis::DRIVE_MODE::PERCENT_POWER);
    m_chassis->SetLeftRightMagnitudes(0, 0);
}

void DriveToTarget::Update()
{
    
    bool direction = false;
    switch (m_state)
    {
    case COARSE_ADJUSTMENT_INIT:
    {
        frc::SmartDashboard::PutString("DriveToTarget state", "COARSE_ADJUSTMENT_INIT");

        // Set LED Modes on limelight
        m_limelight->SetCamMode(DragonLimelight::CAM_MODE::CAM_VISION);
        m_limelight->SetLEDMode(DragonLimelight::LED_ON);

        // Get target offset
        double limelightValue = m_limelight->GetTargetHorizontalOffset();

        // Assuming makes sure our target is real and not noise?
        if (m_coarseAdjustInitLoops > 6)
        {
            direction = limelightValue > 0; //true = turn right
            double turnDist = limelightValue * ROT_OVER_HEADING / 2.0;
            frc::SmartDashboard::PutNumber("turnDist before reduction", turnDist);
            bool turnDistSign = turnDist > 0;
            // turnDist += ((turnDist > 0) ? -EARLY_STOP_DISTANCE : EARLY_STOP_DISTANCE); 
            turnDist *= 0.2;
            if ((turnDist > 0) != turnDistSign)
            {
                turnDist = 0;
                frc::SmartDashboard::PutBoolean("COARSE_ADJUSTMENT_INIT too close for coarse", true);
            }
            else
            {
                frc::SmartDashboard::PutBoolean("COARSE_ADJUSTMENT_INIT too close for coarse", false);
            }
            
            // move to position
            m_hold->ResetLeftRightTargetPosition();
            m_hold->SetLeftRightTargetOffsetPosition(limelightValue * ROT_OVER_HEADING / 2.0, -limelightValue * ROT_OVER_HEADING / 2.0);
            m_hold->RunHoldMode();
            m_state = turnDist == 0 ? DRIVING_TO_TARGET : COARSE_ADJUSTMENT;
        }

        m_coarseAdjustInitLoops++;
    }
        break;

    case COARSE_ADJUSTMENT:
    {
        // Set limelight modes
        frc::SmartDashboard::PutString("DriveToTarget state", "COARSE_ADJUSTMENT");
        m_limelight->SetCamMode(DragonLimelight::CAM_MODE::CAM_VISION);
        m_limelight->SetLEDMode(DragonLimelight::LED_ON);

        double turnVelocity = m_chassis->GetLeftMiddleVelocity() - m_chassis->GetRightMiddleVelocity(); // turning left is negative, right is positive
        if ((turnVelocity > 0 != direction) && turnVelocity != 0)
        {
            double totalDistanceToTarget = std::abs(m_hold->GetLeftDistanceToTarget()) + std::abs(m_hold->GetRightDistanceToTarget());
            if (totalDistanceToTarget < COARSE_DONE_DISTANCE_THRESHOLD)
                m_state = DRIVING_TO_TARGET;
        }
    }

        break;

    case DRIVING_TO_TARGET:
    {
        frc::SmartDashboard::PutString("DriveToTarget state", "DRIVING_TO_TARGET");
        m_limelight->SetCamMode(DragonLimelight::CAM_MODE::CAM_VISION);
        m_limelight->SetLEDMode(DragonLimelight::LED_ON);

        // disable robot leds
        if (m_topLed != nullptr)
            m_topLed->DisableLED();
        if (m_frontLed != nullptr)
        m_frontLed->DisableLED();
        if (m_backLed != nullptr)
            m_backLed->DisableLED();

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
        // frc::SmartDashboard::PutNumber("3D Heading Correction", headingCorrection);c 

        double limelightValue = m_limelight->GetTargetHorizontalOffset();
        double headingCorrection = limelightValue * ROBOT_YAW_MULT;

        double delta = headingCorrection - m_pHeadingCorrection;

        m_pHeadingCorrection = headingCorrection;
        // headingCorrection += delta * 250.0;

        if (headingCorrection > 0.7)
            headingCorrection = 0.7;
        else if (headingCorrection < -0.7)
            headingCorrection = -0.7;

        // frc::SmartDashboard::PutNumber("vision delta", delta);

        frc::SmartDashboard::PutNumber("Limelight horizontal offset", limelightValue);
        double chassisRot = m_chassis->GetLeftMiddleDistance() - m_chassis->GetRightMiddleDistance();
        frc::SmartDashboard::PutNumber("Rot", chassisRot);

        // break; //TEMP
        m_chassis->SetDriveMode(DragonChassis::DRIVE_MODE::PERCENT_POWER);
        m_chassis->SetLeftRightMagnitudes((m_flip ? -DRIVE_SPEED : DRIVE_SPEED) + headingCorrection, (m_flip ? -DRIVE_SPEED : DRIVE_SPEED) - headingCorrection);
    }
    break;

    case DONE:
        frc::SmartDashboard::PutString("DriveToTarget state", "DONE");
        //TODO: are these conflicting? is this why we see the limelight flashing randomly?
        m_limelight->SetCamMode(DragonLimelight::CAM_MODE::CAM_DRIVER);
        m_limelight->SetLEDMode(DragonLimelight::LED_OFF);

        //re enable leds
        if (m_topLed != nullptr)
            m_topLed->EnableLED();
        if (m_frontLed != nullptr)
            m_frontLed->EnableLED();
        if (m_backLed != nullptr)
            m_backLed->EnableLED();
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