/*
 * RobotDefn.cpp
 *
 */

// C++ Includes
#include <iostream>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <xmlhw/RobotDefn.h>
#include <xmlhw/CameraDefn.h>
#include <xmlhw/ChassisDefn.h>
//#include <xmlhw/LidarDefn.h>
#include <xmlhw/MechanismDefn.h>
//#include <xmlhw/PCMDefn.h>
#include <xmlhw/PDPDefn.h>
#include <xmlhw/PigeonDefn.h>
#include <xmlhw/LEDDefn.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>


using namespace frc;
//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a robot.xml file
// Returns:     void
//-----------------------------------------------------------------------
void RobotDefn::ParseXML()
{
    // set the file to parse
    const char* filename = "/home/lvuser/config/robot.xml";

    // load the xml file into memory (parse it)
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file( filename );

    // if it is good
    if ( result )
    {
        printf( "XML file [ %s ] parsed without errors \n ", filename );

        // get the root node <robot>
        pugi::xml_node parent = doc.root();
        for (pugi::xml_node node = parent.first_child(); node; node = node.next_sibling())
        {
            // loop through the direct children of <robot> and call the appropriate parser
            for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling())
            {
                if ( strcmp( child.name(), "chassis") == 0 )
                {
                    printf("chassis parse \n");
                    ChassisDefn::ParseXML( child );
                }
                else if ( strcmp( child.name(), "mechanism") == 0 )
                {
                    printf("mech parse \n");
                    MechanismDefn::ParseXML( child );
                }
                // else if ( strcmp( child.name(), "pcm") == 0 )
                // {
                //     //PCMDefn::ParseXML( child );
                // }
                else if ( strcmp( child.name(), "pdp") == 0 )
                {
                    printf("pdp parse \n");
                    // PDPDefn::ParseXML( child );
                }
                else if ( strcmp( child.name(), "pigeon") == 0 )
                {
                    printf("pigeon parse \n");
                    PigeonDefn::ParseXML( child );
                }
                // else if ( strcmp( child.name(), "lidar") == 0 )
                // {
                //     //LidarDefn::ParseXML( child );
                // }
                else if ( strcmp( child.name(), "camera") == 0 )
                {
                    printf("camera parse \n");
                    // CameraDefn::ParseXML( child );
                }
                else if ( strcmp( child.name(), "led") == 0 )
                {
                    printf("led parse\n");
                    LEDDefn::ParseXML(child);
                }
                else
                {
                    printf( "==>>RobotDefn::ParseXML unknown robot child %s \n", child.name() );
                }
            }
        }
    }
    else
    {
        std::cout << "XML [" << filename << "] parsed with errors, attr value: [" << doc.child("prototype").attribute("attr").value() << "]\n";
        std::cout << "Error description: " << result.description() << "\n";
        std::cout << "Error offset: " << result.offset << " (error at [..." << (filename + result.offset) << "]\n\n";
    }
    
}
