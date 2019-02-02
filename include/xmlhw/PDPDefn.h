/*
 * PDPDefn.h
 *
 *  Created on: Jan 27, 2018
 *      Author: Chris
 */

#ifndef SRC_SUBSYS_XMLPARSING_PDPDEFN_H_
#define SRC_SUBSYS_XMLPARSING_PDPDEFN_H_

// C++ Includes
#include <iostream>

// FRC includes
#include <frc/PowerDistributionPanel.h>

// Team 302 includes

// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace frc;


class PDPDefn
{
public:

    //-----------------------------------------------------------------------
    // Method:      ParseXML
    // Description: Parse a pcm XML element and create a PowerDistributionPanel*
    //              from its definition.
    //
    //<!-- ====================================================
    //     PDP (power distribution panel)
    //     ==================================================== -->
    //<!ELEMENT pdp EMPTY>
    //<!ATTLIST pdp
    //          canId             (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
    //                              10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
    //                              20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 |
    //                              30 | 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 |
    //                              40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 | 48 | 49 |
    //                              50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 |
    //                              60 | 61 | 62 ) "0"
    //>
    //
    // Returns:     PowerDistributionPanel*        PDP object (or nullptr if XML
    //                                             is ill-formed
    //-----------------------------------------------------------------------
    static PowerDistributionPanel* ParseXML
    (
        pugi::xml_node      PDPNode
    );
};

#endif /* SRC_SUBSYS_XMLPARSING_PDPDEFN_H_ */
