/*
 * CanifierFactory.h
 */

#pragma once


#include <ctre/phoenix/CANifier.h>

class CanifierFactory
{
	public:
		static CanifierFactory* GetInstance();

		//=======================================================================================
		// Method:  		GetCanifier
		// Description:		Find or create a Canifier with a the particular CAN ID
		// Returns:         CANifier*  
		//=======================================================================================
		ctre::phoenix::CANifier* GetCanifier
		(
			int			canID				// <I> - CAN ID
		);

	private:
		CanifierFactory();
		virtual ~CanifierFactory() = default;

		static CanifierFactory*      				m_instance;
        ctre::phoenix::CANifier* m_canifiers[63];

};


