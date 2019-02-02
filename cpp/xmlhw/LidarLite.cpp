/*
 *MotorControllerDefn.cpp
 */

// C++ Includes 
#include <iostream>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <xmlhw/LidarLIte.h>
//#include <hw/LidarLite.h>

//<!-- ====================================================
//        enum LIDAR_USAGE
//        {
//            FORWARD,
//            BACKWARD,
//            MAX_LIDAR_USAGES
//        };
//
//	==================================================== -->
//<!ELEMENT lidar EMPTY>
//<!ATTLIST lidar 
//          usage              ( 0 | 1  ) "0"
//          inputpin			 CDATA "0"
//          triggerpin		 CDATA "0"
//>
//DragonLidarLite* LidarLiteDefn::ParseXML
void LidarLiteDefn::ParseXML
(
    pugi::xml_node motorControllerNode
)
{
    int inputpin = 0;
    int triggerpin = 0; 
    //DragonLidarLite::LIDAR_USAGE = DragonLidarLite::UNKNOWN_LIDAR_USAGE;
    bool hasError = false;

    for(pugi::xml_attribute attr = motorControllerNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if(strcmp(attr.name(), "usage") == 0 )
        {
            int iVal = attr.as_int();
            /*switch (iVal)
            {
                case DragonLidarLite::LIDAR_USAGE::FOWARD:
                usage = DragonLidarLite::LIDAR_USAGE::FOWARD;
                break;
                case DragonLidarLite::LIDAR_USAGE::BACKWARD:
                usage = DragonLidarLite::LIDAR_USAGE::BACKWARD;
                break;
                case DragonLidarLite::Lidar_USAGE::MAX_LIDAR_USAGES:
                usage = DragonLidarLite::LIDAR_USAGE::MAX_LIDAR_USAGE;
                break
    
            }*/
        }
        else if (strcmp(attr.name(), "inputpin") == 0 )
        {
           inputpin = attr.as_int();
        }
        else if (strcmp(attr.name(), "triggerpin") == 0)
        {
            triggerpin = attr.as_int();
        }
        else   
        {
            printf("==>>MotorControllerDefn::ParseXML invalid attribute %s \n", attr.name());
            hasError = true;
        }
    }    
    if (!hasError)
    {
        //motorcontroller = new DragonMotorController(usage,type);
    }
    //return motorcontroller;
}
