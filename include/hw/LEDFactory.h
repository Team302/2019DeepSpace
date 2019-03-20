//LEDFactory.h
//Christopher Castillo
//3/15/2019
#pragma once

#include <hw/LED.h>
#include <vector>


class LEDFactory
{
    public:

        static LEDFactory* GetInstance();

        enum LED_USAGE
        {
            UNDERSIDE,
            FRONT,
            REAR
        };

        LED* GetLED
        (
            LEDFactory::LED_USAGE   usage
        );

        LED* CreateLED
        (
            LEDFactory::LED_USAGE       usage,
            int    CANId
        );

        private:
            LEDFactory();
            virtual ~LEDFactory();
            LEDFactory*     m_usage;
            LED*     m_ledUnderside;
            LED*     m_ledFrontSide;
            LED*     m_ledBackSide;

            static LEDFactory* m_ledFactory;
            

    
};