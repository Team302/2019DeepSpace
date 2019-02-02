/*
 * DragonPDP.cpp
 */

#include <hw/DragonPDP.h>
#include <frc/PowerDistributionPanel.h>

using namespace frc;

DragonPDP* DragonPDP::m_instance = nullptr;

DragonPDP* DragonPDP::GetInstance()
{
	if ( DragonPDP::m_instance == nullptr )
	{
		DragonPDP::m_instance = new DragonPDP();
	}
	return DragonPDP::m_instance;
}
//=======================================================================================
// Method:  		CreatePDP
// Description:		Create a PDP from the inputs
// Returns:         TrueColors*
//=======================================================================================
PowerDistributionPanel* DragonPDP::CreatePDP
(
	int			canID				// <I> - CANLight CAN ID
)
{
	DragonPDP::m_pdp = new frc::PowerDistributionPanel( canID );

	return DragonPDP::m_pdp;
}
