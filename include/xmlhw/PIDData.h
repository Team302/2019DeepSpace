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

class PIDData
{
    public:
        enum PID_TARGET
        {
            ARM,
            EXTENDER,
            GENERAL
        };

        enum CONTROL_MODE
        {
            VELOCITY,
            POSITION,
            MOTION_MAGIC
        };

        PIDData
        (
            CONTROL_MODE            mode,
            PID_TARGET              pidTarget,
            double                  proportional,
            double                  integral,
            double                  derivative,
            double                  feedforward,
            double                  maxAcceleration,
            double                  cruiseVelocity
        );


        virtual ~PIDData() = default;

        inline CONTROL_MODE GetMode() { return m_mode; };
        inline PID_TARGET GetPidTarget() { return m_pidTarget; };
        inline double GetP() { return m_proportional; };
        inline double GetI() { return m_integral; };
        inline double GetD() { return m_derivative; };
        inline double GetF() { return m_feedforward; };
        inline double GetMaxAcceleration() { return m_maxAcceleration; };
        inline double GetCruiseVelocity() { return m_cruiseVelocity; };

 
    private:
        PIDData() = delete;

        CONTROL_MODE                    m_mode;
        PID_TARGET                      m_pidTarget;
        double                          m_proportional;
        double                          m_integral;
        double                          m_derivative;
        double                          m_feedforward;
        double                          m_maxAcceleration;
        double                          m_cruiseVelocity;

};

