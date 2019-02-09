
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

#include <iostream>
#include <cmath>

#include <frc/GenericHID.h>

#include <controllers/axis/AnalogAxis.h>

#include <controllers/axis/LinearProfile.h>
#include <controllers/axis/CubedProfile.h>
#include <controllers/axis/DeadbandValue.h>
#include <controllers/axis/FlippedAxis.h>
#include <controllers/axis/NoDeadbandValue.h>
#include <controllers/axis/ScaledDeadbandValue.h>
#include <controllers/axis/SquaredProfile.h>


AnalogAxis::AnalogAxis
(
    frc::GenericHID*                    gamepad,            // <I> - gamepad to query
    int                                 axisID,             // <I> - axis ID this maps to
    bool                                flipAxis            // <I> - true axis is reversed from what is expected
) : m_gamepad( gamepad ),                                   //       false axis in the expected direction
    m_axis( axisID ),
    m_profile( LinearProfile::GetInstance() ),  
    m_deadband( NoDeadbandValue::GetInstance() ), 
    m_scale( new ScaledAxis()  )
{
    if ( flipAxis )
    {
        m_scale->SetScaleFactor( -1.0 );
    }
}

//==================================================================================
/// <summary>
/// Method:         GetAxisValue
/// Description:    Read the analog (axis) value and return it.  If the gamepad
///                 has an issue, return 0.0.
/// </summary>
//==================================================================================
double AnalogAxis::GetAxisValue()
{
    double value = 0.0;

    if ( m_gamepad != nullptr )
    {
        value = GetRawValue();
        value = m_deadband->ApplyDeadband( value );
        value = m_profile->ApplyProfile( value );
        value = m_scale->Scale( value );
    }
    else
    {
        std::cout << "missing gamepad \n";
    }
    return value;
}

void AnalogAxis::SetDeadBand
(
    IDragonGamePad::AXIS_DEADBAND   type            /// <I> - deadband option
)
{
    switch ( type )
    {
        case IDragonGamePad::AXIS_DEADBAND::NONE:
            m_deadband = NoDeadbandValue::GetInstance();
            break;

        case IDragonGamePad::AXIS_DEADBAND::APPLY_STANDARD_DEADBAND:
            m_deadband = DeadbandValue::GetInstance();
            break;

        case IDragonGamePad::AXIS_DEADBAND::APPLY_SCALED_DEADBAND:
            m_deadband = ScaledDeadbandValue::GetInstance();
            break;

        default:
            std::cout << "==>> invalid deadband specified \n";
            break;
    }

}


void AnalogAxis::SetAxisProfile
(
     IDragonGamePad::AXIS_PROFILE    profile         /// <I> - axis profile
)
{
    switch ( profile )
    {
        case IDragonGamePad::AXIS_PROFILE::CUBED:
            m_profile = CubedProfile::GetInstance();
            break;

        case IDragonGamePad::AXIS_PROFILE::SQUARED:
            m_profile = SquaredProfile::GetInstance();
            break;

        case IDragonGamePad::AXIS_PROFILE::LINEAR:
            m_profile = LinearProfile::GetInstance();
            break;

        default:
            std::cout << "==>> invalid profile specified \n";
            break;
    }
}


void AnalogAxis::SetAxisScaleFactor
(
    double scale                     /// <I> - scale factor - must be positive number
)
{
    m_scale->SetScaleFactor( scale );
}
       
//==================================================================================
/// <summary>
/// Method:         GetRawValue
/// Description:    Returns the analog input's raw value.
///                 If there is a connection problem, 0.0 will be returned and 
///                 a debug message will be written.
/// </summary>
//==================================================================================
double AnalogAxis::GetRawValue()
{
    double value = 0.0;
    if ( m_gamepad != nullptr )
    {
        value = m_gamepad->GetRawAxis( m_axis );
    }
    else
    {
        std::cout << "==>> Gamepad isn't connected \n";
    }
    return value;
}

