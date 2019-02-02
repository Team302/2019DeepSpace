/*
 *TalonTachDefn.h
 *
 */

#ifndef SRC_MAIN_CPP_XMLHW_TALONTACH_H_
#define SRC_MAIN_CPP_XMLHW_TALONTACH_H_

// C++ Includes

// FRC includes

// Team 302 includes
//TODO Add the hw file for Talon Tach

// Third Party Includes
#include <pugixml/pugixml.hpp>



class TalonTachDefn
{
    public:

        TalonTachDefn() = delete; // ask Mr. Wits what this mean
        virtual ~TalonTachDefn() = delete;


                //-----------------------------------------------------------------------
        // Method:      ParseXML
        // Description: Parse a TalonTach XML element 
        // Returns:     void
        //-----------------------------------------------------------------------
        //static DragonTalon*ParseXML
        static void ParseXML
        (
            pugi::xml_node      talontachNode
        );
};

#endif /* SRC_MAIN_CPP_XMLHW_TALONTACH_H_ */