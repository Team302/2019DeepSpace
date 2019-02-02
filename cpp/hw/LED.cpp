//LEDs by Chris
//TODO:make LED.cpp and LED.h work with CANifier Factory


#include <hw/LED.h>



#include <CANifier.h>

using namespace ctre::phoenix;

//#include <ctre/phoenix/>

LED::LED()
{

CAN = new CANifier( 48 );

}
void LED::SetColor( Colors color )
{
double r = 0;//creating rgb numbers
double g = 0;
double b = 0;

 

switch(color)//switch that assigns rgb values to each color (orange doesn't work, for some reason.)
    {
    case RED:
    r = 255;
    g = 0;
    b = 0;
    break;

    case YELLOW:
    r=255;
	g=255;
    b=0;
    break;

    case PURPLE:
    r = 255;
    g = 100;
    b = 10;
    break;

    case GREEN:
    r=0;
    g=255;
    b=0;
    break; 

    case BLUE:
    r=0;
    g=0;
    b=255;
    break;

    case MAGENTA:
    r = 255;
    g = 0;
    b = 255;
    break;
    
    default:
 
    break;
    }   
    CAN->SetLEDOutput( r, CAN->LEDChannelB );//outputting rgb values to LED strip
    CAN->SetLEDOutput( g, CAN->LEDChannelA );
    CAN->SetLEDOutput( b, CAN->LEDChannelC );

}