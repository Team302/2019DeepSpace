/*
 * MechanismDefn.cpp
 */

// C++ Includes
#include <iostream>

// FRC includes
#include <frc/AnalogInput.h>
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
//#include <subsys/MechanismFactory.h>
//#include <subsys/IMechanism.h>

//#include <xmlhw/AnalogInputDefn.h>
#include <xmlhw/DigitalInputDefn.h>
#include <xmlhw/MotorDefn.h>
//#include <xmlhw/ServoDefn.h>
//#include <xmlhw/SolenoidDefn.h>

//#include <hw/DragonAnalogInput.h>
//#include <hw/DragonDigitalInput.h>
//#include <hw/DragonServo.h>
//#include <hw/DragonSolenoid.h>
//#include <hw/DragonTalon.h>

#include <xmlhw/MechanismDefn.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace frc;


//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a Mechanism XML element and create an IMechanism
//              from its definition.
//
//
//<!-- ====================================================
//        enum MECHANISM_TYPE
//        {
//            UNKNOWN_MECHANISM = -1,
//            GRABBER,
//            LIFT,
//            CLIMBER,
//            SIDE_HANGER,
//            MAX_MECHANISM_TYPES
//        };
//
//
//    ==================================================== -->
//<!ELEMENT mechanism (motor*, analogInput*, digitalInput*, solenoid*, servo* )>
//<!ATTLIST mechanism
//          type              ( 0 | 1 | 2 | 3 ) "0"
//>
//
//
// Returns:     void
//-----------------------------------------------------------------------
void MechanismDefn::ParseXML
(
    pugi::xml_node      mechanismNode
)
{
    // initialize attributes
    //IMechanism::MECHANISM_TYPE type = IMechanism::UNKNOWN_MECHANISM;

    bool hasError       = false;

    // Parse/validate xml
    for (pugi::xml_attribute attr = mechanismNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "type" ) == 0 )
        {
            int iVal = attr.as_int();
            /*switch ( iVal )
            {
                case IMechanism::GRABBER:
                    type = IMechanism::GRABBER;
                    break;

                case IMechanism::LIFT:
                    type = IMechanism::LIFT;
                    break;

                case IMechanism::CLIMBER:
                    type = IMechanism::CLIMBER;
                    break;

                case IMechanism::SIDE_HANGER:
                    type = IMechanism::SIDE_HANGER;
                    break;

                case IMechanism::ACTIVE_GRABBER:
                    type = IMechanism::ACTIVE_GRABBER;
                    break;

                default:
                    printf( "==>> MechanismDefn::ParseXML unknown Mechanism type %s \n ", attr.value() );
                    hasError = true;
                    break;
                
            }*/
        }
        else
        {
            //printf( "==>>MechanismDefn::ParseXML invalid attribute %s \n", attr.name() );
            hasError = true;
        }
    }

    // initialize the subobjects
    //DragonTalonVector motors;
    //DragonAnalogInputVector analogIns;
    //DragonDigitalInputVector digitals;
    //DragonSolenoidVector solenoids;
    //DragonServoVector servos;

    // Parse/validate subobject xml
    //for (pugi::xml_node child = mechanismNode.first_child(); child; child = child.next_sibling())
    {
        /*    	printf(child.name());
            	printf("\n");
        if ( strcmp( child.name(), "motor") == 0 )
        {
            motors.emplace_back( MotorDefn::ParseXML( child ) );
        }
        else if ( strcmp( child.name(), "analogInput") == 0 )
        {
            analogIns.emplace_back( AnalogInputDefn::ParseXML( child ) );
        }
        else if ( strcmp( child.name(), "digitalInput") == 0 )
        {
            //        	printf("!!!!!!!!!!!!!!!!!!!!!!!1 IM HERE RIGHT NOWWW1!!!JONAH IS HREREE\n");
            digitals.emplace_back( DigitalInputDefn::ParseXML( child ) );
        }
        else if ( strcmp( child.name(), "solenoid") == 0 )
        {
            solenoids.emplace_back( SolenoidDefn::ParseXML( child ) );
        }
        else if ( strcmp( child.name(), "servo") == 0 )
        {
            servos.emplace_back( ServoDefn::ParseXML( child ) );
        }
        else
        {
            printf( "==>> MechanismDefn::ParseXML unknown mechanism child %s \n", child.name() );
        }*/
    }


    // create instance
    /*if ( !hasError )
    {
        MechanismFactory* factory =  MechanismFactory::GetMechanismFactory();
        factory->CreateMechanism( type,                     // mechanism type
                                  motors,                   // dragon talons
                                  solenoids,                // dragon solenoids
                                  digitals,                 // dragon digital inputs
                                  analogIns,                // dragon analog inputs
                                  servos );                 // dragon servos
    }*/
}

