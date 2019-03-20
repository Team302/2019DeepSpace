#pragma once

#include <ctre/phoenix/CANifier.h>







class LED
{
    public:

    enum Colors
    { 
        RED,
        PURPLE,
        YELLOW,
        GREEN,
        BLUE,
        MAGENTA
        

    };


    LED(int CANId);
    LED() = delete;
   void SetColor( Colors color );



   private:
    ctre::phoenix::CANifier* m_CAN;
};