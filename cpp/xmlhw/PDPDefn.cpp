/*
 * PDPDefn.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Chris
 */


// C++ Includes
#include <iostream>

// FRC includes
#include <frc/PowerDistributionPanel.h>
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <hw/DragonPDP.h>
#include <xmlhw/PDPDefn.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>


using namespace frc;

//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a pcm XML element and create a PowerDistributionPanel*
//              from its definition.
//
//<!-- ====================================================
//     PDP (power distribution panel)
//     ==================================================== -->
//<!ELEMENT pdp EMPTY>
//<!ATTLIST pdp
//          canId             (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
//                              10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
//                              20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 |
//                              30 | 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 |
//                              40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 | 48 | 49 |
//                              50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 |
//                              60 | 61 | 62 ) "0"
//>
//
// Returns:     PowerDistributionPanel*        PDP object (or nullptr if XML
//                                             is ill-formed
//-----------------------------------------------------------------------
PowerDistributionPanel* PDPDefn::ParseXML
(
        pugi::xml_node      PDPNode
)
{
    // initialize output
    PowerDistributionPanel* powerpanel = nullptr;

    // initialize attributes to default values
    int canID = 0;

    bool hasError = false;

    // parse/validate xml
    for (pugi::xml_attribute attr = PDPNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "canId" ) == 0 )
        {
            int iVal = attr.as_int();
            if ( iVal > -1 && iVal < 63 )
            {
                canID = iVal;
            }
            else
            {
                printf( "==>> PDPDefn::ParseXML invalid canId %d \n", iVal );
                hasError = true;
            }
        }
        else
        {
            printf( "==>> PDPDefn::ParseXML invalid attribute %s \n", attr.name() );
            hasError = true;
        }
    }

    // create object
    if ( !hasError )
    {
        powerpanel = DragonPDP::GetInstance()->CreatePDP( canID );
    }
    return powerpanel;
}


