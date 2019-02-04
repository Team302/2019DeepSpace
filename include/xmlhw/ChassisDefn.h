// --------------------------------------------------------------------------------------------
// ChassisDefn.h
// --------------------------------------------------------------------------------------------
//
// Description: Create a chassis from an XML definition
//
// <!ELEMENT chassis (motor*) >
// <!ATTLIST chassis
//           wheelDiameter     CDATA #REQUIRED
//           wheelBase         CDATA #REQUIRED
//           track             CDATA #REQUIRED
// >
//
// type matches CHASSIS_TYPE enum found in ChassisFactory.h
//
// Wheel Base is front-back distance between wheel centers
//
// Track is the distance between wheels on an "axle"
//
// --------------------------------------------------------------------------------------------

#ifndef SRC_SUBSYS_XMLPARSING_CHASSISDEFN_H_
#define SRC_SUBSYS_XMLPARSING_CHASSISDEFN_H_

// C++ includes

// FRC includes

// Team302 includes
#include <subsys/chassis/DragonChassis.h>

// Third Party includes
#include <pugixml/pugixml.hpp>

class ChassisDefn
{
	public:
		ChassisDefn() = delete;
		virtual ~ChassisDefn() = delete;

		//-----------------------------------------------------------------------
		// Method:      ParseXML
		// Description: Parse a Chassis XML element and create a DragonChassi from
		//              its definition.
		// Returns:     DragonChassis*        	chassis (or nullptr if XML is ill-formed)
		//-----------------------------------------------------------------------
		static DragonChassis* ParseXML
		(
			pugi::xml_node      chassisNode
		);
};

#endif /* SRC_SUBSYS_XMLPARSING_CHASSISDEFN_H_ */
