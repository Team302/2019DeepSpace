/*
 * ServoDefn.h
 */

#ifndef SRC_SUBSYS_XMLPARSING_SERVODEFN_H_
#define SRC_SUBSYS_XMLPARSING_SERVODEFN_H_
 // C++ Includes
#include <iostream>

// FRC includes

// Team 302 includes
#include <hw/DragonServo.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

class ServoDefn
{
    public:
        ServoDefn() = delete;
        virtual ~ServoDefn() = delete;

        //-----------------------------------------------------------------------
        // Method:      ParseXML
        // Description: Parse a servo XML element and create a DragonServo from
        //              its definition.
        // Returns:     DragonServo*        servo (or nullptr if XML is ill-formed
        //-----------------------------------------------------------------------
        static DragonServo* ParseXML
        (
            pugi::xml_node      ServoNode
        );
};

#endif /* SRC_SUBSYS_XMLPARSING_SERVODEFN_H_ */