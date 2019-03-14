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

#pragma once

#include <vector>

#include <subsys/IMechanism.h>
#include <hw/DragonTalon.h> 
#include <hw/IDragonMotorController.h>

class HatchMechanism : public IMechanism  
{
    public:
        HatchMechanism
        (
            std::vector<IDragonMotorController*> motorControllers
        );
        void SetState
        (
            bool  open        // <I> - true  = open to allow grabbing or deploying hatch
        );                    //       false = close to hold hatch

        void SetSpeed 
        (
            double speed      // <I> - speed to run motor
        );

        IMechanism::MECHANISM_TYPE GetType() const override;
        void SetParam
        (
            IMechanism::MECHANISM_PARAM_TYPE  param,          // <I> - parameter to set
            double                            value           // <I> - parameter value
        ) override;
        void SetPID
        (
            PIDData*        pid                 // <I> - PID control information
        ) override;



  
    private:
        DragonTalon* m_motor;

        // opening/closing rotations
        double m_initialRotations= 0.0;
        double m_open = 0.0;
        double m_closed = 180.0;
};
