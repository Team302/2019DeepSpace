/*
 * MechanismDefn.h
 */

#ifndef SRC_SUBSYS_XMLPARSING_MECHANISMDEFN_H_
#define SRC_SUBSYS_XMLPARSING_MECHANISMDEFN_H_

// C++ Includes

// FRC includes

// Team 302 includes
//#include <subsys/IMechanism.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>


class MechanismDefn
{
    public:
        MechanismDefn() = delete;
        virtual ~MechanismDefn() = delete;


        //-----------------------------------------------------------------------
        // Method:      ParseXML
        // Description: Parse a Mechanism XML element and create an IMechanism
        //              from its definition.
        // Returns:     void
        //-----------------------------------------------------------------------
        static void ParseXML
        (
            pugi::xml_node      mechanismNode
        );
};

#endif /* SRC_SUBSYS_XMLPARSING_MECHANISMDEFN_H_ */
