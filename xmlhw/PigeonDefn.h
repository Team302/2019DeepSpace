/*
 * PigeonDefn.h
 *
 *  Created on: Feb 2, 2018
 *      Author: team302
 */

#ifndef SRC_SUBSYS_XMLPARSING_PIGEONDEFN_H_
#define SRC_SUBSYS_XMLPARSING_PIGEONDEFN_H_

// C++ Includes
#include <iostream>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
//#include <hw/DragonPigeon.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>


class PigeonDefn
{
    public:

        PigeonDefn() = delete;
        virtual ~PigeonDefn() = delete;


        //-----------------------------------------------------------------------
        // Method:      ParseXML
        // Description: Parse a pigeon XML element and create a DragonPigeon from
        //              its definition.
        // Returns:     DragonPigeon*       pigeon IMU (or nullptr if XML is ill-formed)
        //-----------------------------------------------------------------------
        //static DragonPigeon* ParseXML
        static void ParseXML
        (
            pugi::xml_node      pigeonNode
        );
};


#endif /* SRC_SUBSYS_XMLPARSING_PIGEONDEFN_H_ */
