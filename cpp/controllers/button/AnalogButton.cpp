
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

#include <controllers/axis/AnalogAxis.h>
#include <controllers/button/AnalogButton.h>
#include <controllers/IDragonGamePad.h>

//==================================================================================
/// <summary>
/// Class:          DigitalButton
/// Description:    This is the standard button on a gamepad.
/// </summary>
//==================================================================================
AnalogButton::AnalogButton
(
    AnalogAxis*                         axis        // <I> - axis to turn into a button
) : m_axis( axis )                                  
{
}

//==================================================================================
/// <summary>
/// Method:         IsButtonPressed
/// Description:    Read the button and return true if it is pressed and false if 
///                 it isn't.
/// </summary>
//==================================================================================
bool AnalogButton::IsButtonPressed() const 
{
    bool pressed = false;
    if ( m_axis != nullptr )
    {
        auto axisValue = m_axis->GetAxisValue();
        pressed = (axisValue > m_AXIS_TOLERANCE);
    }
    return pressed;
}




