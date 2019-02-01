/*
 * LidarLite.h
 */

#ifndef SRC_MAIN_CPP_XMLHW_LIDARLITE_H_
#define SRC_MAIN_CPP_LIDARLITE_H_
#endif

// Third Party Includes
#include <pugixml/pugixml.hpp>

class LidarLiteDefn
{
        public:

            LidarLiteDefn() = delete;
            virtual ~LidarLiteDefn() = delete;


            //-----------------------------------------------------------------------
        // Method:      ParseXML
        // Description: Parse a lidar lite XML element and create a DragonLidarLite from
        //              its definition..
        // Returns:     void
        //-----------------------------------------------------------------------
        //static DragonLidarLite* ParseXML
        static void ParseXML
        (
            pugi::xml_node  lidarLiteNode
        );
};