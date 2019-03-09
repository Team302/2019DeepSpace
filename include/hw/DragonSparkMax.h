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
    //note: two PIDs: 0 is position, 1 is velocity
    // Constructors
    DragonSparkMax() = delete;
    DragonSparkMax(int id, IDragonMotorController::TALON_TYPE deviceType, CANSparkMax::MotorType motorType, double gearRatio);

    virtual ~DragonSparkMax() = default;

    // Getters
    double GetRotations() const override;
    double GetRPS() const override;
    IDragonMotorController::TALON_TYPE GetType() const override;
    int GetID() const override;

    // Setters
    void SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE mode) override;
    void Set(double value) override;
    void SetRotationOffset(double rotations) override;
    void SetVoltageRamping(double ramping, double rampingClosedLoop = -1) override; // seconds 0 to full, set to 0 to disable
    void EnableCurrentLimiting(bool enabled) override;
    void EnableBrakeMode(bool enabled) override;
    void SetPIDF(double p, double i, double d, double f, int slot = 0) override; // 0 is pos, 1 is vel
    void Invert(bool inverted) override;

    void InvertEncoder(bool inverted);
    void SetSmartCurrentLimiting(int limit);
    CANError Follow(DragonSparkMax* leader, bool invert = false);

private:
    double GetRotationsWithGearNoOffset() const;
    int m_id;
    CANSparkMax* m_spark;
    DRAGON_CONTROL_MODE m_controlMode;
    double m_outputRotationOffset;
    double m_gearRatio;
    IDragonMotorController::TALON_TYPE m_deviceType;

    CANSparkMax* GetSparkMax();
    
};