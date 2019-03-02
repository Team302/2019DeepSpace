/*
 * FieldDefn.h
 *
 *  Created on: Mar 10, 2018
 *      Author: team302
 */

#ifndef SRC_SUBSYS_XMLPARSING_FIELDDEFN_H_
#define SRC_SUBSYS_XMLPARSING_FIELDDEFN_H_

#include <pugixml/pugixml.hpp>
#include <auton/FieldMeasurement.h>

class FieldDefn
{
    public:
        FieldDefn() = delete;
        virtual ~FieldDefn() = delete;

        static void ParseXML
        (
            pugi::xml_node		fieldNode
        );
};


#endif /* SRC_SUBSYS_XMLPARSING_FIELDDEFN_H_ */
