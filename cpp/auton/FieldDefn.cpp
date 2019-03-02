/*
 * FieldDefn.cpp
 *
 *  Created on: Mar 10, 2018
 *      Author: team302
 */

// C++ Includes
#include <iostream>

// FRC includes
#include <frc/AnalogInput.h>
#include <frc/SmartDashboard/SmartDashboard.h>

#include <auton/FieldMeasurement.h>
#include <auton/FieldDefn.h>
// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace frc;


//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a Field XML element and create an IFieldMeasurement
//              from its definition.
//
// Returns:     void
//-----------------------------------------------------------------------
void FieldDefn::ParseXML
(
    pugi::xml_node      mechanismNode
)
{
    // initialize attributes
	FieldMeasurement* m_measurements = FieldMeasurement::GetFieldMeasurement();
	FieldMeasurement::Measurement type = FieldMeasurement::UNKNOWN_FIELD;
	float xLoc = 0.0;
	float yLoc = 0.0;

    bool hasError = false;

    // Parse/validate xml
    for (pugi::xml_attribute attr = mechanismNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "type" ) == 0 )
        {
            int iVal = attr.as_int();
            switch ( iVal )
            {
                case FieldMeasurement::BLUE_SWITCH_RIGHT:
                    type = FieldMeasurement::BLUE_SWITCH_RIGHT;
                    break;

                case FieldMeasurement::BLUE_SWITCH_LEFT:
                    type = FieldMeasurement::BLUE_SWITCH_LEFT;
                    break;

                case FieldMeasurement::BLUE_SCALE_RIGHT:
                    type = FieldMeasurement::BLUE_SCALE_RIGHT;
                    break;

                case FieldMeasurement::BLUE_SCALE_LEFT:
                    type = FieldMeasurement::BLUE_SCALE_LEFT;
                    break;

                case FieldMeasurement::RED_SWITCH_RIGHT:
                    type = FieldMeasurement::RED_SWITCH_RIGHT;
                    break;

                case FieldMeasurement::RED_SWITCH_LEFT:
                    type = FieldMeasurement::RED_SWITCH_LEFT;
                    break;

                case FieldMeasurement::RED_SCALE_RIGHT:
                    type = FieldMeasurement::RED_SCALE_RIGHT;
                    break;

                case FieldMeasurement::RED_SCALE_LEFT:
                    type = FieldMeasurement::RED_SCALE_LEFT;
                    break;

                default:
                    printf( "==>> FieldDefn::ParseXML unknown Field type %s \n ", attr.value() );
                    hasError = true;
                    break;
            }
        }
        else if ( strcmp( attr.name(), "xloc" ) == 0 )
        {
        	xLoc = attr.as_float();
        }
        else if ( strcmp( attr.name(), "yloc" ) == 0 )
        {
        	yLoc = attr.as_float();
        }
        else
        {
            printf( "==>>FieldDefn::ParseXML invalid attribute %s \n", attr.name() );
            hasError = true;
        }
    }

    m_measurements->AddLocation(type, xLoc, yLoc);

    if ( !hasError )
    {

    }
}
