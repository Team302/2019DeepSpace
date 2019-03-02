/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "teleop/TeleopControl.h"
// FRC Includes
#include <frc/GenericHID.h>
#include <frc/DriverStation.h>
// Dragon Stuff
#include <controllers/IDragonGamePad.h>
#include <controllers/DragonXBox.h>
//Garbage
#include <cstdio>

using namespace frc;

//----------------------------------------------------------------------------------
// Method:      GetInstance
// Description: If there isn't an instance of this class, it will create one.  The
//              single class instance will be returned.
// Returns:     OperatorInterface*  instance of this class
//----------------------------------------------------------------------------------
TeleopControl* TeleopControl::m_instance = nullptr; // initialize the instance variable to nullptr
TeleopControl* TeleopControl::GetInstance()
{
    if ( TeleopControl::m_instance == nullptr )
    {
        TeleopControl::m_instance = new TeleopControl();
    }
    return TeleopControl::m_instance;
}
//----------------------------------------------------------------------------------
// Method:      OperatorInterface <<constructor>>
// Description: This will construct and initialize the object.
//              It maps the functions to the buttons/axis.
//---------------------------------------------------------------------------------
TeleopControl::TeleopControl() : m_axisIDs(),
								 m_buttonIDs(),
								 m_controllerIndex(),
								 m_controllers(),
								 m_count( 0 )
{
	DriverStation* ds = &DriverStation::GetInstance();
	for ( int inx=0; inx<DriverStation::kJoystickPorts; ++inx )
	{
		m_controllers[inx] = nullptr;
		if ( ds->GetJoystickIsXbox( inx ) )
		{
			m_controllers[inx] = new DragonXBox( inx );
		}
		// else if ( ds->GetJoystickType( inx ) == GenericHID::kHIDJoystick )
		// {
		// 	m_controllers[inx] = new DragonStick( inx );
		// }
	}


    // Initialize the items to not defined
    for ( int inx=0; inx<m_maxFunctions; ++inx )
    {
        m_axisIDs[inx]    		= IDragonGamePad::AXIS_IDENTIFIER::UNDEFINED_AXIS;
        m_buttonIDs[inx]  		= IDragonGamePad::BUTTON_IDENTIFIER::UNDEFINED_BUTTON;
        m_controllerIndex[inx]  = -1;
    }

//	for ( int inx=0; inx<6; ++inx )
//	{
//		printf( "==>> joystick %d type %d \n", inx, ds->GetJoystickType( inx ) );
//	}

    if ( m_controllers[0] != nullptr && ds->GetJoystickIsXbox(0) )
    {
    	if ( ds->GetJoystickIsXbox(0) )
    	{
			m_controllerIndex[ TANK_DRIVE_LEFT_CONTROL ] 	= 0;
			m_axisIDs[ TANK_DRIVE_LEFT_CONTROL ]    		= IDragonGamePad::AXIS_IDENTIFIER::LEFT_JOYSTICK_Y;     //XBOX_Y_AXIS_LEFT_JOYSTICK;
			m_controllerIndex[ TANK_DRIVE_RIGHT_CONTROL ] 	= 0;
			m_axisIDs[ TANK_DRIVE_RIGHT_CONTROL ]   		= IDragonGamePad::AXIS_IDENTIFIER::RIGHT_JOYSTICK_Y;    //XBOX_Y_AXIS_RIGHT_JOYSTICK;

			m_controllerIndex[ ARCADE_DRIVE_THROTTLE ] 		= 0;
			m_axisIDs[ ARCADE_DRIVE_THROTTLE ]      		= IDragonGamePad::AXIS_IDENTIFIER::LEFT_JOYSTICK_Y;     // XBOX_Y_AXIS_LEFT_JOYSTICK;
			m_controllerIndex[ ARCADE_DRIVE_STEER ] 		= 0;
			m_axisIDs[ ARCADE_DRIVE_STEER ]         		= IDragonGamePad::AXIS_IDENTIFIER::RIGHT_JOYSTICK_X;    // XBOX_X_AXIS_RIGHT_JOYSTICK;

			m_controllerIndex[ ROBOT_X_MAGNITUDE ]			= 0;
			m_axisIDs[ ROBOT_X_MAGNITUDE ]    				= IDragonGamePad::AXIS_IDENTIFIER::LEFT_JOYSTICK_X;     // XBOX_X_AXIS_LEFT_JOYSTICK;

			m_controllerIndex[ ROBOT_Y_MAGNITUDE ]			= 0;
			m_axisIDs[ ROBOT_Y_MAGNITUDE ]    				= IDragonGamePad::AXIS_IDENTIFIER::LEFT_JOYSTICK_Y;     // XBOX_Y_AXIS_LEFT_JOYSTICK;

			m_controllerIndex[ ROBOT_ROTATION_MAGNITUDE ]	= 0;
			m_axisIDs[ ROBOT_ROTATION_MAGNITUDE ]    		= IDragonGamePad::AXIS_IDENTIFIER::RIGHT_JOYSTICK_X;    // XBOX_X_AXIS_RIGHT_JOYSTICK;

			m_controllerIndex[ DRIVE_BOOST_MODE ]           = 0;
			m_buttonIDs[ DRIVE_BOOST_MODE ]                 = IDragonGamePad::BUTTON_IDENTIFIER::RIGHT_BUMPER;

            m_controllerIndex[ ALLOW_CLIMB_DRIVE ]          = 0;
            m_buttonIDs[ ALLOW_CLIMB_DRIVE ]                = IDragonGamePad::BUTTON_IDENTIFIER::A_BUTTON;

            m_controllerIndex[ CLIMB_DRIVE ]                = 0;
            m_axisIDs[ CLIMB_DRIVE ]                        = IDragonGamePad::AXIS_IDENTIFIER::LEFT_JOYSTICK_Y;

            m_controllerIndex[ DROP_BUDDY_CLIMB ]           = 0;
            m_buttonIDs[ DROP_BUDDY_CLIMB ]                 = IDragonGamePad::BUTTON_IDENTIFIER::RIGHT_BUMPER;
    	}
		// else if ( ds->GetJoystickType( 0 ) == GenericHID::kHIDJoystick )
		// {
		// 	printf( "need to map DragonStick functions 0 \n" );
		// }
    }
    else
    {
    	printf( "TeleopControl::TeleopControl(): no controller plugged into port 0 \n" );
    }

    if ( m_controllers[1] != nullptr && ds->GetJoystickIsXbox(1) )
    {
        // cubes
        m_controllerIndex[ DEPLOY ]                         = 1;
        m_buttonIDs[ DEPLOY ]                               = IDragonGamePad::BUTTON_IDENTIFIER::RIGHT_BUMPER;      // Right Bumper deploys

        m_controllerIndex[ GOTO_ROCKET_MED ]                = 1;
        m_buttonIDs[ GOTO_ROCKET_MED ]                      = IDragonGamePad::BUTTON_IDENTIFIER::POV_0;             // up on dpad goes to med rocket height

        m_controllerIndex[ GOTO_CARGOSHIP ]                 = 1;
        m_buttonIDs[ GOTO_CARGOSHIP ]						= IDragonGamePad::BUTTON_IDENTIFIER::POV_180;           // down on dpad goes to cargoship

        m_controllerIndex[ GOTO_ROCKET_LOW ]                = 1;
        m_buttonIDs[ GOTO_ROCKET_LOW ]                      = IDragonGamePad::BUTTON_IDENTIFIER::POV_270;            // left on dpad goes to low rocket height

        m_controllerIndex[ GOTO_ROCKET_HIGH ]               = 1;
        m_buttonIDs[ GOTO_ROCKET_HIGH ]                     = IDragonGamePad::BUTTON_IDENTIFIER::POV_90;            // right on dpad goes to high rocket height

        m_controllerIndex[ GOTO_FLOOR ]                     = 1;
        m_buttonIDs[ GOTO_FLOOR ]                           = IDragonGamePad::BUTTON_IDENTIFIER::A_BUTTON;          // 'A' button goes to floor

        m_controllerIndex[ GOTO_HUMAN_PLAYER ]              = 1;
        m_buttonIDs[ GOTO_HUMAN_PLAYER ]                    = IDragonGamePad::BUTTON_IDENTIFIER::X_BUTTON;          // 'X' button goes to human player

        m_controllerIndex[ GAMEPIECE_FLIP ]                 = 1;
        m_buttonIDs[ GAMEPIECE_FLIP ]                         = IDragonGamePad::BUTTON_IDENTIFIER::Y_BUTTON;        // 'Y' button flips current gamepiece

        m_controllerIndex[ ROBOT_FLIP ]                     = 1;
        m_buttonIDs[ ROBOT_FLIP ]                             = IDragonGamePad::BUTTON_IDENTIFIER::B_BUTTON;       // 'B' button flips active side of robot

        m_controllerIndex[ INTAKE ]                         = 1;
        m_axisIDs[ INTAKE ]                                 = IDragonGamePad::AXIS_IDENTIFIER::RIGHT_TRIGGER;      // Right trigger intakes  

        m_controllerIndex[ OUTAKE ]                         = 1;
        m_axisIDs[ OUTAKE ]                                 = IDragonGamePad::AXIS_IDENTIFIER::LEFT_TRIGGER;       // Left trigger outakes

        m_controllerIndex[ ROTATE_ARM ]                     = 1;
        m_axisIDs[ ROTATE_ARM ]                             = IDragonGamePad::AXIS_IDENTIFIER::LEFT_JOYSTICK_Y;    // left Y axis rotates arm

        m_controllerIndex[ EXTEND_ARM ]                     = 1;
        m_axisIDs[ EXTEND_ARM ]                             = IDragonGamePad::AXIS_IDENTIFIER::LEFT_JOYSTICK_X;    // left X axis extends/retracts arm

        m_controllerIndex[ ROTATE_WRIST ]                   = 1;
        m_axisIDs[ ROTATE_WRIST ]                           = IDragonGamePad::AXIS_IDENTIFIER::RIGHT_JOYSTICK_Y;   // right Y axis rotates wrist

        m_controllerIndex[ CLIMB_ELEVATOR_UP ]              = 1;
        m_buttonIDs[ CLIMB_ELEVATOR_UP ]                    = IDragonGamePad::BUTTON_IDENTIFIER::SELECT_BUTTON;

        m_controllerIndex[ CLIMB_ELEVATOR_DOWN ]            = 1;
        m_buttonIDs[ CLIMB_ELEVATOR_DOWN ]                  = IDragonGamePad::BUTTON_IDENTIFIER::START_BUTTON;
    }
    else
    {
    	printf( "TeleopControl::TeleopControl(): no controller plugged into port 1 \n" );
    }
}


//------------------------------------------------------------------
// Method:      SetAxisScaleFactor
// Description: Allow the range of values to be set smaller than
//              -1.0 to 1.0.  By providing a scale factor between 0.0
//              and 1.0, the range can be made smaller.  If a value
//              outside the range is provided, then the value will
//              be set to the closest bounding value (e.g. 1.5 will
//              become 1.0)
// Returns:     void
//------------------------------------------------------------------
void TeleopControl::SetAxisScaleFactor
(
    TeleopControl::FUNCTION_IDENTIFIER  	function,      // <I> - function that will update an axis
    float                                   scaleFactor    // <I> - scale factor used to limit the range
)
{
	int ctlIndex = m_controllerIndex[ function];
	IDragonGamePad::AXIS_IDENTIFIER axis = m_axisIDs[ function ];
    if ( ctlIndex > -1 && axis != IDragonGamePad::AXIS_IDENTIFIER::UNDEFINED_AXIS  )
    {
    	if (m_controllers[ ctlIndex ] != nullptr)
    	{
    		m_controllers[ ctlIndex ]->SetAxisScale( axis,scaleFactor);
    	}
    }
}

//------------------------------------------------------------------
// Method:      SetAxisProfile
// Description: Sets the axis profile for the specifed axis
// Returns:     void
//------------------------------------------------------------------
void TeleopControl::SetAxisProfile
(
    TeleopControl::FUNCTION_IDENTIFIER      function,       // <I> - function that will update an axis
    IDragonGamePad::AXIS_PROFILE       		profile         // <I> - profile to use
)
{
	int ctlIndex = m_controllerIndex[ function];
	IDragonGamePad::AXIS_IDENTIFIER axis = m_axisIDs[ function ];
    if ( ctlIndex > -1 && axis != IDragonGamePad::AXIS_IDENTIFIER::UNDEFINED_AXIS  )
    {
    	if (m_controllers[ ctlIndex ] != nullptr)
    	{
    		m_controllers[ ctlIndex ]->SetAxisProfile( axis,profile);
    	}
    }
}

//------------------------------------------------------------------
// Method:      GetAxisValue
// Description: Reads the joystick axis, removes any deadband (small
//              value) and then scales as requested.
// Returns:     float   -  scaled axis value
//------------------------------------------------------------------
float TeleopControl::GetAxisValue
(
    TeleopControl::FUNCTION_IDENTIFIER  function    // <I> - function that whose axis will be read
) const
{
    float value = 0.0;
	int ctlIndex = m_controllerIndex[ function];
	IDragonGamePad::AXIS_IDENTIFIER axis = m_axisIDs[ function ];
    if ( ctlIndex > -1 && axis != IDragonGamePad::AXIS_IDENTIFIER::UNDEFINED_AXIS  )
    {
    	if (m_controllers[ ctlIndex ] != nullptr)
    	{
    		value = m_controllers[ ctlIndex ]->GetAxisValue( axis );
    	}
    }
/*
    if ( function == TeleopControl::RAISE_4BAR )
    {
        if ( m_count == 0  )
        {
//            printf( "==>> checking axis function %d \n", function );
//            printf( "==>> controller %d axis %d value %g \n", m_controllerIndex[ function ], m_axisIDs[ function ], value );
        }
        m_count++;
        if ( m_count > 100 )
        {
            m_count = 0;
        }
    }*/

    //	SmartDashboard::PutNumber( "Axis ID ", function );
//	SmartDashboard::PutNumber( "Axis Value ", value );
    return value;
}

//------------------------------------------------------------------
// Method:      IsButtonPressed
// Description: Reads the button value.  Also allows POV, bumpers,
//              and triggers to be treated as buttons.
// Returns:     bool   -  scaled axis value
//------------------------------------------------------------------
bool TeleopControl::IsButtonPressed
(
    TeleopControl::FUNCTION_IDENTIFIER  function    // <I> - function that whose button will be read
) const
{
    bool isSelected = false;
	int ctlIndex = m_controllerIndex[ function];
	IDragonGamePad::BUTTON_IDENTIFIER btn = m_buttonIDs[ function ];
    if ( ctlIndex > -1 && btn != IDragonGamePad::BUTTON_IDENTIFIER::UNDEFINED_BUTTON  )
    {
    	if (m_controllers[ ctlIndex ] != nullptr)
    	{
    		isSelected = m_controllers[ ctlIndex ]->IsButtonPressed( btn );
    	}
    }


/*    if ( function == TeleopControl::RAISE_4BAR )
    {
        if ( m_count == 0  )
        {
//            printf( "==>> checking button function %d \n", function );
//            printf( "==>> controller %d button %d pressed %s \n", m_controllerIndex[ function ], m_buttonIDs[ function ], isSelected ? "true" : "false" );
        }
        m_count++;
        if ( m_count > 100 )
        {
            m_count = 0;
        }
    }*/



    return isSelected;
}

