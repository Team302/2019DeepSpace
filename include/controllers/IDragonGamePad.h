
/*========================================================================================================
 * IDragonGamePad.h
 *========================================================================================================
 *
 * File Description:  Interface for all input devices for controlling the robot in teleop mode.
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


#ifndef SRC_MAIN_INCLUDE_COMMON_CONTROLLERS_IDRAGONGAMEPAD_H_
#define SRC_MAIN_INCLUDE_COMMON_CONTROLLERS_IDRAGONGAMEPAD_H_

class IDragonGamePad
{
    public:
        enum BUTTON_IDENTIFIER
        {
            A_BUTTON,
            B_BUTTON,
            X_BUTTON,
            Y_BUTTON,
            LEFT_BUMPER,
            RIGHT_BUMPER,
            BACK_BUTTON,
            START_BUTTON,
            LEFT_STICK_PRESSED,
            RIGHT_STICK_PRESSED,
            LEFT_TRIGGER_PRESSED,
            RIGHT_TRIGGER_PRESSED,
            POV_0,
            POV_45,
            POV_90,
            POV_135,
            POV_180,
            POV_225,
            POV_270,
            POV_315,
            MAX_BUTTONS,
            UNDEFINED_BUTTON
        };


        enum BUTTON_MODE
        {
            STANDARD,
            DEBOUNCED,
            TOGGLE,
            DEBOUNCED_TOGGLE,
            MAX_BUTTON_MODES
       };

        enum AXIS_IDENTIFIER
        {
            LEFT_JOYSTICK_X,
            LEFT_JOYSTICK_Y,
            RIGHT_JOYSTICK_X,
            RIGHT_JOYSTICK_Y,
            LEFT_TRIGGER,
            RIGHT_TRIGGER,
            MAX_AXIS,
            UNDEFINED_AXIS
        };


        enum AXIS_DEADBAND
        {
            NONE,
            APPLY_STANDARD_DEADBAND,
            APPLY_SCALED_DEADBAND,
            MAX_DEADBANDS
        };

        enum AXIS_PROFILE
        {
            LINEAR,
            SQUARED,
            CUBED,
            MAX_PROFILES
        };

        IDragonGamePad() = default;
        ~IDragonGamePad() = default;

        
        //getters
        ///-------------------------------------------------------------------------------------------------
        /// Method:      GetAxisValue
        /// Description: Return the current value (between -1.0 and 1.0) for the requested axis.
        /// Returns:     float   - current axis value
        ///-------------------------------------------------------------------------------------------------
        virtual float GetAxisValue
        (
            AXIS_IDENTIFIER    axis        // <I> - axis identifier to read
        ) const = 0;

        ///-------------------------------------------------------------------------------------------------
        /// Method:      IsButtonPressed
        /// Description: Return whether the requested button is selected (true) or not (false)
        /// Returns:     bool    true  - button is pressed
        ///                      false - button is not pressed
        ///-------------------------------------------------------------------------------------------------
        virtual bool IsButtonPressed
        (
            BUTTON_IDENTIFIER    button         // <I> - button to check
        ) const = 0;


        //setters

        ///==================================================================================
        /// <summary>
        /// Method:         SetAxisDeadband
        /// Description:    Specify what deadband behavior is desired such as none, standard,
        ///                 standard with scaling.
        /// Returns:        void
        /// </summary>
        ///==================================================================================
        virtual void SetAxisDeadband
        (
            AXIS_IDENTIFIER axis, /// <I> - axis to modify
            AXIS_DEADBAND type    /// <I> - deadband option
        ) = 0;
        
        ///-------------------------------------------------------------------------------------------------
        /// Method:      SetProfile
        /// Description: Specify the profile curve used for setting the sensitivity of the axis.  By default,
        ///              this is linear, but a cubic curve would give more control when the axis is barely
        ///              pressed (e.g. if it were moved 50% forward, instead of returning 0.5, it would
        ///              return 0.5 * 0.5 * 0.5 or .125, but when the axis was moved all the way forward,
        ///              it would return the same value -- 1.0.  Since it is cubed, it retains the sign.
        ///
        ///              This affects values returned from GetAxis calls.
        /// Returns:     void
        ///-------------------------------------------------------------------------------------------------
        virtual void SetAxisProfile
        (
            AXIS_IDENTIFIER           axis,       // <I> - axis identifier to modify
            AXIS_PROFILE  	   curve       // <I> - the definition of the sensitivity
        ) = 0;


        ///-------------------------------------------------------------------------------------------------
        /// Method:      SetScale
        /// Description: Scale the returned value to a range between the specified negative scale factor and
        ///              the scale factor.  This is used to reduce the maximum value returned.
        ///
        ///              This affects values returned from GetAxis calls.
        /// Returns:     void
        ///-------------------------------------------------------------------------------------------------
        virtual void SetAxisScale
        (
            AXIS_IDENTIFIER    			        axis,       // <I> - axis identifier to modify
            float                               scaleFactor // <I> - value  (0 < scale <= 1.0) to scale the axis value
        ) = 0;

        //==================================================================================
        /// <summary>
        /// Method:         SetButtonMode
        /// Description:    Specify how the button should behave.  Examples include (but
        ///                 not limited to):
        ///                 - pressed / not pressed
        ///                 - toggle
        /// Returns:        void
        /// </summary>
        //==================================================================================
        virtual void SetButtonMode
        (
            BUTTON_IDENTIFIER button, /// <I> - button to check
            BUTTON_MODE mode          /// <I> - button behavior
        ) = 0;

        virtual double GetRawAxis
        (
            AXIS_IDENTIFIER    axis        // <I> - axis identifier to read
        ) const = 0;
        virtual bool IsRawButtonPressed
        (
            BUTTON_IDENTIFIER    button         // <I> - button to check
        ) const = 0;  

        virtual int GetPOVValue() const = 0;

};

#endif 