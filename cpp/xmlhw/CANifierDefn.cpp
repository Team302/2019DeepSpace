/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <xmlhw/CANifierDefn.h>

//Third Party includes
#include <pugixml/pugixml.hpp>

//CTRE includes
#include <ctre/Phoenix.h>

using namespace frc;


ctre::phoenix::CANifier* CANifierDefn::ParseXML
(
    pugi::xml_node      canifierNode
)
{
//initialize output
ctre::phoenix::CANifier* canifier = nullptr;
// initialize attributes to default values
	int canID = 0;
    CANifierDefn::USAGE usage = CANifierDefn::USAGE::UNKNOWN_CANIFIER;
	bool hasError = false;

//Parse/validate xml
	for(pugi::xml_attribute attr = canifierNode.first_attribute(); attr; attr = attr.next_attribute() )
	{
		if (strcmp(attr.name(), "canId" ) == 0)
		{
			int iVal = attr.as_int();
            if ( iVal > -1 && iVal < 63 )
            {
                canID = attr.as_int();
            }
            else
            {
                printf( "==>> CANifierDefn::ParseXML invalid CAN ID %d \n", iVal );
                hasError = true;
            }
		}
        else if(strcmp(attr.name(), "usage" ) == 0)
        {
            int iVal = attr.as_int();
            switch(iVal)
            {
            case CANifierDefn::USAGE::CANIFIER_1:
                usage = CANifierDefn::USAGE::CANIFIER_1;
                break;

            case CANifierDefn::USAGE::CANIFIER_2:
                usage = CANifierDefn::USAGE::CANIFIER_2;
                break;

            case CANifierDefn::USAGE::UNKNOWN_CANIFIER:
                usage = CANifierDefn::USAGE::UNKNOWN_CANIFIER;
                hasError = true;
                printf("==>> CANifierDefn:: unknown CANifier usage");
                break;
            }
        }
		
		else
		{
		    hasError = true;
			printf( "==>CANifierDefn::ParseXML invalid attribute %s \n", attr.name() );
		}

	}

	if (!hasError)
	{
        //creates CANifier object if no error in XML
		canifier = new ctre::phoenix::CANifier(canID);
		
	}
    return canifier;
}

