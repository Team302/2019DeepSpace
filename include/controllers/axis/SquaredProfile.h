
/*========================================================================================================
 * SquaredProfile.h
 *========================================================================================================
 *
 * File Description:  This applies a squared value profile to the input values.
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


#ifndef SRC_MAIN_INCLUDE_COMMON_CONTROLLERS_AXIS_SQUAREDPROFILE_H_
#define SRC_MAIN_INCLUDE_COMMON_CONTROLLERS_AXIS_SQUAREDPROFILE_H_

#include <controllers/axis/IProfile.h>

//==================================================================================
/// <summary>
/// Class:          CubedProfile
/// Description:    This provides profile to be applied to input values.
/// </summary>
//==================================================================================
class SquaredProfile : public IProfile
{
    public:

        //==================================================================================
        /// <summary>
        /// Method:         GetInstance
        /// Description:    Static singleton method to create the object
        /// Returns:        SquaredProfile*  Singleton squared profile object
        /// </summary>
        //==================================================================================
        static SquaredProfile* GetInstance();


        //==================================================================================
        /// <summary>
        /// Method:         ApplyProfile
        /// Description:    Apply the profile
        /// </summary>
        //==================================================================================
        double ApplyProfile
        (
            double      inputVal            // <I> - value to apply profile to
        ) const override;

    private:
        SquaredProfile() = default;
        ~SquaredProfile() = default;

        static SquaredProfile*       m_instance;

};

#endif
