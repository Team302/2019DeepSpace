/*
* OutputSmoother.cpp
*
* Date Created: Jan 24, 2019
* Author: Jonah Shader
*/

#include "utils/OutputSmoother.h"

OutputSmoother::OutputSmoother(double acceleration, double deceleration) : m_acceleration(acceleration),
                                                                           m_deceleration(deceleration),
                                                                           m_previousValue(0.0),
                                                                           m_input(0.0)
{
}

void OutputSmoother::Update()
{
    if ((m_previousValue < 0 && m_input > 0) || (m_previousValue > 0 && m_input < 0))
    {
        if (m_previousValue < m_input)
        {
            m_previousValue += m_deceleration;
            if (m_previousValue > m_input)
            {
                m_previousValue = m_input;
            }
        }
        else
        {
            m_previousValue -= m_deceleration; // acceleration
            if (m_previousValue < m_input)
            {
                m_previousValue = m_input;
            }
        }
    }
    else // matching sign, accelerate
    {
        if (m_previousValue < m_input)
        {
            m_previousValue += m_acceleration;
            if (m_previousValue > m_input)
            {
                m_previousValue = m_input;
            }
        }
        else
        {
            m_previousValue -= m_acceleration; // acceleration
            if (m_previousValue < m_input)
            {
                m_previousValue = m_input;
            }
        }
    }

}

void OutputSmoother::SetInput(double input)
{
    m_input = input;
}

double OutputSmoother::GetOutput() const
{
    return m_previousValue;
}