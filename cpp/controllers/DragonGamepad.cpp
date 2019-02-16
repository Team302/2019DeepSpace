/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <controllers/DragonGamepad.h>

#include <controllers/axis/IDeadband.h>
#include <controllers/axis/IProfile.h>

#include <controllers/button/DigitalButton.h>
#include <controllers/axis/AnalogAxis.h>
#include <controllers/button/AnalogButton.h>

#include <frc/GenericHID.h>
#include <frc/Joystick.h>

DragonGamepad::DragonGamepad
(
    int port
)  : m_gamepad( new frc::Joystick(port)),
m_axis(),
m_button(),
m_count(),
m_axisScale(),
m_axisInversionFactor(),
m_axisProfile()
{
    //Create Axis objects
    m_axis[GAMEPAD_AXIS_16] = new AnalogAxis(m_gamepad, GAMEPAD_AXIS_16,false);
    m_axis[GAMEPAD_AXIS_17] = new AnalogAxis(m_gamepad, GAMEPAD_AXIS_17,false);
    m_axis[GAMEPAD_DIAL_22] = new AnalogAxis(m_gamepad, GAMEPAD_DIAL_22,false);
    m_axis[GAMEPAD_DIAL_23] = new AnalogAxis(m_gamepad, GAMEPAD_DIAL_23,false);
    m_axis[GAMEPAD_DIAL_24] = new AnalogAxis(m_gamepad, GAMEPAD_DIAL_24,false);
    m_axis[GAMEPAD_DIAL_25] = new AnalogAxis(m_gamepad, GAMEPAD_DIAL_25,false);
    m_axis[GAMEPAD_DIAL_26] = new AnalogAxis(m_gamepad, GAMEPAD_DIAL_26,false);
    m_axis[GAMEPAD_DIAL_27] = new AnalogAxis(m_gamepad, GAMEPAD_DIAL_27,false);
    m_axis[LEFT_ANALOG_BUTTON_AXIS] = new AnalogAxis(m_gamepad, LEFT_BUTTON_AXIS_ID,false );
    m_axis[RIGHT_ANALOG_BUTTON_AXIS] = new AnalogAxis(m_gamepad, RIGHT_BUTTON_AXIS_ID,false);

    //Create Button objects
    m_analogButtons[GAMEPAD_BUTTON_1] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_1_LOWERBAND,BUTTON_1_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_2] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_2_LOWERBAND,BUTTON_2_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_3] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_3_LOWERBAND,BUTTON_3_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_4] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_4_LOWERBAND,BUTTON_4_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_5] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_5_LOWERBAND,BUTTON_5_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_6] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_6_LOWERBAND,BUTTON_6_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_7] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_7_LOWERBAND,BUTTON_7_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_8] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_8_LOWERBAND,BUTTON_8_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_9] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_9_LOWERBAND,BUTTON_9_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_10] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_10_LOWERBAND,BUTTON_10_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_11] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_11_LOWERBAND,BUTTON_11_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_12] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_12_LOWERBAND,BUTTON_12_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_13] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_13_LOWERBAND,BUTTON_13_UPPERBAND);
    //m_analogButtons[GAMEPAD_BIG_RED_BUTTON] = new AnalogButton(m_gamepad, GAMEPAD_BIG_RED_BUTTON,);

    m_button[GAMEPAD_SWITCH_18] = new DigitalButton(m_gamepad, GAMEPAD_SWITCH_18);
    m_button[GAMEPAD_SWITCH_19] = new DigitalButton(m_gamepad, GAMEPAD_SWITCH_19);
    m_button[GAMEPAD_SWITCH_20] = new DigitalButton(m_gamepad, GAMEPAD_SWITCH_20);
    m_button[GAMEPAD_SWITCH_21] = new DigitalButton(m_gamepad, GAMEPAD_SWITCH_21);
    m_button[GAMEPAD_BUTTON_14_UP] = new DigitalButton(m_gamepad, GAMEPAD_BUTTON_14_UP);
    m_button[GAMEPAD_BUTTON_14_DOWN] = new DigitalButton(m_gamepad, GAMEPAD_BUTTON_14_DOWN);
    m_button[GAMEPAD_BUTTON_15_UP] = new DigitalButton(m_gamepad, GAMEPAD_BUTTON_15_UP);
    m_button[GAMEPAD_BUTTON_15_DOWN] = new DigitalButton(m_gamepad, GAMEPAD_BUTTON_15_DOWN);
}

DragonGamepad::~DragonGamepad()
{
    delete m_gamepad;
    m_gamepad = nullptr;
}

float DragonGamepad::GetAxisValue
(
    AXIS_IDENTIFIER axis
) const
{
    float value = 0.0;
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis]->GetAxisValue();
    }
    return value;   
}

bool DragonGamepad::IsButtonPressed
(
    BUTTON_IDENTIFIER button
) const
{
    bool isPressed = false;
    return isPressed;
}

void DragonGamepad::SetAxisDeadband
(
    AXIS_IDENTIFIER axis,
    AXIS_DEADBAND type
)
{
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis]->SetDeadBand( type );
    }        
}

void DragonGamepad::SetAxisProfile
(
    AXIS_IDENTIFIER axis,
    AXIS_PROFILE curve
)
{
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis]->SetAxisProfile( curve );
    }        
}

void DragonGamepad::SetAxisScale
(
    AXIS_IDENTIFIER axis,
    float scaleFactor
)
{
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis]->SetAxisScaleFactor( scaleFactor );
    }        
}

void DragonGamepad::SetButtonMode
(
    BUTTON_IDENTIFIER button,
    BUTTON_MODE mode
) 
{

}

double DragonGamepad::GetRawAxis
(
    AXIS_IDENTIFIER axis
)
{
    double value = 0.0;
    if(axis < MAX_GAMEPAD_AXIS)
    {
        switch(axis)
        {
            case GAMEPAD_AXIS_16:
            value = m_gamepad->GetY(frc::GenericHID::kLeftHand) * m_axisInversionFactor[axis];
            break;

            case GAMEPAD_AXIS_17:
            value = m_gamepad->GetY(frc::GenericHID::kRightHand) * m_axisInversionFactor[axis];
            break;

            case GAMEPAD_DIAL_22:
            value = m_gamepad->GetY(frc::GenericHID::kLeftHand) * m_axisInversionFactor[axis];
            break;

            case GAMEPAD_DIAL_23:
            value = m_gamepad->GetY(frc::GenericHID::kLeftHand) * m_axisInversionFactor[axis];
            break;

            case GAMEPAD_DIAL_24:
            value = m_gamepad->GetY(frc::GenericHID::kLeftHand) * m_axisInversionFactor[axis];
            break; 

            case GAMEPAD_DIAL_25:
            value = m_gamepad->GetY(frc::GenericHID::kLeftHand) * m_axisInversionFactor[axis];
            break;

            case GAMEPAD_DIAL_26:
            value = m_gamepad->GetY(frc::GenericHID::kLeftHand) * m_axisInversionFactor[axis];
            break;

            case GAMEPAD_DIAL_27:
            value = m_gamepad->GetY(frc::GenericHID::kLeftHand) * m_axisInversionFactor[axis];
            break;
        
        if (std::abs(value) < APPLY_STANDARD_DEADBAND)
		{
			value = 0.0;
		}
		else if (std::abs(value) > APPLY_STANDARD_DEADBAND)
		{
			if ( m_axisProfile[axis] == CUBED )
			{
				value = pow( value, 3.0 );
			}
			value = value * m_axisScale[axis];
		}
        
            

        }
    }
    return value;
}

bool DragonGamepad::IsRawButtonPressed
(
    BUTTON_IDENTIFIER button
) 
{
    bool pressed = false;
    if(m_analogButtons[button] != nullptr)
    {
        pressed = m_button[button]->IsButtonPressed();
    }
    return pressed;
}
int DragonGamepad::GetPOVValue
(
)
{
    return 0;
}