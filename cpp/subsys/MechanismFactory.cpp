#include <subsys/MechanismFactory.h>
#include <subsys/IMechanism.h>
#include <vector>

#include <hw/DragonAnalogInput.h>
#include <hw/DragonDigitalInput.h>
#include <hw/DragonServo.h>
#include <hw/DragonTalon.h>
#include <subsys/Intake.h>
#include <subsys/Arm.h>
#include <subsys/Wrist.h>
#include <subsys/Climber.h>

MechanismFactory* MechanismFactory::m_mechanismFactory = nullptr;

MechanismFactory* MechanismFactory::GetMechanismFactory()
{
	if ( MechanismFactory::m_mechanismFactory == nullptr )
	{
		MechanismFactory::m_mechanismFactory = new MechanismFactory();
	}
	return MechanismFactory::m_mechanismFactory;
}

IMechanism* MechanismFactory::GetIMechanism
(
	IMechanism::MECHANISM_TYPE			type		// <I> - manipulator type
)
{
	IMechanism* subsys = nullptr;
    switch ( type )
    {
        case IMechanism::CLIMBER:
            subsys = m_climber;
            break;

        case IMechanism::INTAKE:
            subsys = m_intake;
            break;

        case IMechanism::ARM:
            subsys = m_arm;
            break;

        case IMechanism::WRIST:
            subsys = m_wrist;
            break;

        default:
            printf( "==>> Unknown mechanism %d \n", type );
            break;
    }

	return subsys;
}

//=======================================================================================
// Method:  		CreateMechanism
// Description:		Create a mechanism from the inputs
// Returns:         Void
//=======================================================================================
IMechanism* MechanismFactory::CreateMechanism
(
    IMechanism::MECHANISM_TYPE           type,               // <I> - manipulator Type
    const IDragonMotorControllerVector&  motorControllers,   // <I> - Motor Controllers
    const DragonDigitalInputVector&      digitalInputs,      // <I> - Digital Inputs
    const DragonAnalogInputVector&       analogInputs,       // <I> - Analog Inputs
    const DragonServoVector&             servos              // <I> - servos
)
{
    IMechanism* subsys = nullptr;
    int index = type;

    switch ( index )
    {
        case IMechanism::CLIMBER:
            subsys = new Climber( motorControllers, servos );//, digitalInputs, analogInputs );
            //subsys = new Climber( type, motorControllers );//, digitalInputs, analogInputs );
            m_climber = subsys;
            break;

        case IMechanism::INTAKE:
            subsys = new Intake( motorControllers );
            //subsys = new Intake( type, motorControllers, digitalInputs, analogInputs );
            m_intake = subsys;
            break;

        case IMechanism::WRIST:
            subsys = new Wrist( motorControllers );
            //subsys = new Wrist( type, motorControllers, digitalInputs, analogInputs );
            m_wrist = subsys;
            break;

        case IMechanism::ARM:
            subsys = new Arm( motorControllers );
            // subsys = new Arm( type, motorControllers, digitalInputs, analogInputs );
            m_arm = subsys;
            break;

        default:
            printf( "==>> Unknown mechanism %d \n", index );
            break;
    }

    return subsys;
}

MechanismFactory::MechanismFactory() : m_climber( nullptr ),
                                       m_intake( nullptr ),
                                       m_arm( nullptr ),
                                       m_wrist( nullptr )
{
}

MechanismFactory::~MechanismFactory()
{
    delete m_climber;
    delete m_intake;
    delete m_arm;
    delete m_wrist;
}

