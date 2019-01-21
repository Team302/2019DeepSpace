/*
 * DigitalInputDfen.h
 *
 *  Created on: Jan 15, 2018
 *      Author: casti
 */

#ifndef SUBSYS_XMLPARSING_DIGITALINPUTDEFN_H_
#define SUBSYS_XMLPARSING_DIGITALINPUTDEFN_H_

// C++ Includes
#include <iostream>

// FRC includes

// Team 302 includes
//#include <hw/DragonDigitalInput.h>

// Third Party includes
#include <pugixml/pugixml.hpp>


class DigitalInputDefn
{
    public:

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
        //static DragonDigitalInput* ParseXML
        static void ParseXML
        (
            pugi::xml_node      motorNode
        );

};

#endif /* SUBSYS_XMLPARSING_DIGITALINPUTDEFN_H_ */
