/*
 * LidarDefn.h
 *
 */

#ifndef SRC_SUBSYS_XMLPARSING_LIDARDEFN_H_
#define SRC_SUBSYS_XMLPARSING_LIDARDEFN_H_

// C++ Includes
#include <iostream>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <hw/DragonLidar.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

class LidarDefn
{
    public:
        LidarDefn() = delete;
        virtual ~LidarDefn() = delete;

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
        //             FORWARD,
        //             BACKWARD,
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
        static void ParseXML
        (
            pugi::xml_node      lidarNode
        );



};

#endif /* SRC_SUBSYS_XMLPARSING_LIDARDEFN_H_ */
