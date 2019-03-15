/*
 * MechanismDefn.cpp
 */

// C++ Includes
#include <iostream>
#include <utility>
#include <vector>

// FRC includes
#include <frc/AnalogInput.h>
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <subsys/MechanismFactory.h>
#include <subsys/IMechanism.h>

#include <xmlhw/AnalogInputDefn.h>
#include <xmlhw/DigitalInputDefn.h>
#include <xmlhw/MotorDefn.h>
//#include <xmlhw/ServoDefn.h>  Chris is working on this

#include <hw/DragonAnalogInput.h>
#include <hw/DragonDigitalInput.h>
#include <hw/DragonServo.h>
#include <hw/IDragonMotorController.h>
#include <subsys/IMechanism.h>

#include <xmlhw/MechanismDefn.h>
#include <xmlhw/MechanismDataDefn.h>
#include <xmlhw/PIDDefn.h>

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
//            WRIST,
//            INTAKE,
//            ARM,
//            CLIMBER,
//            MAX_MECHANISM_TYPES
//        };
//
//
//    ==================================================== -->
//<!ELEMENT mechanism (motor*, analogInput*, digitalInput*, servo* )>
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
    IMechanism::MECHANISM_TYPE type = IMechanism::UNKNOWN_MECHANISM;

    bool hasError       = false;

    // Parse/validate xml
    for (pugi::xml_attribute attr = mechanismNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "type" ) == 0 )
        {
            
            int iVal = attr.as_int();
            printf("mech: %d \n", iVal);
            switch ( iVal )
            {
                case IMechanism::WRIST:
                    type = IMechanism::WRIST;
                    break;

                case IMechanism::INTAKE:
                    type = IMechanism::INTAKE;
                    break;

                case IMechanism::ARM:
                    type = IMechanism::ARM;
                    break;

                case IMechanism::CLIMBER:
                    type = IMechanism::CLIMBER;
                    break;

                case IMechanism::HATCH_MANIPULATOR:
                    type = IMechanism::HATCH_MANIPULATOR;
                    break;

                default:
                    printf( "==>> MechanismDefn::ParseXML unknown Mechanism type %s \n ", attr.value() );
                    hasError = true;
                    break;
                
            }
        }
        else
        {
            printf( "==>>MechanismDefn::ParseXML invalid attribute %s \n", attr.name() );
            hasError = true;
        }
    }

    // initialize the subobjects
    IDragonMotorControllerVector motors;
    DragonAnalogInputVector analogIns;
    DragonDigitalInputVector digitals;
    DragonServoVector servos;

    mechParameters parameters;
    std::vector<PIDData*> pidControlVector;

    // Parse/validate subobject xml
    for (pugi::xml_node child = mechanismNode.first_child(); child; child = child.next_sibling())
    {
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
            digitals.emplace_back( DigitalInputDefn::ParseXML( child ) );
        }
        else if ( strcmp( child.name(), "servo") == 0 )
        {
//            servos.emplace_back( ServoDefn::ParseXML( child ) );
        }
        else if ( strcmp( child.name(), "mechanismData") == 0 )
        {
            // Mechanism Data
            parameters.emplace_back( MechanismDataDefn::ParseXML( child ) );
        }
        else if ( strcmp( child.name(), "PID") == 0 )
        {
            pidControlVector.emplace_back( PIDDefn::ParseXML( child ) );
        }
        else
        {
            printf( "==>> MechanismDefn::ParseXML unknown mechanism child %s \n", child.name() );
        }
    }


    // create instance
    if ( !hasError )
    {
        MechanismFactory* factory =  MechanismFactory::GetMechanismFactory();
        factory->CreateMechanism( type,                     // mechanism type
                                  motors,                   // dragon talons
                                  digitals,                 // dragon digital inputs
                                  analogIns,                // dragon analog inputs
                                  servos,                   // dragon servos
                                  parameters,               // mechanism parameters
                                  pidControlVector );       // pid control information
    }
}
