//====================================================================================================================================================
// PIDDefn.h
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
#include <xmlhw/PIDData.h>
#include <xmlhw/PIDDefn.h>

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
PIDData* PIDDefn::ParseXML
(
    pugi::xml_node      PIDNode
)
{
    // initialize output
    PIDData* data = nullptr;

    // initialize attributes to default values
    PIDData::CONTROL_MODE mode;
    PIDData::PID_TARGET pidTarget = PIDData::PID_TARGET::GENERAL;

    double p = 0.0;
    double i = 0.0;
    double d = 0.0;
    double f = 0.0;
    double maxAccel = 0.0;
    double cruiseVel = 0.0;

    bool hasError = false;

    // parse/validate xml
    for (pugi::xml_attribute attr = PIDNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "mode" ) == 0 )
        {
            mode = (PIDData::CONTROL_MODE)attr.as_int();
        }
        else if ( strcmp( attr.name(), "pidtarget" ) == 0 )
        {
            auto target = attr.value();
            if ( strcmp( target, "ARM") == 0 )
            {
                pidTarget = PIDData::PID_TARGET::ARM;
            }
            else if ( strcmp( target, "EXTENDER") == 0 )
            {
                pidTarget = PIDData::PID_TARGET::EXTENDER;
            }
            else if ( strcmp( target, "GENERAL") == 0 )
            {
                pidTarget = PIDData::PID_TARGET::GENERAL;
            }
            else
            {
                printf( "PID Target is invalid %s \n", target );
            }
        }
        else if ( strcmp( attr.name(), "proportional") == 0 )
        {
            p = attr.as_double();
        }       
         else if ( strcmp( attr.name(), "integral") == 0 )
        {
            i = attr.as_double();
        }        
        else if ( strcmp( attr.name(), "derivative") == 0 )
        {
            d = attr.as_double();
        }        
        else if ( strcmp( attr.name(), "feedforward") == 0 )
        {
            f = attr.as_double();
        }        
        else if ( strcmp( attr.name(), "maxacceleration") == 0 )
        {
            maxAccel = attr.as_double();
        }
        else if ( strcmp( attr.name(), "cruisevelocity") == 0 )
        {
            cruiseVel = attr.as_double();
        }
        else
        {
            printf( "==>> PIDDefn::ParseXML invalid attribute %s \n", attr.name() );
            hasError = true;
        }
    }
    if ( !hasError )
    {
        data = new PIDData( mode, pidTarget, p, i, d, f, maxAccel, cruiseVel );
    }
    return data;
}


