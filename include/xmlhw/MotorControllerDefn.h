/*
 * MotorControllerDefn.h
 */

#ifndef SRC_MAIN_CPP_XMLHW_MOTORCONTROLLERDEFN_H_
#define SRC_MAIN_CPP_XMLHW_MOTORCONTROLLERDEFN_H_
#endif

// Third Party Includes
#include <pugixml/pugixml.hpp>

class MotorControllerDefn
{
        public:

            MotorControllerDefn() = delete;
            virtual ~MotorControllerDefn() = delete;


            //-----------------------------------------------------------------------
        // Method:      ParseXML
        // Description: Parse a motor controller XML element and create a DragonMotorController from
        //              its definition..
        // Returns:     void
        //-----------------------------------------------------------------------
        //static DragonMotorController* ParseXML
        static void ParseXML
        (
            pugi::xml_node  motorControllerNode
        );
};