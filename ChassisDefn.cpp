// --------------------------------------------------------------------------------------------
// ChassisDefn.cpp
// --------------------------------------------------------------------------------------------
//
// Description: Create a chassis from an XML definition
//
// <!ELEMENT chassis (motor*) >
// <!ATTLIST chassis
//           type              ( 0 | 1 | 2  ) "0"
//           wheelDiameter     CDATA #REQUIRED
//           wheelBase         CDATA #REQUIRED
//           track             CDATA #REQUIRED
// >
//
// type matches CHASSIS_TYPE enum found in ChassisFactory.h
//
// Wheel Base is front-back distance between wheel centers
//
// Track is the distance between wheels on an "axle"
//
// --------------------------------------------------------------------------------------------

// C++ includes
//#include <subsys/ChassisFactory.h>
#include <iostream>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team302 includes
//#include <subsys/IChassis.h>
//#include <hw/DragonTalon.h>
#include <xmlhw/ChassisDefn.h>
#include <xmlhw/MotorDefn.h>

// Third Party includes
#include <pugixml/pugixml.hpp>


using namespace frc;


//--------------------------------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a Chassis XML element and create an IChassis from its definition.
// Returns:     IChassis*        	chassis (or nullptr if XML is ill-formed)
//--------------------------------------------------------------------------------------------
//IChassis* ChassisDefn::ParseXML
void ChassisDefn::ParseXML
(
	pugi::xml_node      chassisNode
)
{
    //IChassis* chassis = nullptr;
    //ChassisFactory::CHASSIS_TYPE type = ChassisFactory::UNKNOWN_CHASSIS;
    float wheelDiameter	= 0.0;
    float wheelBase 	= 0.0;
    float track 		= 0.0;
    bool hasError 		= false;

    //--------------------------------------------------------------------------------------------
    // process attributes
    //--------------------------------------------------------------------------------------------
    for (pugi::xml_attribute attr = chassisNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "type" ) == 0 )
        {
        	int iVal = attr.as_int();
        	switch ( iVal )
        	{
        		//case ChassisFactory::TANK_CHASSIS:
        			//type = ChassisFactory::TANK_CHASSIS;
        			break;

        		//case ChassisFactory::MECANUM_CHASSIS:
        			//type = ChassisFactory::MECANUM_CHASSIS;
        			break;

        		default:
        			printf( "==>> unknown chassis type %s \n ", attr.value() );
        			hasError = true;
        			break;
        	}
        }
        else if ( strcmp( attr.name(), "wheelDiameter" ) == 0 )
        {
        	wheelDiameter = attr.as_float();
        }
        else if ( strcmp( attr.name(), "wheelBase" ) == 0 )
        {
        	wheelBase = attr.as_float();
        }
        else if ( strcmp( attr.name(), "track" ) == 0 )
        {
        	track = attr.as_float();
        }
        else
        {
        	printf( "==>> chassis: invalid attribute %s \n", attr.name() );
            hasError = true;
        }
    }

    //--------------------------------------------------------------------------------------------
    // Process child element nodes
    //--------------------------------------------------------------------------------------------
    //std::vector<DragonTalon*> motors;
    for (pugi::xml_node child = chassisNode.first_child(); child; child = child.next_sibling())
    {
    	if ( strcmp( child.name(), "motor") == 0 )
    	{
    		//motors.emplace_back( MotorDefn::ParseXML( child ) );
    	}
    	else
    	{
    		printf( "==>> chassis unknown child %s \n", child.name() );
    	}
    }


    //--------------------------------------------------------------------------------------------
    // create chassis instance
    //--------------------------------------------------------------------------------------------
    if ( !hasError )
    {
        //ChassisFactory* factory =  ChassisFactory::GetChassisFactory();
        //factory->CreateChassis( type, wheelDiameter, wheelBase, track, motors );
    }
    //return chassis;
}

