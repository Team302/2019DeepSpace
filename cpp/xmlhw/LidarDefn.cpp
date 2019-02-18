/*
 * LidarDefn.cpp
 *
 */


// C++ Includes
#include <iostream>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <hw/LidarFactory.h>
#include <hw/DragonLidar.h>
#include <xmlhw/LidarDefn.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>


//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a lidar XML element and create a DragonLidar object
//              from its definition.
//
//
//<!-- ====================================================
//     lidar
//     ==================================================== -->
//        enum LIDAR_USAGE
//         {
//             FORWARD_GRABBER,
//             DOWNWARD_GRABBER,
//             MAX_LIDAR_USAGES
//         };
//
//<!ELEMENT lidar EMPTY>
//<!ATTLIST lidar
//          usage             (  0 |  1  ) "0"
//          inputpin          CDATA #REQUIRED
//          triggerpin        CDATA #REQUIRED
//>
// Returns  void
//-----------------------------------------------------------------------
void LidarDefn::ParseXML
(
    pugi::xml_node      lidarNode
)
{
    // initialize the output

    // initialize attributes to default values
    DragonLidar::LIDAR_USAGE usage      = DragonLidar::FORWARD;
    int                      inputPin   = 0;
    int                      triggerPin = 0;

    bool hasError = false;

    for (pugi::xml_attribute attr = lidarNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "usage" ) == 0 )
        {
            int iVal = attr.as_int();
            switch ( iVal )
            {
                case DragonLidar::FORWARD:
                    usage = DragonLidar::FORWARD;
                    break;

                case DragonLidar::BACKWARD:
                    usage = DragonLidar::BACKWARD;
                    break;

                default:
                    printf( "==>>LidarDefn::ParseXML Invalid Lidar Usage %d \n", iVal );
                    hasError = true;
                    break;
            }
        }
        else if ( strcmp( attr.name(), "inputpin" ) == 0 )
        {
            int iVal = attr.as_int();
            if ( iVal > -1 && iVal < 10 )
            {
                inputPin = attr.as_int();
            }
            else
            {
                printf( "==>> LidarDefn::ParseXML invalid input pin %d \n", iVal );
                hasError = true;
            }
        }
        else if ( strcmp( attr.name(), "triggerpin" ) == 0 )
        {
            int iVal = attr.as_int();
            if ( iVal > -1 && iVal < 10 )
            {
                triggerPin = attr.as_int();
            }
            else
            {
                printf( "==>> LidarDefn::ParseXML invalid trigger pin %d \n", iVal );
                hasError = true;
            }
        }
        else
        {
            printf( "==>>LidarDefn::ParseXML invalid attribute %s \n", attr.name() );
            hasError = true;
        }
    }

    if ( !hasError )
    {
        LidarFactory::GetLidarFactory()->CreateLidar( usage, inputPin, triggerPin );
    }
}
