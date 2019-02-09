
/*========================================================================================================
 * DeadbandValue.h
 *========================================================================================================
 *
 * File Description:  Removes deadband from a input value, so small values are treated as 0.0.  This can
 *                    be useful to eliminate hardware noise as well as inadvertent movement of the analog
 *                    input.
 *
 *========================================================================================================*/

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

#ifndef SRC_MAIN_INCLUDE_CONTROLLER_AXIS_ANALOGAXIS_H_
#define SRC_MAIN_INCLUDE_CONTROLLER_AXIS_ANALOGAXIS_H_

#include <frc/GenericHID.h>

#include <controllers/IDragonGamePad.h>
#include <controllers/axis/IProfile.h>
#include <controllers/axis/IDeadband.h>
#include <controllers/axis/ScaledAxis.h>

//==================================================================================
/// <summary>
/// Class:          AnalogAxis
/// Description:    This class handles the analog inputs on a gamepad
/// </summary>
//==================================================================================
class AnalogAxis
{
    public:
        AnalogAxis
        (
            frc::GenericHID*                    gamepad,        // <I> - gamepad to query
            int                                 axisID,         // <I> - axis ID this maps to
            bool                                flipped         // <I> - true axis is reversed from what is expected, 
        );                                                      //       false axis has the expected direction



        //==================================================================================
        /// <summary>
        /// Method:         GetAxisValue
        /// Description:    Read the analog (axis) value and return it.  If the gamepad
        ///                 has an issue, return 0.0.
        /// </summary>
        //==================================================================================
        double GetAxisValue();

        void SetDeadBand
        (
            IDragonGamePad::AXIS_DEADBAND   type            /// <I> - deadband option
        );


        void SetAxisProfile
        (
            IDragonGamePad::AXIS_PROFILE    profile         /// <I> - axis profile
        );


        void SetAxisScaleFactor
        (
           double scale                     /// <I> - sacle factor
        );


    protected:
       
        //==================================================================================
        /// <summary>
        /// Method:         GetRawValue
        /// Description:    Returns the analog input's raw value.
        ///                 If there is a connection problem, 0.0 will be returned and 
        ///                 a debug message will be written.
        /// </summary>
        //==================================================================================
        virtual double GetRawValue();
 
    private:

        frc::GenericHID*                    m_gamepad;
        int                                 m_axis;
        IProfile*                           m_profile;
        IDeadband*                          m_deadband;
        ScaledAxis*                         m_scale;
};

#endif