/*
 * DragonPDP.h
 */

#pragma once


#include <frc/PowerDistributionPanel.h>

using namespace frc;

class DragonPDP
{
	public:
		static DragonPDP* GetInstance();

		//=======================================================================================
		// Method:  		CreatePDP
		// Description:		Create a PDP from inputs
		// Returns:         Void
		//=======================================================================================
		PowerDistributionPanel* CreatePDP
		(
			int			canID				// <I> - PDP CAN ID
		);

		inline frc::PowerDistributionPanel* GetPDP() { return m_pdp;}

	private:
		DragonPDP() = default;
		virtual ~DragonPDP() = default;

		static DragonPDP*      				m_instance;
		frc::PowerDistributionPanel*      	m_pdp;

};


