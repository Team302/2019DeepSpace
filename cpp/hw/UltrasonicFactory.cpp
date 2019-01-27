/*
 * UltrasonicFactory.cpp
 *
 *  Created on: Feb 10, 2018
 *      Author: team302
 */

#include <hw/UltrasonicFactory.h>
#include <hw/DragonUltrasonic.h>

UltrasonicFactory* UltrasonicFactory::m_ultrasonicFactory = nullptr;
DragonUltrasonic* UltrasonicFactory::m_ultrasonic = nullptr;

UltrasonicFactory* UltrasonicFactory::GetUltrasonicFactory()
{
	if ( UltrasonicFactory::m_ultrasonicFactory == nullptr )
	{
		UltrasonicFactory::m_ultrasonicFactory = new UltrasonicFactory();
	}
	return UltrasonicFactory::m_ultrasonicFactory;
}

DragonUltrasonic* UltrasonicFactory::GetDragonUltrasonic
(
     DragonUltrasonic::ULTRASONIC_USAGE  usage
)
{
    DragonUltrasonic* ultra = nullptr;
    if ( usage == DragonUltrasonic::LEFT_SIDE_DISTANCE )
    {
        ultra = m_left;
    }
    else if ( usage == DragonUltrasonic::RIGHT_SIDE_DISTANCE )
    {
        ultra = m_right;
    }
    else
    {
        printf( "UltrasonicFactory::GetDragonUltrasonic invalid usage %d \n", usage );
    }

    return ultra;
}


//=======================================================================================
// Method:  		CreateUltrasonic
// Description:		Create an ultrasonic from the inputs
// Returns:         DragonUltrasonic*
//=======================================================================================
DragonUltrasonic* UltrasonicFactory::CreateUltrasonic
(
	DragonUltrasonic::ULTRASONIC_USAGE		usage,
	int								        analogInChannel
)
{
    DragonUltrasonic* ultra = nullptr;
    if ( usage == DragonUltrasonic::LEFT_SIDE_DISTANCE )
    {
        ultra = new DragonUltrasonic( usage, analogInChannel );;
    }
    else if ( usage == DragonUltrasonic::RIGHT_SIDE_DISTANCE )
    {
        ultra = new DragonUltrasonic( usage, analogInChannel );;
    }
    else
    {
        printf( "UltrasonicFactory::GetDragonUltrasonic invalid usage %d \n", usage );
    }
    return ultra;
}

UltrasonicFactory::UltrasonicFactory() : m_left( nullptr ),
                                         m_right( nullptr )
{
}


