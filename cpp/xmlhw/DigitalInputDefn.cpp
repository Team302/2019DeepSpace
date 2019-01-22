// --------------------------------------------------------------------------------------------
// DigitalInputDefn.cpp
//
//  Created on: Jan 15, 2018
//      Author: casti
//
// --------------------------------------------------------------------------------------------
//
// Description: Create an DigitalInput from an XML definition
//
//
// --------------------------------------------------------------------------------------------

// C++ includes
#include <iostream>

// FRC includes
#include <xmlhw/DigitalInputDefn.h>
#include <frc/SmartDashboard/SmartDashboard.h>

// Team302 includes
#include <xmlhw/DigitalInputDefn.h>
//#include <hw/DragonDigitalInput.h>

// Third Party includes
#include <pugixml/pugixml.hpp>


using namespace frc;

//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a motor XML element and create a DragonTalon from
//              its definition.
//
//<!-- ====================================================
//     digitalInput
//     ====================================================
//        enum DIGITAL_INPUT_TYPE
//        {
//            UNKNOWN_DIGITAL_INPUT_TYPE = -1,
//            CUBE_PRESENT,
//            ELEVATOR_POSITION_0,
//            ELEVATOR_POSITION_1,
//            ELEVATOR_POSITION_2,
//            ELEVATOR_POSITION_3,
//            ELEVATOR_POSITION_4,
//            ELEVATOR_POSITION_5,
//            ELEVATOR_POSITION_6,
//            MAX_DIGITAL_INPPUT_TYPES
//        };
//
//     ==================================================== -->
//<!ELEMENT digitalInput EMPTY>
//<!ATTLIST digitalInput
//          usage             (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 ) "0"
//          digitalId         (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
//                              10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
//                              20 | 21 | 22 | 23 | 24 | 25 ) "0"
//          reversed          (true | false ) "false"
//>
//
//
// Returns:     DragonDigitalInput*
//-----------------------------------------------------------------------
//DragonDigitalInput* DigitalInputDefn::ParseXML
void DigitalInputDefn::ParseXML
(
    pugi::xml_node DigitalNode
)
{
    // initialize the output
    //DragonDigitalInput*         input = nullptr;

    // initialize the attributes to default values
    //DragonDigitalInput::DIGITAL_INPUT_TYPE  usage = DragonDigitalInput::UNKNOWN_DIGITAL_INPUT_TYPE;
    int                                     digitalID = 0;
    bool                                    reversed = false;

    bool hasError = false;

    // Parse/validate the XML
    for (pugi::xml_attribute attr = DigitalNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "usage" ) == 0 )
        {
            int iVal = attr.as_int();
            /*switch (iVal )
            {
                //case DragonDigitalInput::DIGITAL_INPUT_TYPE::CUBE_PRESENT:
                    //usage = DragonDigitalInput::DIGITAL_INPUT_TYPE::CUBE_PRESENT;
                    break;

                //case DragonDigitalInput::DIGITAL_INPUT_TYPE::ELEVATOR_FLOOR:
                    //usage = DragonDigitalInput::DIGITAL_INPUT_TYPE::ELEVATOR_FLOOR;
                    break;

                //case DragonDigitalInput::DIGITAL_INPUT_TYPE::ELEVATOR_SWITCH:
                    //usage = DragonDigitalInput::DIGITAL_INPUT_TYPE::ELEVATOR_SWITCH;
                    break;

                //case DragonDigitalInput::DIGITAL_INPUT_TYPE::ELEVATOR_SCALE:
                    //usage = DragonDigitalInput::DIGITAL_INPUT_TYPE::ELEVATOR_SCALE;
                    break;

                //case DragonDigitalInput::DIGITAL_INPUT_TYPE::ELEVATOR_MAX:
                    //usage = DragonDigitalInput::DIGITAL_INPUT_TYPE::ELEVATOR_MAX;
                    break;

                //case DragonDigitalInput::DIGITAL_INPUT_TYPE::ELEVATOR_POSITION_4:
                    //usage = DragonDigitalInput::DIGITAL_INPUT_TYPE::ELEVATOR_POSITION_4;
                    break;

                //case DragonDigitalInput::DIGITAL_INPUT_TYPE::ELEVATOR_POSITION_5:
                    //usage = DragonDigitalInput::DIGITAL_INPUT_TYPE::ELEVATOR_POSITION_5;
                    break;

                //case DragonDigitalInput::DIGITAL_INPUT_TYPE::ELEVATOR_POSITION_6:
                   // usage = DragonDigitalInput::DIGITAL_INPUT_TYPE::ELEVATOR_POSITION_6;
                    break;

                default:
                	hasError = true;
                    printf( "==>> unknown DragonDigitalInput type %d \n", iVal );
                    break;
            }*/
        }
        else if ( strcmp( attr.name(), "digitalId" ) == 0 )
        {
            int iVal = attr.as_int();
            if ( iVal >=0 && iVal <= 25 )
            {
                digitalID = iVal;
            }
            else
            {
                printf( "==>> DigitalInputDefn::ParseXML  invalid digitalId %d \n", iVal );
                hasError = true;
            }
        }
        else if ( strcmp( attr.name(), "reversed" ) == 0 )
        {
            reversed = attr.as_bool();

        }
    }

    // Create the DragonDigitalInput
    if ( !hasError )
    {
        //input = new DragonDigitalInput( usage, digitalID, reversed );
    }
    //return input;
}

