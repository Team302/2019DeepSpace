/*
 * MotorDefn.h
 *
 */

#pragma once


// C++ Includes
#include <vector>

// FRC includes

// Team 302 includes
#include <hw/IDragonMotorController.h>
#include <hw/DragonSparkMax.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>



class MotorDefn
{
    public:

        MotorDefn() = delete;
        virtual ~MotorDefn() = delete;


        //-----------------------------------------------------------------------
        // Method:      ParseXML
        // Description: Parse a motor XML element and create a DragonTalon from
        //              its definition.
        // Returns:     DragonTalon*        motor controller (or nullptr if XML
        //                                  is ill-formed
        //-----------------------------------------------------------------------
        static IDragonMotorController* ParseXML
        (
            pugi::xml_node      motorNode
        );

    private:
};


