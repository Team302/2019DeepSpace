/*
 * IDragonMotorControllerFactory.h
 *
 */

#pragma once

#include <hw/IDragonMotorController.h>
#include <rev/CANSparkMax.h>


class IDragonMotorControllerFactory
{
    public:
        enum MOTOR_TYPE
        {
            TALONSRX,
            BRUSHLESS_SPARK_MAX,
            BRUSHED_SPARK_MAX,
            MAX_MOTOR_TYPES
        };
        static IDragonMotorControllerFactory* GetInstance();

        //=======================================================================================
        // Method:          CreateIDragonMotorController
        // Description:     Create a DragonMotorController from the inputs
        // Returns:         IDragonMotorController*
        //=======================================================================================
        IDragonMotorController* CreateIDragonMotorController
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
        );

    private:
        IDragonMotorControllerFactory() = default;
        ~IDragonMotorControllerFactory() = default;

        static IDragonMotorControllerFactory*        m_factory;
};

