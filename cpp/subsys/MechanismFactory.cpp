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
    const DragonServoVector&             servos,             // <I> - servos
    const mechParameters&                parameters,         // <I> - parameters
    const std::vector<PIDData*>          pid                 // <I> - PID control info
)
{
    IMechanism* subsys = nullptr;
    int index = type;

    switch ( index )
    {
        case IMechanism::CLIMBER:
            subsys = new Climber( motorControllers, servos );
            // for ( auto itr=parmeters.begin(); itr!=parameters.end(); ++itr )
            // {
            //     subsys->SetParam( itr.first, itr.second );
            // }
            // for ( auto itr=pid.begin(); itr!=pid.end; ++itr)
            // {
            //     subsys->SetPID( itr );
            // }
            m_climber = subsys;
            break;

        case IMechanism::INTAKE:
            subsys = new Intake( motorControllers );
            // for ( auto itr=parmeters.begin(); itr!=parameters.end(); ++itr )
            // {
            //     subsys->SetParam( itr.first, itr.second );
            // }
            // for ( auto itr=pid.begin(); itr!=pid.end; ++itr)
            // {
            //     subsys->SetPID( itr );
            // }
            m_intake = subsys;
            break;

        case IMechanism::WRIST:
            subsys = new Wrist( motorControllers );
            // for ( auto itr=parmeters.begin(); itr!=parameters.end(); ++itr )
            // {
            //     subsys->SetParam( itr.first, itr.second );
            // }
            // for ( auto itr=pid.begin(); itr!=pid.end; ++itr)
            // {
            //     subsys->SetPID( itr );
            // }
            m_wrist = subsys;
            break;

        case IMechanism::ARM:
            subsys = new Arm( motorControllers );
            // for ( auto itr=parmeters.begin(); itr!=parameters.end(); ++itr )
            // {
            //     subsys->SetParam( itr.first, itr.second );
            // }
            // for ( auto itr=pid.begin(); itr!=pid.end; ++itr)
            // {
            //     subsys->SetPID( itr );
            // }
            m_arm = subsys;
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
        }
        for ( auto inx=0; inx<pid.size(); ++inx )
        {
            subsys->SetPID( pid[inx] );
        }
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

