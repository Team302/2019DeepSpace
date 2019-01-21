/*
* DragonSparkMax.h
*
* Date Created: Jan 15, 2019
* Author: Jonah Shader
*/

#pragma once

#include <hw/IDragonMotorController.h>

#include <rev/CANSparkMax.h>

// namespaces
using namespace rev;

class DragonSparkMax : public IDragonMotorController
{
public:
    // Constructors
    DragonSparkMax() = delete;
    DragonSparkMax(int id, CANSparkMax::MotorType motorType);

    virtual ~DragonSparkMax() = default;

    // Getters
    double GetRotations() const override;
    double GetRPS() const override;

    // Setters
    void SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE mode) override;
    void Set(double value) override;
    void SetRotationOffset(double rotations) override;
    void SetVoltageRamping(double ramping) override; // seconds 0 to full, set to 0 to disable
    void EnableCurrentLimiting(bool enabled) override;
    void EnableBrakeMode(bool enabled) override;
    void SetPIDF(double p, double i, double d, double f) override;

private:
    CANSparkMax* m_spark;
    DRAGON_CONTROL_MODE m_controlMode;
    double m_rotationOffset;
    
};