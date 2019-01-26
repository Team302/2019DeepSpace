// C++ Includes
#include <iostream>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <xmlhw/MotorDefn.h>
//#include <hw/DragonTalon.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

//#include <ctre/phoenix/MotorControl/CAN/TalonSRX.h>

//using namespace  ctre::phoenix::motorcontrol;
//using namespace  ctre::phoenix::motorcontrol::can;

//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a motor XML element and create a DragonTalon from
//              its definition.
//
//        <!-- ====================================================
//             motor usage options
//             ====================================================
//        enum TALON_TYPE
//        {
//            UNKNOWN_TALON_TYPE = -1,
//            MECANUM_FRONT_LEFT,
//            MECANUM_FRONT_LEFT2,
//            MECANUM_FRONT_RIGHT,
//            MECANUM_FRONT_RIGHT2,
//            MECANUM_BACK_LEFT,
//            MECANUM_BACK_LEFT2,
//            MECANUM_BACK_RIGHT,
//            MECANUM_BACK_RIGHT2,
//            TANK_LEFT_MASTER,
//            TANK_LEFT_SLAVE1,
//            TANK_LEFT_SLAVE2,
//            TANK_RIGHT_MASTER,
//            TANK_RIGHT_SLAVE1,
//            TANK_RIGHT_SLAVE2,
//            CLIMBER_MASTER,
//            ELEVATOR_MASTER,
//            ELEVATOR_SLAVE,
//            SIDE_HANGER_MOTOR,
//            ACTIVE_INTAKE_WHEELS,
//            FOURBAR_LIFT_MOTOR,
//            MAX_TALON_TYPES
//        };
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
//DragonTalon* MotorDefn::ParseXML
void MotorDefn::ParseXML
(
    pugi::xml_node      motorNode
)
{
    // initialize the output
    //DragonTalon* talon = nullptr;

    // initialize attributes to default values
    int canID = 0;
    //DragonTalon::TALON_TYPE     motorType = DragonTalon::UNKNOWN_TALON_TYPE;
    bool                        inverted = false;
    bool                        sensorInverted = false;
//    CANTalon::FeedbackDevice  feedbackDevice = CANTalon::QuadEncoder;
    //TODO:: make sure enum matches defines in dtd
    //FeedbackDevice              feedbackDevice = QuadEncoder;
    int                         countsPerRev = 0;
    float                       gearRatio = 1;
    bool                        brakeMode = false;
    int                         slaveTo = -1;
//    int                       currentLimit = 0;
    int                         peakCurrentDuration = 0;
    int                         continuousCurrentLimit = 0;
    int                         peakCurrentLimit = 0;
    bool                        enableCurrentLimit = false;


    bool hasError = false;

    for (pugi::xml_attribute attr = motorNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "usage" ) == 0 )
        {
            int iVal = attr.as_int();
            /*switch ( iVal )
            {
                case DragonTalon::MECANUM_FRONT_LEFT:
                    motorType = DragonTalon::MECANUM_FRONT_LEFT;
                    break;

                case DragonTalon::MECANUM_FRONT_LEFT2:
                    motorType = DragonTalon::MECANUM_FRONT_LEFT2;
                    break;

                case DragonTalon::MECANUM_FRONT_RIGHT:
                    motorType = DragonTalon::MECANUM_FRONT_RIGHT;
                    break;

                case DragonTalon::MECANUM_FRONT_RIGHT2:
                    motorType = DragonTalon::MECANUM_FRONT_RIGHT2;
                    break;

                case DragonTalon::MECANUM_BACK_LEFT:
                    motorType = DragonTalon::MECANUM_BACK_LEFT;
                    break;

                case DragonTalon::MECANUM_BACK_LEFT2:
                    motorType = DragonTalon::MECANUM_BACK_LEFT2;
                    break;

                case DragonTalon::MECANUM_BACK_RIGHT:
                    motorType = DragonTalon::MECANUM_BACK_RIGHT;
                    break;

                case DragonTalon::MECANUM_BACK_RIGHT2:
                    motorType = DragonTalon::MECANUM_BACK_RIGHT2;
                    break;

                case DragonTalon::TANK_LEFT_MASTER:
                    motorType = DragonTalon::TANK_LEFT_MASTER;
                    break;

                case DragonTalon::TANK_LEFT_SLAVE1:
                    motorType = DragonTalon::TANK_LEFT_SLAVE1;
                    break;

                case DragonTalon::TANK_LEFT_SLAVE2:
                    motorType = DragonTalon::TANK_LEFT_SLAVE2;
                    break;

                case DragonTalon::TANK_RIGHT_MASTER:
                    motorType = DragonTalon::TANK_RIGHT_MASTER;
                    break;

                case DragonTalon::TANK_RIGHT_SLAVE1:
                    motorType = DragonTalon::TANK_RIGHT_SLAVE1;
                    break;

                case DragonTalon::TANK_RIGHT_SLAVE2:
                    motorType = DragonTalon::TANK_RIGHT_SLAVE2;
                    break;

                case DragonTalon::CLIMBER_MASTER:
                    motorType = DragonTalon::CLIMBER_MASTER;
                    break;

                case DragonTalon::ELEVATOR_MASTER:
                    motorType = DragonTalon::ELEVATOR_MASTER;
                    break;

                case DragonTalon::ELEVATOR_SLAVE:
                    motorType = DragonTalon::ELEVATOR_SLAVE;
                    break;

                case DragonTalon::SIDE_HANGER_MOTOR:
                    motorType = DragonTalon::SIDE_HANGER_MOTOR;
                    break;

                case DragonTalon::ACTIVE_INTAKE_WHEELS:
                    motorType = DragonTalon::ACTIVE_INTAKE_WHEELS;
                    break;

                case DragonTalon::FOURBAR_LIFT_MOTOR:
                    motorType = DragonTalon::FOURBAR_LIFT_MOTOR;
                    break;

                case DragonTalon::ACTIVE_INTAKE_SLAVE:
                	motorType = DragonTalon::ACTIVE_INTAKE_SLAVE;
                	break;

                default:
                    printf( "==>>MotorDefn::ParseXML Invalid Motor Type %d \n", iVal );
                    hasError = true;
                    break;
            }*/
        }
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
        else if ( strcmp( attr.name(), "type" ) == 0 )
        {
            if ( strcmp( attr.value(), "cantalon" ) != 0 )
            {
                hasError = true;
            }
        }
        else if ( strcmp( attr.name(), "inverted" ) == 0 )
        {
            inverted = attr.as_bool();
        }
        else if ( strcmp( attr.name(), "sensorInverted" ) == 0 )
        {
            sensorInverted = attr.as_bool();
        }
        else if ( strcmp( attr.name(), "feedbackDevice" ) == 0 )
        {
            int iVal = attr.as_int();
            // Some options are duplicated enum values in the WPILib base, so
            // comment out one so that there isn't more than one case with the same value
            /*switch ( iVal )
            {
                 //commented out in ctre code with note to add back in
                //case None:
                    //feedbackDevice = None;
                    //break;
                
              case QuadEncoder:
                    feedbackDevice = QuadEncoder;
                    break;

                case Analog:
                    feedbackDevice = Analog;
                    break;

                case Tachometer:
                    feedbackDevice = Tachometer;
                    break;

              case PulseWidthEncodedPosition:
                    feedbackDevice = PulseWidthEncodedPosition;
                    break;

                case SensorSum:
                    feedbackDevice = SensorSum;
                    break;

                case SensorDifference:
                    feedbackDevice = SensorDifference;
                    break;

                case RemoteSensor0:
                    feedbackDevice = RemoteSensor0;
                    break;

                case RemoteSensor1:
                    feedbackDevice = RemoteSensor1;
                    break;

                case SoftwareEmulatedSensor:
                    feedbackDevice = SoftwareEmulatedSensor;
                    break;

//                case CTRE_MagEncoder_Absolute:
//                    feedbackDevice = CTRE_MagEncoder_Absolute;
//                    break;

//                case CTRE_MagEncoder_Relative:
//                    feedbackDevice = CTRE_MagEncoder_Relative;
//                    break;

                default:
                    printf( "==>>MotorDefn::ParseXML invalid feedback devide %d \n", iVal );
                    hasError = true;
                    break;
            }*/
        }
        else if ( strcmp( attr.name(), "countsPerRev" ) == 0 )
        {
            countsPerRev = attr.as_int();
        }
        else if ( strcmp( attr.name(), "gearRatio" ) == 0 )
        {
            gearRatio = attr.as_float();
        }

        else if ( strcmp( attr.name(), "brakeMode" ) == 0 )
        {
            brakeMode = attr.as_bool();
        }

        else if ( strcmp( attr.name(), "slaveTo") == 0 )
        {
            slaveTo = attr.as_int();
        }
        else if ( strcmp( attr.name(), "peakCurrentDuration") == 0 )
        {
            peakCurrentDuration = attr.as_int();
        }
        else if ( strcmp( attr.name(), "continuousCurrentLimit") == 0 )
        {
            continuousCurrentLimit = attr.as_int();
        }
        else if ( strcmp( attr.name(), "peakCurrentLimit") == 0 )
        {
            peakCurrentLimit = attr.as_int();
        }
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
        //talon = new DragonTalon( motorType, canID, countsPerRev, gearRatio );
        //talon->SetInverted( inverted );
        //talon->SetSensorPhase(sensorInverted );
        //talon->ConfigSelectedFeedbackSensor( feedbackDevice, 0, 0 );  // TODO: 2 new parameters should get set from XML
        if ( brakeMode )
        {
            //talon->SetNeutralMode( NeutralMode::Brake );
        }
        else
        {
            //talon->SetNeutralMode( NeutralMode::Coast );
        }
        if ( slaveTo > -1 )
        {
            //talon->SetAsSlave( slaveTo );
        }

        //talon->EnableCurrentLimit( enableCurrentLimit );
        if ( enableCurrentLimit )
        {
            //talon->ConfigPeakCurrentDuration( peakCurrentDuration, 0 );
            //talon->ConfigContinuousCurrentLimit( continuousCurrentLimit, 0 );
            //talon->ConfigPeakCurrentLimit( peakCurrentLimit, 0 );
        }
    }
    //return talon;
}
