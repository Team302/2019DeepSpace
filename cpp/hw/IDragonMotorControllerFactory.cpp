/*
 * IDragonMotorControllerFactory.cpp
 *
 */

#include <hw/IDragonMotorControllerFactory.h>
#include <hw/DragonTalon.h>
#include <hw/DragonSparkMax.h>

IDragonMotorControllerFactory* IDragonMotorControllerFactory::m_factory = nullptr;



IDragonMotorControllerFactory* IDragonMotorControllerFactory::GetInstance()
{
    if ( IDragonMotorControllerFactory::m_factory == nullptr )
    {
        IDragonMotorControllerFactory::m_factory = new IDragonMotorControllerFactory();
    }
    return IDragonMotorControllerFactory::m_factory;
}


//=======================================================================================
// Method:          CreateIDragonMotorControllerFactory
// Description:     Create a IDragonMotorControllerFactory from the inputs
// Returns:         IDragonMotorController*
//=======================================================================================
IDragonMotorController* IDragonMotorControllerFactory::CreateIDragonMotorController
(
    MOTOR_TYPE                          type,
    int                                 canID, 
    IDragonMotorController::TALON_TYPE  usage, 
    bool                                inverted,
    bool                                sensorInverted,
    int                                 feedbackDevice,     // TODO:: create enum
    int                                 countsPerRev,
    double                              gearRatio,
    bool                                brakeMode,          // can't set now
    int                                 follow,             // can't set now
    int                                 peakCurrentLimit,
    int                                 continuousCurrentLimit
)
{
    IDragonMotorController* motor = nullptr;
    switch ( type )
    {
        case MOTOR_TYPE::TALONSRX:
        {
            auto dt = new DragonTalon( usage, canID, countsPerRev, gearRatio );
            dt->SetInverted( inverted );
            dt->SetSensorInverted( sensorInverted );
            dt->ConfigPeakCurrentLimit( peakCurrentLimit, 0 );
            dt->ConfigContinuousCurrentLimit( continuousCurrentLimit, 0  );     
            motor = dt;       
        }
        break;

        case MOTOR_TYPE::BRUSHLESS_SPARK_MAX:
        {
            auto sm = new DragonSparkMax( canID, usage, rev::CANSparkMax::MotorType::kBrushless );
            sm->SetInverted( inverted );
            motor = sm;
            // TODO: handle current limits
        }
        break;

        case MOTOR_TYPE::BRUSHED_SPARK_MAX:
        {
            auto sm = new DragonSparkMax( canID, usage, rev::CANSparkMax::MotorType::kBrushed );
            sm->SetInverted( inverted );
            motor = sm;
            // TODO: handle current limits
        }
        break;

        default:
            break;
    }

    return motor;
}

