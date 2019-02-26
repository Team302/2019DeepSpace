/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsys/LEDFactory.h"

#include "hw/LED.h"

LEDFactory* LEDFactory::m_ledfactory = nullptr;
LEDFactory* LEDFactory::GetLEDFactory
(

) 
{
    if(LEDFactory::m_ledfactory == nullptr)
    {
        LEDFactory::m_ledfactory = new LEDFactory();
    }
    return LEDFactory::m_ledfactory;
}

LED* LEDFactory::GetLED
(
    LED_LOCATIONS location
)
{
    LED* led = nullptr;
    switch(location)
    {
        case FRONT:
            led = m_frontled;
            break;

        case BACK:
            led = m_backled;
            break;

        case TOP:
            led = m_topled;
            break;

        default:
            printf("==> Unknown led%d \n", location);
            break;
    }

    return led;
} 

LED* LEDFactory::CreateLEDs
(
    LED_LOCATIONS location
)
{
    LED* led = nullptr;

    switch(location)
    {
        case FRONT:
        //
        break;

        case BACK:
        //
        break;

        case TOP:
        //
        break;
    }
    return led;
}

LEDFactory::LEDFactory() : m_frontled(nullptr),
                           m_backled(nullptr),
                           m_topled(nullptr)
{

}

LEDFactory::~LEDFactory()
{
    delete m_frontled;
    delete m_backled;
    delete m_topled;
}