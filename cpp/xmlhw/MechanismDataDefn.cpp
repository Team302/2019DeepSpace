//====================================================================================================================================================
// MechanismDataDefn.h
//====================================================================================================================================================
// Copyright 2018 Lake Orion Robobitcs FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

// C++ Includes
#include <iostream>
#include <utility>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <subsys/IMechanism.h>
#include <xmlhw/MechanismDataDefn.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>



using namespace frc;


//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse MechanismData XML element 
//  <!ELEMENT mechanismData EMPTY>
//  <!ATTLIST mechanismData 
//            dataType
//            value CDATA "0.0"
//  >
//
// Returns:     mechParamData        mechanism data
//-----------------------------------------------------------------------
mechParamData  MechanismDataDefn::ParseXML
(
    pugi::xml_node      MechanismDataNode
)
{
    // initialize output
    mechParamData mechData;

    // initialize attributes to default values
    mechData.first = IMechanism::MECHANISM_PARAM_TYPE::MECHANISM_DATA_UNKNOWN;
    mechData.second = 0.0;

    bool hasError = false;

    // parse/validate xml
    for (pugi::xml_attribute attr = MechanismDataNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "dataType" ) == 0 )
        {
            IMechanism::MECHANISM_PARAM_TYPE type = (IMechanism::MECHANISM_PARAM_TYPE)attr.as_int();
            if ( type > IMechanism::MECHANISM_PARAM_TYPE::MECHANISM_DATA_UNKNOWN && 
                 type < IMechanism::MECHANISM_PARAM_TYPE::MAX_MECHANISM_PARAM_TYPES )
            {
                mechData.first = type;
            }
            else
            {
                printf( "==>> MechanismDataDefn::ParseXML invalid dataType %d \n", type );
                hasError = true;
            }
        }
        else if ( strcmp( attr.name(), "value") == 0 )
        {
            mechData.second = attr.as_double();
        }
        else
        {
            printf( "==>> MechanismDataDefn::ParseXML invalid attribute %s \n", attr.name() );
            hasError = true;
        }
    }
    return mechData;
}


