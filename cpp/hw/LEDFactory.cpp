/*
LEDFactory.cpp
Christopher Castillo
3/16/2019
*/

#include <hw/LEDFactory.h>
#include <hw/LED.h>

LEDFactory* LEDFactory::m_ledFactory = nullptr;

LEDFactory* LEDFactory::GetInstance
(

)
{
    if(LEDFactory::m_ledFactory == nullptr)
    {
        LEDFactory::m_ledFactory = new LEDFactory();
    }

    return LEDFactory::m_ledFactory;
}

LED* LEDFactory::GetLED
(
    LEDFactory::LED_USAGE  usage
)
{
     LED* led = nullptr;

    switch(usage)
    {
        case LEDFactory::UNDERSIDE:
            led = m_ledUnderside;
            break;
        case LEDFactory::FRONT:
            led = m_ledFrontSide;
            break;
        case LEDFactory::REAR:
            led = m_ledBackSide;
            break;
        default:
            printf("==>> Unknown LED usage %d \n", usage);
            break;
    }
    return led;
}

LED* LEDFactory::CreateLED
(
LEDFactory::LED_USAGE       usage,
int CANId
)
{
    LED* usage = nullptr;
    int index = usage;

    printf("LEDFactory index: %d\n", index);
    switch(index)
    {
        case LEDFactory::FRONT:
            printf("LEDFactory beginning of");
            break;
    }
}