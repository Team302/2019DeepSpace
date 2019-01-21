
/*========================================================================================================
 * DragonXBox.cpp
 *========================================================================================================
 *
 * File Description:  Wrapper for an XBOX controller used to control the robot in teleop mode.
 *
 *========================================================================================================*/


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

#include <controllers/DragonXBox.h>

#include <controllers/axis/IDeadband.h>
#include <controllers/axis/IProfile.h>

#include <controllers/button/DigitalButton.h>


#include <frc/GenericHID.h>
#include <frc/XboxController.h>
 
DragonXBox::DragonXBox
( 
    int port
) : m_xbox( new frc::XboxController( port ) ),
    m_axis()
{
    // Create Axis Objects
    m_axis[ LEFT_JOYSTICK_X]  = new AnalogAxis( this, LEFT_JOYSTICK_X, false  );
    m_axis[ LEFT_JOYSTICK_Y]  = new AnalogAxis( this, LEFT_JOYSTICK_Y, true   );
    m_axis[ RIGHT_JOYSTICK_X] = new AnalogAxis( this, RIGHT_JOYSTICK_X, false );
    m_axis[ RIGHT_JOYSTICK_Y] = new AnalogAxis( this, RIGHT_JOYSTICK_Y, true  );
    m_axis[ LEFT_TRIGGER]     = new AnalogAxis( this, LEFT_TRIGGER,     false );
    m_axis[ RIGHT_TRIGGER]    = new AnalogAxis( this, RIGHT_TRIGGER,    false );

    // Create DigitalButton Objects for the physical buttons
    m_button[A_BUTTON]            = new DigitalButton( this, A_BUTTON            );
    m_button[B_BUTTON]            = new DigitalButton( this, B_BUTTON            );
    m_button[X_BUTTON]            = new DigitalButton( this, X_BUTTON            );
    m_button[Y_BUTTON]            = new DigitalButton( this, Y_BUTTON            );
    m_button[LEFT_BUMPER]         = new DigitalButton( this, LEFT_BUMPER         );
    m_button[RIGHT_BUMPER]        = new DigitalButton( this, RIGHT_BUMPER        );
    m_button[BACK_BUTTON]         = new DigitalButton( this, BACK_BUTTON         );
    m_button[START_BUTTON]        = new DigitalButton( this, START_BUTTON        );
    m_button[LEFT_STICK_PRESSED]  = new DigitalButton( this, LEFT_STICK_PRESSED  );
    m_button[RIGHT_STICK_PRESSED] = new DigitalButton( this, RIGHT_STICK_PRESSED );
    
    // Create AnalogButton Objects for the triggers

    // Create POVButton Objects for the POV
}

DragonXBox::~DragonXBox()
{
    delete m_xbox;
    m_xbox = nullptr;
}

   
//getters
///-------------------------------------------------------------------------------------------------
/// Method:      GetAxisValue
/// Description: Return the current value (between -1.0 and 1.0) for the requested axis.
/// Returns:     float   - current axis value
///-------------------------------------------------------------------------------------------------
float DragonXBox::GetAxisValue
(
    AXIS_IDENTIFIER    axis// <I> - axis identifier to read
) const
{
    float value = 0.0;
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis]->GetAxisValue();
    }
    return value;
}



///-------------------------------------------------------------------------------------------------
/// Method:      IsButtonPressed
/// Description: Return whether the requested button is selected (true) or not (false)
/// Returns:     bool    true  - button is pressed
///              false - button is not pressed
///-------------------------------------------------------------------------------------------------
bool DragonXBox::IsButtonPressed
(
    BUTTON_IDENTIFIER    button // <I> - button to check
) const
{
    bool isPressed = false;
    return isPressed;
}


//setters
///-------------------------------------------------------------------------------------------------
/// Method:      SetProfile
/// Description: Specify the profile curve used for setting the sensitivity of the axis.  By default,
///              this is linear, but a cubic curve would give more control when the axis is barely
///              pressed (e.g. if it were moved 50% forward, instead of returning 0.5, it would
///              return 0.5 * 0.5 * 0.5 or .125, but when the axis was moved all the way forward,
///              it would return the same value -- 1.0.  Since it is cubed, it retains the sign.
///
///              This affects values returned from GetAxis calls.
/// Returns:     void
///-------------------------------------------------------------------------------------------------
void DragonXBox::SetAxisProfile
(
    AXIS_IDENTIFIER                 axis,       // <I> - axis identifier to modify
    AXIS_PROFILE  	                curve       // <I> - the definition of the sensitivity
)
{
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis]->SetAxisProfile( curve );
    }        
}


///-------------------------------------------------------------------------------------------------
/// Method:      SetScale
/// Description: Scale the returned value to a range between the specified negative scale factor and
///              the scale factor.  This is used to reduce the maximum value returned.
///
///              This affects values returned from GetAxis calls.
/// Returns:     void
///-------------------------------------------------------------------------------------------------
void DragonXBox::SetAxisScale
(
    AXIS_IDENTIFIER    			        axis,       // <I> - axis identifier to modify
    float                               scaleFactor // <I> - value  (0 < scale <= 1.0) to scale the axis value
)
{
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis]->SetAxisScaleFactor( scaleFactor );
    }        
} 
 
///==================================================================================
/// <summary>
/// Method:         SetAxisDeadband
/// Description:    Specify what deadband behavior is desired such as none, standard,
///                 standard with scaling.
/// Returns:        void
/// </summary>
///==================================================================================
void DragonXBox::SetAxisDeadband
(
    AXIS_IDENTIFIER axis, /// <I> - axis to modify
    AXIS_DEADBAND type    /// <I> - deadband option
) 
{
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis]->SetDeadBand( type );
    }        
}



    //==================================================================================
    /// <summary>
    /// Method:         SetButtonMode
    /// Description:    Specify how the button should behave.  Examples include (but
    ///                 not limited to):
    ///                 - pressed / not pressed
    ///                 - toggle
    /// Returns:        void
    /// </summary>
    //==================================================================================
    void DragonXBox::SetButtonMode
    (
        BUTTON_IDENTIFIER button, /// <I> - button to check
        BUTTON_MODE mode          /// <I> - button behavior
    )
    {

    }

    double DragonXBox::GetRawAxis
    (
        AXIS_IDENTIFIER    axis        // <I> - axis identifier to read
    ) const 
    {
        double value = 0.0;
        return value;
    }

    bool DragonXBox::IsRawButtonPressed
    (
        BUTTON_IDENTIFIER    button         // <I> - button to check
    ) const 
    {
        bool pressed = false;
        //switch statement to check if button is pressed depending on which button is identified
        switch(button)
        {
            case A_BUTTON:
                pressed = m_xbox->GetAButton();
                break;
		    case B_BUTTON:
                pressed = m_xbox->GetBButton();
                break;
		    case X_BUTTON:
                pressed = m_xbox->GetXButton();
                break;
		    case Y_BUTTON:
                pressed = m_xbox->GetYButton();
                break;
		    case LEFT_BUMPER:
                pressed = m_xbox->GetBumper( frc::GenericHID::kLeftHand );
                break;
		    case RIGHT_BUMPER:
                pressed = m_xbox->GetBumper( frc::GenericHID::kRightHand );
                break;
		    case BACK_BUTTON:
                pressed = m_xbox->GetBackButton();
                break;
		    case START_BUTTON:
                pressed = m_xbox->GetStartButton();
                break;
            case LEFT_STICK_PRESSED:
                pressed = m_xbox->GetStickButton( frc::GenericHID::kLeftHand );
                break;
		    case RIGHT_STICK_PRESSED:
                pressed = m_xbox->GetStickButton( frc::GenericHID::kRightHand );
                break;

            default:
                pressed = false;
                break;
        }

        return pressed; //returns bool for is button pressed
    }  


    int DragonXBox::GetPOVValue() const
    {
        return m_xbox->GetPOV();
    }  


