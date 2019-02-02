// --------------------------------------------------------------------------------------------
// AnalogInputDefn.h
// --------------------------------------------------------------------------------------------
//
// Description: Create an AnalogInput from an XML definition
//
// 	<!-- ====================================================
//		 analogInput type options
//	 	====================================================
//	 	enum ANALOG_SENSOR_TYPE
//	 	{
//	 		UNKNOWN_ANALOG_TYPE = -1,
//	 		ANALOG_GENERAL,
//	 		ANALOG_GYRO,
//	 		POTENTIOMETER,
//	 		PRESSURE_GAUGE,
//	 		MAX_ANALOG_TYPES
//	 	};
//	 	==================================================== -->
//	<!ELEMENT analogInput EMPTY>
//	<!ATTLIST analogInput
//  	      type              (  0 |  1 |  2 ) "0"
//      	  analogId          (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 ) "0"
//            voltageMin        CDATA "0.0"
//            voltageMax        CDATA "5.0"
//            outputMin         CDATA #REQUIRED
//            outputMax         CDATA #REQUIRED
//	>
//
// --------------------------------------------------------------------------------------------

#ifndef SRC_SUBSYS_XMLPARSING_ANALOGINPUTDEFN_H_
#define SRC_SUBSYS_XMLPARSING_ANALOGINPUTDEFN_H_


// C++ includes

// FRC includes
#include <frc/AnalogInput.h>

// Team302 includes
#include <hw/DragonAnalogInput.h>

// Third Party includes
#include <pugixml/pugixml.hpp>

using namespace frc;

class AnalogInputDefn
{
    public:

		AnalogInputDefn() = delete;
        virtual ~AnalogInputDefn() = delete;


        //-----------------------------------------------------------------------
        // Method:      ParseXML
        // Description: Parse a analogSensor XML element and create a DragonAnalogInput from
        //              its definition.
        // Returns:     DragonAnalogInput*      AnalogInput (or nullptr if XML
        //                                  	is ill-formed
        //-----------------------------------------------------------------------
        static DragonAnalogInput* ParseXML
        (
            pugi::xml_node      sensorNode
        );
};

#endif /* SRC_SUBSYS_XMLPARSING_ANALOGINPUTDEFN_H_ */
