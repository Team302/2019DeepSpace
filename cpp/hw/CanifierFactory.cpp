/*
 * CanifierFactory.cpp
 */

#include <ctre/phoenix/CANifier.h>

#include <hw/CanifierFactory.h>

CanifierFactory* CanifierFactory::m_instance = nullptr;

CanifierFactory* CanifierFactory::GetInstance()
{
	if ( CanifierFactory::m_instance == nullptr )
	{
		CanifierFactory::m_instance = new CanifierFactory();
	}
	return CanifierFactory::m_instance;
}

CanifierFactory::CanifierFactory()
{
    for ( auto inx=0; inx<63; ++inx )
    {
        m_canifiers[inx] = nullptr;
    }
}


//=======================================================================================
// Method:  		GetCanifier
// Description:		Find or create a Canifier with a the particular CAN ID
// Returns:         CANifier*  
//=======================================================================================
ctre::phoenix::CANifier* CanifierFactory::GetCanifier
(
	int			canID				// <I> - CAN ID
)
{
    ctre::phoenix::CANifier* canifier;
    if ( canID > -1 && canID < 63 )
    {
        if ( m_canifiers[canID] == nullptr )
        {
            m_canifiers[canID] = new ctre::phoenix::CANifier( canID );
        }
        canifier = m_canifiers[canID];
    }
    else
    {
        printf( "==>> CanifierFactory::GetCanifier: invalid CAN ID requested %d \n", canID );
    }
	return canifier;
}
