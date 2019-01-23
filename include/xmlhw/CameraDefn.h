/*
 * CameraDefn.h
 *
 *  Created on: Mar 10, 2018
 *      Author: neeth
 */

#ifndef SRC_SUBSYS_XMLPARSING_CAMERADEFN_H_
#define SRC_SUBSYS_XMLPARSING_CAMERADEFN_H_

// Third Party Includes
#include <pugixml/pugixml.hpp>


class CameraDefn
{
    public:

        enum PIXEL_FORMAT
        {
                UNKNOWN_PIXEL_FORMAT = -1,
                KMJPEG,
                KYUYV,
                KRGB565,
                KBGR,
                KGRAY
        };

        CameraDefn() = delete;
        virtual ~CameraDefn() = delete;
    /*Method: ParseXML
     *Description: Parses a Camera XML element
     * Returns: void
     *
     */
        static void ParseXML(
        pugi::xml_node	cameraNode
                );
private:

};

#endif /* SRC_SUBSYS_XMLPARSING_CAMERADEFN_H_ */
