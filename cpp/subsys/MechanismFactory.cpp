#include <subsys/MechanismFactory.h>
#include <subsys/IMechanism.h>
#include <subsys/MechParamData.h>
#include <vector>

#include <hw/DragonAnalogInput.h>
#include <hw/DragonDigitalInput.h>
#include <hw/DragonServo.h>
#include <hw/DragonTalon.h>
#include <subsys/Intake.h>
#include <subsys/Arm.h>
#include <subsys/Wrist.h>
#include <subsys/Climber.h>
#include <subsys/HatchMechanism.h>
#include <xmlhw/PIDData.h>

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
        case IMechanism::MECHANISM_TYPE::CLIMBER:
            subsys = m_climber;
            break;

        case IMechanism::MECHANISM_TYPE::INTAKE:
            subsys = m_intake;
            break;

        case IMechanism::MECHANISM_TYPE::ARM:
            subsys = m_arm;
            break;

        case IMechanism::MECHANISM_TYPE::WRIST:
            subsys = m_wrist;
            break;

        case IMechanism::MECHANISM_TYPE::HATCH_MANIPULATOR:
            subsys = m_hatch;
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
    const DragonServoVector&             servos,             // <I> - servos
    const mechParameters&                parameters,         // <I> - parameters
    const std::vector<PIDData*>          pid                 // <I> - PID control info
)
{
    IMechanism* subsys = nullptr;
    int index = type;

    printf("MechanismFactory index: %d\n", index);

    switch ( index )
    {
        case IMechanism::MECHANISM_TYPE::CLIMBER:
            printf("MechanismFactory beginning of CLIMBER case\n");
            subsys = new Climber( motorControllers, servos );
            m_climber = subsys;
            break;

        case IMechanism::MECHANISM_TYPE::INTAKE:
            subsys = new Intake( motorControllers );
            m_intake = subsys;
            break;

        case IMechanism::MECHANISM_TYPE::WRIST:
           subsys = new Wrist( motorControllers );
            m_wrist = subsys;
            break;

        case IMechanism::MECHANISM_TYPE::ARM:
            subsys = new Arm( motorControllers );
            m_arm = subsys;
            break;

        case IMechanism::MECHANISM_TYPE::HATCH_MANIPULATOR:
            subsys = new HatchMechanism( motorControllers );
            m_hatch = subsys;
            break;

        default:
            printf( "==>> Unknown mechanism %d \n", index );
            break;
    }

    if ( subsys!= nullptr )
    {
        for ( auto inx=0; inx<parameters.size(); ++inx )
        {
            subsys->SetParam( parameters[inx].first, parameters[inx].second );
            printf("after MechanismFactory SetParam\n");
        }
        for ( auto inx=0; inx<pid.size(); ++inx )
        {
            subsys->SetPID( pid[inx] );
            printf("after MechanismFactory SetPID\n");
        }
    }

    printf("In MechanismFactory after pid and parameter stuff\n");

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
    delete m_hatch;
}

