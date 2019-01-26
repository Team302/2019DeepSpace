/*
 *MotorControllerDefn.cpp
 */

// C++ Includes 
#include <iostream>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <xmlhw/MotorControllerDefn.h>
//#include <hw/DragonMotorController.h>

//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a motor controller XML element and create a DragonMotorController from
//              its definition..
//
//        <!-- ====================================================
//	        Motor Controller Usage
//	        ====================================================
//	        enum MOTOR_CONTROLLER_USAGE
//          {
//                FRONT_RIGHT_MOTOR_CONTROLLER,
//                FRONT_LEFT_MOTOR_CONTROLLER,
//                BACK_RIGHT_MOTOR_CONTROLLER,
//                BACK_LEFT_MOTOR_CONTROLLER
//	        };
//	        ==================================================== -->
//            <!-- ====================================================
//	        Motor Controller Type
//	        ====================================================
//	        enum MOTOR_CONTROLLER_TYPE
//          {
//                CANTALON,
//                SPARKMAX_BRUSHLESS,
//                SPARKMX_BRUSHED
//	        };
//	        ==================================================== -->
//        <!ELEMENT motorcontroller EMPTY>
//        <!ATTLIST motorcontroller
//                usage             (  0 |  1 |  2 |  3 |  4 |  5 |  6 ) "0" 
//                type              CDATA ( cantalon | sparkmax_brushless | sparkmax_brushed ) "cantalon"
//        >
//
//
//        Return:       DragonMotorCOntroller*
//-----------------------------------------------------------------------
//DragonMotorController* MotorControllerDefn::ParseXML
void MotorControllerDefn::ParseXML
(
    pugi::xml_node motorControllerNode
)
{
    //DragonMotorController::MOTOR_CONTROLLER_USAGE = DragonMotorController::UNKOWN_MOTOR_CONTROLLER_USAGE;
    bool hasError = false;

    for(pugi::xml_attribute attr = motorControllerNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if(strcmp(attr.name(), "usage") == 0 )
        {
            int iVal = attr.as_int();
            /*switch (iVal)
            {
                case DragonMotorController::MOTOR_CONTROLLER_USAGE::FRONT_RIGHT_MOTOR_CONTROLLER:
                    usage = DragonMotorController::MOTOR_CONTROLLER_USAGE::FRONT_RIGHT_MOTOR_CONTROLLER;
                    break;
                case DragonMotorController::MOTOR_CONTROLLER_USAGE::FRONT_LEFT_MOTOR_CONTROLLER:
                    usage = DragonMotorController::MOTOR_CONTROLLER_USAGE::FRONT_LEFT_MOTOR_CONTROLLER:
                    break;
                case DragonMotorController::MOTOR_CONTROLLER_USAGE::BACK_RIGHT_MOTOR_CONTROLLER:
                    usage = DragontMotorController::MOTOR_CONTROLLER_USAGE::BACK_RIGHT_MOTOR_CONTROLLER;
                    break;
                case DragonMotorController::MOTOR_CONTROLLER_USAGE::BACK_LEFT_MOTOR_CONTROLLER:
                    usage = DragonMotorController::MOTOR_CONTROLLER_USAGE::BACK_LEFT_MOTOR_CONTROLLER;
                    break;
    
            }*/
        }
        else if (strcmp(attr.name(), "type") == 0 )
        {
            int iVal = attr.as_int();
            /*switch (iVal)
            {
                case DragonMotorController::MOTOR_CONTROLLER_TYPE::CANTALON:
                    usage = DragonMotorController::MOTOR_CONTROLLER_TYPE::CANTALON;
                    break;
                case DragonMotorController::MOTOR_CONTROLLER_TYPE::SPARKMAX_BRUSHLESS:
                    usage = DragonMotorController::MOTOR_CONTROLLER_TYPE::SPARKMAX_BRUSHLESS;
                    break;
                case DragonMotorController::MOTOR_CONTROLLER_TYPE::SPARKMX_BRUSHED:
                    usage = DragonMotorController::MOTOR_CONTROLLER_TYPE::SPARKMAX_BRUSHLESS;
                    break;
            }*/
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
