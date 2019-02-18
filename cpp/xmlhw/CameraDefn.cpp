/*
 * CameraDefn.cpp
 *
 *  Created on: Mar 10, 2018
 *      Author: neeth
 */

#include <xmlhw/CameraDefn.h>

//Third Party includes
#include <pugixml/pugixml.hpp>

//WPILIB includes
#include <cameraserver/CameraServer.h>

using namespace frc;

//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a Camera XML element....
//
//
//<!-- ====================================================
//		 camera pixel format options
//		 ====================================================
//		 	enum PIXEL_FORMAT
//		{
//				UNKNOWN_PIXEL_FORMAT = -1,
//				KMJPEG,
//				KYUYV,
//				KRGB565,
//				KBGR,
//				KGRAY
//		};
//		===================================================== -->
//	<!ELEMENT camera EMPTY>
//	<!ATTLIST camera
//			  type 				( 0 | 1 | 2 | 3 | 4) "0"
//			  width				CDATA "0"
//			  height			CDATA "0"
//			  fps				CDATA "0"
//	>
//
//
// Returns:     void
//-----------------------------------------------------------------------
void CameraDefn::ParseXML
(
    pugi::xml_node      cameraNode
)
{
//initialize output

// initialize attributes to default values
	cs::VideoMode::PixelFormat type = cs::VideoMode::kUnknown;
	int				 	ID = 0;
	int 				width = 640;
	int 				height = 480;
	int 				fps = 30;

	bool hasError = false;

//Parse/validate xml
	for(pugi::xml_attribute attr = cameraNode.first_attribute(); attr; attr = attr.next_attribute() )
	{
		if ( strcmp( attr.name(), "ID") == 0 )
		{
			ID = attr.as_int();
		}
		else if (strcmp(attr.name(), "format" ) == 0)
		{
			int iVal = attr.as_int();
			switch(iVal)
			{
			case CameraDefn::KMJPEG:
				type = cs::VideoMode::kMJPEG;
				break;

			case CameraDefn::KYUYV:
				type = cs::VideoMode::kYUYV;
				break;

			case CameraDefn::KRGB565:
				type = cs::VideoMode::kRGB565;
				break;

			case CameraDefn::KBGR:
				type = cs::VideoMode::kBGR;
				break;

			case CameraDefn::KGRAY:
				type = cs::VideoMode::kGray;
				break;

			default:
				type = cs::VideoMode::kUnknown;
				hasError = true;
				printf( "==>> CameraDefn:: unknown camera format %d \n", iVal );
				break;
			}
		}
		else if (strcmp(attr.name(), "width") == 0)
		{
			width = attr.as_int();
		}

		else if (strcmp(attr.name(), "height") == 0)
		{
			height = attr.as_int();
		}
		else if (strcmp(attr.name(), "fps") == 0)
		{
			fps = attr.as_int();
		}
		else
		{
		    hasError = true;
			printf( "==>CameraDefn::ParseXML invalid attribute %s \n", attr.name() );
		}

	}

	if (!hasError)
	{
		CameraServer* server = CameraServer::GetInstance();
		if ( server != nullptr )
		{
		    cs::UsbCamera camera = server->StartAutomaticCapture( ID );
            	    camera.SetVideoMode(type, width, height, fps );
		}
		else
		{
		    printf( "==>> CameraDefn: camera server not found \n" );
		}
	}
}

