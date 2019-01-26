/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsys/Intake.h"
#include "hal/PDP.h"

Intake::Intake() :
m_intakeMotor(new DragonTalon(IDragonMotorController::TALON_TYPE::INTAKE, 0, 0, 0))
{
    m_intakeMotor->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
}

void Intake::IntakeManual(double speed)
{
    m_intakeMotor->Set(speed);
}

void Intake::IntakePreset(bool cargo, bool outtake)
{
    if(cargo)
        m_intakeMotor->Set(CARGO_INTAKE_SPEED);
    else if(cargo && outtake)
        m_intakeMotor->Set(CARGO_OUTTAKE_SPEED);
    else if(outtake)
        m_intakeMotor->Set(HATCH_OUTTAKE_SPEED);
    else
        m_intakeMotor->Set(HATCH_INTAKE_SPEED);
}

bool Intake::ObjectPresent()
{
    return true; //Yay we have one we did it go score!!!!
}



