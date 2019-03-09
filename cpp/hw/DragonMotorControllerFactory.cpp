/*
 * DragonMotorControllerFactory.cpp
 *
 */

#include <hw/DragonMotorControllerFactory.h>        
#include <xmlhw/MotorDefn.h>
#include <hw/DragonTalon.h>
#include <hw/DragonSparkMax.h>

#include <ctre/phoenix/MotorControl/CAN/TalonSRX.h>
#include <ctre/phoenix/MotorControl/FeedbackDevice.h>
#include <rev/CANSparkMax.h>


DragonMotorControllerFactory* DragonMotorControllerFactory::m_instance = nullptr;


DragonMotorControllerFactory* DragonMotorControllerFactory::GetInstance()
{
    if ( DragonMotorControllerFactory::m_instance == nullptr )
    {
        DragonMotorControllerFactory::m_instance = new DragonMotorControllerFactory();
    }
    return DragonMotorControllerFactory::m_instance;
}

DragonMotorControllerFactory::DragonMotorControllerFactory() 
{
	for ( auto inx=0; inx<63; ++inx )
	{
		m_controllers[inx] = nullptr;
	}
}

//=======================================================================================
// Method:          CreateMotorController
// Description:     Create a motor controller from the inputs
// Returns:         Void
//=======================================================================================
IDragonMotorController* DragonMotorControllerFactory::CreateMotorController
(
	DragonMotorControllerFactory::MOTOR_TYPE		mtype,
    int 											canID,
	int 											pdpID,
    IDragonMotorController::TALON_TYPE     			usage,
    bool 											inverted, 
    bool 											sensorInverted,
    ctre::phoenix::motorcontrol::FeedbackDevice  	feedbackDevice,
    int 											countsPerRev,
    float 											gearRatio,
    bool 											brakeMode,
    int 											slaveTo,
    int 											currentLimit,
    int 											peakCurrentDuration,
    int 											continuousCurrentLimit,
    int 											peakCurrentLimit,
    bool 											enableCurrentLimit
)
{
	printf("In DragonMotorControllerFactory beginning of constructor\n");
    IDragonMotorController* controller = nullptr;
	
	switch ( mtype )
	{
		case MOTOR_TYPE::TALONSRX:
		{
			// TODO:: set PDP ID
			auto talon = new DragonTalon( usage, canID, countsPerRev, gearRatio );
			talon->EnableBrakeMode( brakeMode );
			talon->Invert( inverted );
			talon->SetSensorInverted( sensorInverted );
			talon->ConfigSelectedFeedbackSensor( feedbackDevice, 0, 50 );
			talon->ConfigSelectedFeedbackSensor( feedbackDevice, 1, 50 );

			talon->ConfigPeakCurrentLimit( peakCurrentLimit, 50 );
			talon->ConfigPeakCurrentDuration( peakCurrentDuration, 50 );
			talon->ConfigContinuousCurrentLimit( continuousCurrentLimit, 50 );
			talon->EnableCurrentLimiting( enableCurrentLimit );

			if ( slaveTo > -1 )
			{
				talon->SetAsSlave( slaveTo );
			}       
			controller = talon;         
		}
		break;

		case MOTOR_TYPE::BRUSHLESS_SPARK_MAX:
		{
			// TODO:: set PDP ID
			auto smax = new DragonSparkMax( canID, usage, CANSparkMax::MotorType::kBrushless, gearRatio );
			smax->Invert( inverted );
			smax->EnableBrakeMode( brakeMode );
			smax->InvertEncoder( sensorInverted );
			smax->EnableCurrentLimiting( enableCurrentLimit );
			smax->SetSmartCurrentLimiting( continuousCurrentLimit );
			printf("Setting SparkMax current limit to %d\n", continuousCurrentLimit);

			if ( slaveTo > -1 )
			{
				DragonSparkMax* master = nullptr;
				if ( GetController( slaveTo ) != nullptr )
				{
					master = dynamic_cast<DragonSparkMax*>( GetController( slaveTo ) );
				}
				if ( master != nullptr )
				{
					smax->Follow( master );
				}
				else 
				{
					printf( "Invalid SlaveTo id %d \n", slaveTo );
				}
			}    
			controller = smax;           
		} 
		break;

		case MOTOR_TYPE::BRUSHED_SPARK_MAX:
		{
			// TODO:: set PDP ID
			auto smax = new DragonSparkMax( canID, usage, CANSparkMax::MotorType::kBrushed , gearRatio );
			smax->Invert( inverted );
			smax->EnableBrakeMode( brakeMode );
			smax->InvertEncoder( sensorInverted );
			smax->EnableCurrentLimiting( enableCurrentLimit );

			if ( slaveTo > -1 )
			{
				DragonSparkMax* master = nullptr;
				if ( GetController( slaveTo ) != nullptr )
				{
					master = dynamic_cast<DragonSparkMax*>( GetController( slaveTo ) );
				}
				if ( master != nullptr )
				{
					smax->Follow( master );
				}
				else 
				{
					printf( "Invalid SlaveTo id %d \n", slaveTo );
				}
			}
			controller = smax;
		}            
		break;

		default:
			break;
	}
	m_controllers[ canID ] = controller;
	printf("In DragonMotorControllerFactory end of constructor\n");
	return controller;
}



//=======================================================================================
// Method:          GetController
// Description:     return motor controller
// Returns:         IDragonMotorController* 	may be nullptr if there isn't a controller
//												with this CAN ID.
//=======================================================================================
IDragonMotorController* DragonMotorControllerFactory::GetController
(
	int			canID
)
{
	IDragonMotorController* controller = nullptr;
	if ( canID > -1 && canID < 63 )
	{
		controller = m_controllers[ canID ];
	}
	return controller;
}
