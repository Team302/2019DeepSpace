/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#ifndef SRC_SUBSYS_XMLPARSING_CANIFIERDEFN_H_
#define SRC_SUBSYS_XMLPARSING_CANIFIERDEFN_H_

// Third Party Includes
#include <pugixml/pugixml.hpp>

//CTRE Includes
#include <ctre/Phoenix.h>


class CANifierDefn
{
    public:

        CANifierDefn() = delete;
        virtual ~CANifierDefn() = delete;
    /*Method: ParseXML
     *Description: Parses a CANifier XML element
     * Returns: void
     *
     */
        static ctre::phoenix::CANifier* ParseXML(
        pugi::xml_node	canifierNode
                );
private:

};

#endif /* SRC_SUBSYS_XMLPARSING_CANIFIERDEFN_H_ */
