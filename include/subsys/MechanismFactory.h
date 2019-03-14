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
#include <subsys/Arm.h>
#include <subsys/Climber.h>
#include <subsys/Intake.h>
#include <subsys/Wrist.h>
#include <subsys/IMechanism.h>
#include <subsys/MechParamData.h>
#include <subsys/HatchMechanism.h>
#include <xmlhw/PIDData.h>


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
			const IDragonMotorControllerVector&	    motorControllers,	// <I> - Motor Controllers
			const DragonDigitalInputVector&         digitalInputs,      // <I> - Digital Inputs
			const DragonAnalogInputVector&          analogInputs,       // <I> - Analog Inputs
			const DragonServoVector&                servos,             // <I> - servos
		    const mechParameters&               	parameters,         // <I> - parameters
    		const std::vector<PIDData*>         	pid                 // <I> - PID control info
		);

		inline Wrist* GetWrist() { return m_wrist != nullptr ? dynamic_cast<Wrist*>( m_wrist ) : nullptr; };
		inline Intake* GetIntake() { return m_intake != nullptr ? dynamic_cast<Intake*>( m_intake ) : nullptr; };
		inline Arm* GetArm() { return m_arm != nullptr ? dynamic_cast<Arm*>( m_arm ) : nullptr; };
		inline Climber* GetClimber() { return m_climber != nullptr ? dynamic_cast<Climber*>( m_climber ) : nullptr; };
		inline HatchMechanism* GetHatchMech() { return m_hatch != nullptr ? dynamic_cast<HatchMechanism*>( m_hatch ) : nullptr; };

	private:
		MechanismFactory();
		virtual ~MechanismFactory();

		IMechanism*                 m_wrist;
		IMechanism*                 m_intake;
		IMechanism*                 m_arm;
		IMechanism*                 m_climber;
		IMechanism*					m_hatch;

		static MechanismFactory*	m_mechanismFactory;
		
//		IMechanismVector            m_mechanisms;


};