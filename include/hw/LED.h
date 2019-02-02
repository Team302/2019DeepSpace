//LEDs - By Chris
#pragma once

#include <frc/CANifier.h>







class LED
{
    public:

    enum Colors //enum containing colors
    { 
        RED,
        PURPLE,
        YELLOW,
        GREEN,
        BLUE,
        MAGENTA
        

    };

    LED();
   void SetColor( Colors color );



   private:

        ctre::phoenix::CANifier* CAN;
};