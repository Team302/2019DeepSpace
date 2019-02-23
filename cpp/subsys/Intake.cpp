/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsys/Intake.h"
#include "hal/PDP.h"
#include <subsys/IMechanism.h>
#include <xmlhw/PIDData.h>

Intake::Intake(IDragonMotorControllerVector motorControllers) :
m_intakeMotor(nullptr)
{
    for (int i = 0; i < motorControllers.size(); i++)
    {
        switch (motorControllers[i]->GetType())
        {
            case IDragonMotorController::TALON_TYPE::INTAKE:
                m_intakeMotor = static_cast<DragonTalon*>(motorControllers[i]);
            break;

            default:
            break;
        }
    }
    m_intakeMotor->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
    m_intakeMotor->Set(0);
}

void Intake::IntakeManual(double speed)
{
    m_intakeMotor->Set(speed);
}

void Intake::IntakePreset(bool cargo, bool outtake)
{
    if(cargo)
        m_intakeMotor->Set(m_cargoIntakeSpeed);
    else if(cargo && outtake)
        m_intakeMotor->Set(m_cargoOuttakeSpeed);
    else if(outtake)
        m_intakeMotor->Set(m_hatchOuttakeSpeed);
    else
        m_intakeMotor->Set(m_hatchIntakeSpeed);
}

bool Intake::ObjectPresent()
{
    return true; //Yay we have one we did it go score!!!!
}

void Intake::EnableBrakeMode(bool brakeEnabled)
{
    m_intakeMotor->EnableBrakeMode(brakeEnabled);
}


IMechanism::MECHANISM_TYPE Intake::GetType() const
{
    return IMechanism::MECHANISM_TYPE::INTAKE;
}

void Intake::SetParam
(
    IMechanism::MECHANISM_PARAM_TYPE    param,          // <I> - parameter to set
    double                              value           // <I> - parameter value
) 
{
    switch(param)
    {
        case CARGO_INTAKE_SPEED_PARAM:
            m_cargoIntakeSpeed = value;
            break;

        case CARGO_OUTTAKE_SPEED_PARAM:
            m_cargoOuttakeSpeed = value;
            break;

        case HATCH_INTAKE_SPEED_PARAM:
            m_hatchIntakeSpeed = value;
            break;

        case HATCH_OUTTAKE_SPEED_PARAM:
            m_hatchOuttakeSpeed = value;
            break;

        default:
            printf("Intake.cpp is getting an invalid parameter");
            break;


    }
}
void Intake::SetPID
(
    PIDData*        pid                 // <I> - PID control information
) 
{
    // TODO:  Override values
}




