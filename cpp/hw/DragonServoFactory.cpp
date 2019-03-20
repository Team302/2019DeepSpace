
/*========================================================================================================
 * DragonServoFactory.cpp
 *========================================================================================================
 *
 * File Description:  Create DragonServos and allow external clients to retrieve created DragonServos
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



#include <hw/DragonServoFactory.h>
#include <hw/DragonServo.h>


DragonServoFactory* DragonServoFactory::m_instance = nullptr;


DragonServoFactory* DragonServoFactory::GetInstance()
{
    if ( DragonServoFactory::m_instance == nullptr )
    {
        DragonServoFactory::m_instance = new DragonServoFactory();
    }
    return DragonServoFactory::m_instance;
}

DragonServoFactory::DragonServoFactory()
{
    for ( auto inx=0; inx<DragonServo::SERVO_USAGE::MAX_SERVO_USAGES; ++inx )
    {
        m_servo[inx] = nullptr;
    }
}

//=======================================================================================
// Method:          CreateDragonServo
// Description:     Create a DragonServo from the inputs
// Returns:         DragonServo*    - could be nullptr if invalid inputs are supplied
//=======================================================================================
DragonServo* DragonServoFactory::CreateDragonServo
(
    DragonServo::SERVO_USAGE    deviceUsage,        // <I> - Usage of the servo
    int                         deviceID,           // <I> - PWM ID
    double                      minAngle,           // <I> - Minimun desired angle
    double                      maxAngle            // <I> - Maximum desired angle
)
{
    DragonServo* servo = nullptr;
    if ( deviceUsage > DragonServo::SERVO_USAGE::UNKNOWN_SERVO_USAGE && deviceUsage < DragonServo::SERVO_USAGE::MAX_SERVO_USAGES )
    {
        servo = new DragonServo( deviceUsage, deviceID, minAngle, maxAngle );
        m_servo[(int) deviceUsage] = servo;
    }
    return servo;
}


//=======================================================================================
// Method:          GetDragonServo
// Description:     return DragonServo for a particular usage
// Returns:         DragonServo*                may be nullptr if there isn't a servo with
//                                              with this usage.
//=======================================================================================
DragonServo* DragonServoFactory::GetDragonServo
(
    DragonServo::SERVO_USAGE    deviceUsage         // <I> - Usage of the servo
)
{
    DragonServo* servo = nullptr;
    if ( deviceUsage > DragonServo::SERVO_USAGE::UNKNOWN_SERVO_USAGE && deviceUsage < DragonServo::SERVO_USAGE::MAX_SERVO_USAGES )
    {
        servo = m_servo[ (int) deviceUsage ];
    }
    return servo;
}
