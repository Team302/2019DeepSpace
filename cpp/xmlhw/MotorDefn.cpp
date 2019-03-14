// C++ Includes
#include <iostream>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <xmlhw/MotorDefn.h>
#include <hw/DragonTalon.h>
#include <hw/DragonSparkMax.h>
#include <hw/DragonMotorControllerFactory.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

#include <ctre/phoenix/MotorControl/CAN/TalonSRX.h>
#include <ctre/phoenix/MotorControl/FeedbackDevice.h>
#include <rev/CANSparkMax.h>


//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a motor XML element and create a DragonTalon from
//              its definition.
//
//        <!-- ====================================================
//             motor usage options
//             ====================================================
//
//		enum TALON_TYPE
//		{
//			UNKNOWN_TALON_TYPE = -1,
//			FRONT_LEFT_DRIVE,
//			MIDDLE_LEFT_DRIVE,
//			BACK_LEFT_DRIVE,
//			FRONT_RIGHT_DRIVE,
//			MIDDLE_RIGHT_DRIVE,
//			BACK_RIGHT_DRIVE,
//			ARM_MASTER,
//			ARM_SLAVE,
//			ARM_EXTENSION,
//			WRIST,
//			INTAKE,
//			ELEVATOR_WINCH,
//			ELEVATOR_DRIVE,
//			MAX_TALON_TYPES
//		};
//
//
//
//    ====================================================
//    motor sensor types
//    ====================================================
//        enum TALON_SENSOR_TYPE
//        {
//            NO_SENSOR = -1,
//            QUAD_ENCODER,
//            UNKNOWN_SENSOR,
//            ANALOG_POT,
//            ANALOG_ENCODER,
//            ENCODER_RISING,
//            ENCODER_FALLING,
//            CTRE_MAG_ENCODER_RELATIVE,
//            CTRE_MAG_ENCODER_ABSOLUTE,
//            PULSE_WIDTH,
//            MAX_SENSOR_TYPES
//        };
//    ==================================================== -->
//<!ELEMENT motor EMPTY>
//<!ATTLIST motor
//          usage             (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
//                              10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 ) "0"
//          canId             (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
//                              10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
//                              20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 |
//                              30 | 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 |
//                              40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 | 48 | 49 |
//                              50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 |
//                              60 | 61 | 62 ) "0"
//          type              CDATA #FIXED "cantalon"
//          inverted          ( true | false ) "false"
//          sensorInverted    ( true | false ) "false"
//          feedbackDevice    ( -1 | 0  |  2 |  3 |  4 |  5 |  6 |  7 |  8 ) "-1"
//          countsPerRev      CDATA "0"
//          gearRatio         CDATA "1"
//          brakeMode         ( true | false ) "false"
//          slaveTo           CDATA "-1"
//          currentLimiting   CDATA "0"
//>
//
// Returns:     DragonTalon*        motor controller (or nullptr if XML
//                                  is ill-formed
//-----------------------------------------------------------------------
IDragonMotorController* MotorDefn::ParseXML
(
    pugi::xml_node      motorNode
)
{
    // initialize the output
    IDragonMotorController* controller = nullptr;

    // initialize attributes to default values
    int canID = 0;
	int pdpID = -1;
    IDragonMotorController::TALON_TYPE     usage = IDragonMotorController::TALON_TYPE::UNKNOWN_TALON_TYPE;
    bool inverted = false;
    bool sensorInverted = false;
    ctre::phoenix::motorcontrol::FeedbackDevice  feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder;
    //TODO:: make sure enum matches defines in dtd
    int countsPerRev = 0;
    float gearRatio = 1;
    bool brakeMode = false;
    int slaveTo = -1;
    int currentLimit = 0;
    int peakCurrentDuration = 0;
    int continuousCurrentLimit = 0;
    int peakCurrentLimit = 0;
    bool enableCurrentLimit = false;

    DragonMotorControllerFactory::MOTOR_TYPE mtype = DragonMotorControllerFactory::MOTOR_TYPE::TALONSRX; 


    bool hasError = false;

    for (pugi::xml_attribute attr = motorNode.first_attribute(); attr; attr = attr.next_attribute())
    {
		
		//		enum TALON_TYPE
		//		{
		//			UNKNOWN_TALON_TYPE = -1,
		//			FRONT_LEFT_DRIVE,
		//			MIDDLE_LEFT_DRIVE,
		//			BACK_LEFT_DRIVE,
		//			FRONT_RIGHT_DRIVE,
		//			MIDDLE_RIGHT_DRIVE,
		//			BACK_RIGHT_DRIVE,
		//			ARM_MASTER,
		//			ARM_SLAVE,
		//			ARM_EXTENSION,
		//			WRIST,
		//			INTAKE,
		//			ELEVATOR_WINCH,
		//			ELEVATOR_DRIVE,
		//			MAX_TALON_TYPES
		//		};		
        if ( strcmp( attr.name(), "usage" ) == 0 )
        {
            auto usageStr = attr.value();
            if ( strcmp( usageStr, "FRONT_LEFT_DRIVE") == 0 )
            {
                usage = IDragonMotorController::TALON_TYPE::FRONT_LEFT_DRIVE;
            }
            else if ( strcmp( usageStr, "MIDDLE_LEFT_DRIVE") == 0 )
            {
                usage = IDragonMotorController::TALON_TYPE::MIDDLE_LEFT_DRIVE;
            }
            else if ( strcmp( usageStr, "BACK_LEFT_DRIVE") == 0 )
            {
                usage = IDragonMotorController::TALON_TYPE::BACK_LEFT_DRIVE;
            }            
            else if ( strcmp( usageStr, "FRONT_RIGHT_DRIVE") == 0 )
            {
                usage = IDragonMotorController::TALON_TYPE::FRONT_RIGHT_DRIVE;
            }
            else if ( strcmp( usageStr, "MIDDLE_RIGHT_DRIVE") == 0 )
            {
                usage = IDragonMotorController::TALON_TYPE::MIDDLE_RIGHT_DRIVE;
            }
            else if ( strcmp( usageStr, "BACK_RIGHT_DRIVE") == 0 )
            {
                usage = IDragonMotorController::TALON_TYPE::BACK_RIGHT_DRIVE;
            }
            else if ( strcmp( usageStr, "ARM_MASTER") == 0 )
            {
                usage = IDragonMotorController::TALON_TYPE::ARM_MASTER;
            }            
            else if ( strcmp( usageStr, "ARM_SLAVE") == 0 )
            {
                usage = IDragonMotorController::TALON_TYPE::ARM_SLAVE;
            }
            else if ( strcmp( usageStr, "ARM_EXTENSION") == 0 )
            {
                usage = IDragonMotorController::TALON_TYPE::ARM_EXTENSION;
            }
            else if ( strcmp( usageStr, "WRIST") == 0 )
            {
                usage = IDragonMotorController::TALON_TYPE::WRIST;
            }            
			else if ( strcmp( usageStr, "INTAKE") == 0 )
            {
                usage = IDragonMotorController::TALON_TYPE::INTAKE;
            }
            else if ( strcmp( usageStr, "ELEVATOR_WINCH") == 0 )
            {
                usage = IDragonMotorController::TALON_TYPE::ELEVATOR_WINCH;
            }
            else if ( strcmp( usageStr, "ELEVATOR_DRIVE") == 0 )
            {
                usage = IDragonMotorController::TALON_TYPE::ELEVATOR_DRIVE;
            }
            else if ( strcmp( usageStr, "HATCH_MECH_MOTOR" ) == 0 ) 
            {
                usage = IDragonMotorController::TALON_TYPE::HATCH_MECH_MOTOR;
            }
            else
            {
                printf( "==>>MotorDefn::ParseXML Invalid Motor Type %s \n", usageStr );
                hasError = true;
            }
        }
		// CAN ID 0 thru 62 are valid
        else if ( strcmp( attr.name(), "canId" ) == 0 )
        {
            int iVal = attr.as_int();
            if ( iVal > -1 && iVal < 63 )
            {
                canID = attr.as_int();
            }
            else
            {
                printf( "==>> MotorDefn::ParseXML invalid CAN ID %d \n", iVal );
                hasError = true;
            }
        }
		// PDP ID 0 thru 15 are valid
        else if ( strcmp( attr.name(), "pdpID" ) == 0 )
        {
            int iVal = attr.as_int();
            if ( iVal > -1 && iVal < 16 )
            {
                pdpID = attr.as_int();
            }
            else
            {
                printf( "==>> MotorDefn::ParseXML invalid PDP ID %d \n", iVal );
                hasError = true;
            }
        }
		// type:  cantalon, sparkmax_brushless and sparkmax_brushed are valid
        else if ( strcmp( attr.name(), "type" ) == 0 )
        {
            if ( strcmp( attr.value(), "cantalon") == 0 )
            {
                mtype = DragonMotorControllerFactory::MOTOR_TYPE::TALONSRX;
            }
            else if ( strcmp( attr.value(), "sparkmax_brushless") == 0 )
            {
                mtype = DragonMotorControllerFactory::MOTOR_TYPE::BRUSHLESS_SPARK_MAX;
            }
            else if ( strcmp( attr.value(), "sparkmax_brushed") == 0 )
            {
                mtype = DragonMotorControllerFactory::MOTOR_TYPE::BRUSHED_SPARK_MAX;
            }
            else
            {
                printf( "Invalid motor type %s \n", attr.value() );
                hasError = true;
            }
        }
		// inverted
        else if ( strcmp( attr.name(), "inverted" ) == 0 )
        {
            inverted = attr.as_bool();
        }
		// sensor inverted
        else if ( strcmp( attr.name(), "sensorInverted" ) == 0 )
        {
            sensorInverted = attr.as_bool();
        }
		// feedback device (only used by cantalon)
		//        enum TALON_SENSOR_TYPE
		//        {
		//            NO_SENSOR = -1,
		//            QUAD_ENCODER,
		//            UNKNOWN_SENSOR,
		//            ANALOG_POT,
		//            ANALOG_ENCODER,
		//            ENCODER_RISING,
		//            ENCODER_FALLING,
		//            CTRE_MAG_ENCODER_RELATIVE,
		//            CTRE_MAG_ENCODER_ABSOLUTE,
		//            PULSE_WIDTH,
		//            MAX_SENSOR_TYPES
		//        };        
		else if ( strcmp( attr.name(), "feedbackDevice" ) == 0 )
        {
            int iVal = attr.as_int();
            // Some options are duplicated enum values in the WPILib base, so
            // comment out one so that there isn't more than one case with the same value
            switch ( iVal )
            {
                 //commented out in ctre code with note to add back in
                //case None:
                    //feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::None;
                    //break;
                
              case QuadEncoder:
                    feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder;
                    break;

                case Analog:
                    feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::Analog;
                    break;

                case Tachometer:
                    feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::Tachometer;
                    break;

              case PulseWidthEncodedPosition:
                    feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::PulseWidthEncodedPosition;
                    break;

                case SensorSum:
                    feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::SensorSum;
                    break;

                case SensorDifference:
                    feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::SensorDifference;
                    break;

                case RemoteSensor0:
                    feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::RemoteSensor0;
                    break;

                case RemoteSensor1:
                    feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::RemoteSensor1;
                    break;

                case SoftwareEmulatedSensor:
                    feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::SoftwareEmulatedSensor;
                    break;

//                case CTRE_MagEncoder_Absolute:
//                    feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Absolute;
//                    break;

//                case CTRE_MagEncoder_Relative:
//                    feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative;
//                    break;

                default:
                    printf( "==>>MotorDefn::ParseXML invalid feedback devide %d \n", iVal );
                    hasError = true;
                    break;
            }
        }
		// counts per revolution
        else if ( strcmp( attr.name(), "countsPerRev" ) == 0 )
        {
            countsPerRev = attr.as_int();
        }
		// gear ratio
        else if ( strcmp( attr.name(), "gearRatio" ) == 0 )
        {
            gearRatio = attr.as_float();
        }

		// brake mode (or coast)
        else if ( strcmp( attr.name(), "brakeMode" ) == 0 )
        {
            brakeMode = attr.as_bool();
        }
		// slaveto (existing CAN id of the master motor)
        else if ( strcmp( attr.name(), "slaveTo") == 0 )
        {
            slaveTo = attr.as_int();
        }
		// peak current duration (cantalon)
        else if ( strcmp( attr.name(), "peakCurrentDuration") == 0 )
        {
            peakCurrentDuration = attr.as_int();
        }
		// continuous current duration (cantalon)
        else if ( strcmp( attr.name(), "continuousCurrentLimit") == 0 )
        {
            continuousCurrentLimit = attr.as_int();
        }
		// peak current limit (cantalon)
        else if ( strcmp( attr.name(), "peakCurrentLimit") == 0 )
        {
            peakCurrentLimit = attr.as_int();
        }
		// enable current limiting
        else if ( strcmp( attr.name(), "currentLimiting") == 0 )
        {
            enableCurrentLimit = attr.as_bool();
        }
        else
        {
            printf( "==>>MotorDefn::ParseXML invalid attribute %s \n", attr.name() );
            hasError = true;
        }
    }

    if ( !hasError )
    {
		pdpID = ( pdpID < 0 ) ? pdpID = canID : pdpID;
        controller = DragonMotorControllerFactory::GetInstance()->CreateMotorController( mtype,
                                                                                         canID,
                                                                                         pdpID,
                                                                                         usage,
                                                                                         inverted,
                                                                                         sensorInverted,
                                                                                         feedbackDevice,
                                                                                         countsPerRev,
                                                                                         gearRatio,
                                                                                         brakeMode,
                                                                                         slaveTo,
                                                                                         currentLimit,
                                                                                         peakCurrentLimit,
                                                                                         peakCurrentDuration,
                                                                                         peakCurrentLimit,
                                                                                         enableCurrentLimit );
    }
    return controller;
}
