//====================================================================================================================================================
// Copyright 2018 Lake Orion Robobitcs FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

#include <subsys/HatchMechanism.h>

#include <subsys/IMechanism.h>
#include <xmlhw/PIDData.h>
#include <frc/smartdashboard/SmartDashboard.h>

HatchMechanism::HatchMechanism
(
    IDragonMotorControllerVector motorControllers
) : m_motor(nullptr)
{
    for( int inx=0; inx<motorControllers.size(); ++inx )
    {
        switch (motorControllers[inx]->GetType())
        {
            case IDragonMotorController::TALON_TYPE::HATCH_MECH_MOTOR:
                m_motor = dynamic_cast<DragonTalon*>(motorControllers[inx]);
                break;

            default:
                printf( "==>> unknown motor in Hatch Mechanism %d \n", motorControllers[inx]->GetType() );
                break;
        }
    }

    if ( m_motor != nullptr )
    {
        m_motor->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT);
        m_motor->Set(0.0);
        SetLegalStartingPos();
    }
    else
    {
        printf( "==>> no motor set in Hatch Mechanism \n" );
    }
}

void HatchMechanism::SetState
(
    bool  open        // <I> - true  = open to allow grabbing or deploying hatch
)                     //       false = close to hold hatch
{
    auto rotations = open ? m_openRots : 0;
    
    m_motor->SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE::ROTATIONS);
    m_motor->Set(rotations);
}

void HatchMechanism::SetSpeed 
(
    double speed    // <I> - speed to run motors
)
{
    m_motor->SetControlMode( IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT );
    m_motor->Set( speed );
    frc::SmartDashboard::PutNumber("hatch mech rots", m_motor->GetRotations());
}


IMechanism::MECHANISM_TYPE HatchMechanism::GetType() const
{
    return IMechanism::MECHANISM_TYPE::HATCH_MANIPULATOR;
}

void HatchMechanism::SetParam
(
    IMechanism::MECHANISM_PARAM_TYPE    param,          // <I> - parameter to set
    double                              value           // <I> - parameter value
) 
{
    switch(param)
    {
        case IMechanism::MECHANISM_PARAM_TYPE::HATCH_MECH_OPEN_ROTATIONS:
            m_openRots = value;
            break;

        // case IMechanism::MECHANISM_PARAM_TYPE::HATCH_MECH_CLOSED_ROTATIONS:
        //     m_closed = value;
        //     break;

        default:
            printf("HatchMechanism.cpp is getting an invalid parameter");
            break;


    }
}


void HatchMechanism::SetPID
(
    PIDData*        pid                 // <I> - PID control information
) 
{
    m_motor->SetPIDF(pid->GetP(), pid->GetI(), pid->GetD(), pid->GetF());
    if (pid->GetMode() == PIDData::MOTION_MAGIC)
    {
        m_motor->ConfigMotionAcceleration(pid->GetMaxAcceleration());
        m_motor->ConfigMotionCruiseVelocity(pid->GetCruiseVelocity());
    }
}

void HatchMechanism::SetPracticeStartingPos()
{
    m_motor->SetRotationOffset(0);
}

void HatchMechanism::SetLegalStartingPos()
{
    m_motor->SetRotationOffset(m_openRots - 0.1);
}
