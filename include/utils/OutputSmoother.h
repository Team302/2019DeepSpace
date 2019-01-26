/*
* OutputSmoother.h
*
* Date Created: Jan 24, 2019
* Author: Jonah Shader
*/

/*
This class applies ramping to an input value to reduce initial voltage spikes on motors.
Acceleration and deceleration are in units per update
*/

#pragma once

class OutputSmoother {
public:
    OutputSmoother(double acceleration, double deceleration); // accel and decel is in units per update
    ~OutputSmoother() = default;

    void Update();
    void SetInput(double input);
    double GetOutput() const;

private:
    double m_acceleration;
    double m_deceleration;
    double m_previousValue;
    double m_input;
};