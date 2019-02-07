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

#ifndef SRC_MAIN_INCLUDE_CONTROLLER_BUTTON_TOGGLEBUTTON_H_
#define SRC_MAIN_INCLUDE_CONTROLLER_BUTTON_TOGGLEBUTTON_H_

#include <controllers/button/ButtonDecorator.h>
#include <controllers/button/IButton.h>


//==================================================================================
/// <summary>
/// Class:          ButtonDecorator
/// Description:    This is a decorator for modifying button behavior.
/// </summary>
//==================================================================================
class ToggleButton : public ButtonDecorator
{
    public:
        ToggleButton 
        (
            IButton*        button          // <I> - button to decorate
        );
        ToggleButton() = delete;
        ~ToggleButton() = default;
        
        bool IsButtonPressed() const override;


    private:
        mutable bool        m_isPressed;
        mutable bool        m_isToggledOn;
};

#endif
