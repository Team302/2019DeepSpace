/*
 * PrimitiveParser.h
 *
 *  Created on: Jan 24, 2018
 *      Author: casti
 */

#ifndef SRC_SUBSYS_XMLPARSING_PRIMITIVEPARSER_H_
#define SRC_SUBSYS_XMLPARSING_PRIMITIVEPARSER_H_

#include <pugixml/pugixml.hpp>
#include <auton/PrimitiveParams.h>

#include <iostream>

class PrimitiveParser
{
    public:
        static PrimitiveParamsVector ParseXML
        (
            std::string     fileName
        );
};

#endif /* SRC_SUBSYS_XMLPARSING_PRIMITIVEPARSER_H_ */
