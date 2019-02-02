/*
 * MechanismFactory.h
 */

#pragma once

#include <subsys/IMechanism.h>
#include <vector>

#include <hw/DragonAnalogInput.h>
#include <hw/DragonDigitalInput.h>
#include <hw/DragonServo.h>
#include <hw/DragonTalon.h>

class MechanismFactory
{
	public:

		static MechanismFactory* GetMechanismFactory();


		IMechanism* GetIMechanism
		(
			IMechanism::MECHANISM_TYPE			type		// <I> - manipulator type
		);

		//=======================================================================================
		// Method:  		CreateManipulator
		// Description:		Create a manipulator from the inputs
		// Returns:         Void
		//=======================================================================================
		IMechanism* CreateMechanism
		(
			IMechanism::MECHANISM_TYPE		        type,				// <I> - manipulator Type
			const std::vector<IDragonMotorController*>&		    motorControllers,	// <I> - Motor Controllers
			const DragonDigitalInputVector&         digitalInputs,      // <I> - Digital Inputs
			const DragonAnalogInputVector&          analogInputs,       // <I> - Analog Inputs
			const DragonServoVector&                servos              // <I> - servos
		);


	private:
		MechanismFactory();
		virtual ~MechanismFactory();

		IMechanism*                 m_intake;
		IMechanism*                 m_arm;
		IMechanism*                 m_wrist;
		IMechanism*                 m_climber;

		static MechanismFactory*	m_mechanismFactory;
//		IMechanismVector            m_mechanisms;


};