/*
 * DragonMotorControllerFactory.h
 *
 */

#pragma once

#include <xmlhw/MotorDefn.h>
#include <hw/DragonTalon.h>
#include <hw/DragonSparkMax.h>

#include <ctre/phoenix/MotorControl/CAN/TalonSRX.h>
#include <ctre/phoenix/MotorControl/FeedbackDevice.h>
#include <rev/CANSparkMax.h>

class DragonMotorControllerFactory
{
    public:
	    enum MOTOR_TYPE
    	{
        	TALONSRX,
        	BRUSHLESS_SPARK_MAX,
        	BRUSHED_SPARK_MAX
    	};
        static DragonMotorControllerFactory* GetInstance();



		//=======================================================================================
		// Method:          CreateMotorController
		// Description:     Create a motor controller from the inputs
		// Returns:         Void
		//=======================================================================================
		IDragonMotorController* CreateMotorController
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
		);
		



		//=======================================================================================
		// Method:          GetController
		// Description:     return motor controller
		// Returns:         IDragonMotorController* 	may be nullptr if there isn't a controller
		//												with this CAN ID.
		//=======================================================================================
		IDragonMotorController* GetController
		(
			int			canID
		);

    private:
        DragonMotorControllerFactory();
        ~DragonMotorControllerFactory() = default;

        static DragonMotorControllerFactory*        m_instance;
		IDragonMotorController* 					m_controllers[63];


};

