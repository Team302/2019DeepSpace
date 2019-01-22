/*
 * IDragonMotorController.h
 *
 *  Created on: Jan 15, 2019
 *      Author: Jonah Shader
 */

#pragma once

class IDragonMotorController
{
public:
    enum DRAGON_CONTROL_MODE {
        PERCENT_OUTPUT,
        ROTATIONS,
        RPS
    };

    enum TALON_TYPE
    {
        UNKNOWN_TALON_TYPE = -1,
        FRONT_LEFT_DRIVE,
        MIDDLE_LEFT_DRIVE,
        BACK_LEFT_DRIVE,
        FRONT_RIGHT_DRIVE,
        MIDDLE_RIGHT_DRIVE,
        BACK_RIGHT_DRIVE,
        ARM_LEFT,
        ARM_RIGHT,
        ARM_EXTENSION,
        WRIST,
        INTAKE,
        ELEVATOR_WINCH,
        ELEVATOR_DRIVE,
        MAX_TALON_TYPES
    };

    // Getters
    virtual double GetRotations() const = 0;
    virtual double GetRPS() const = 0;
    virtual TALON_TYPE GetType() const = 0;

    // Setters
    virtual void SetControlMode(DRAGON_CONTROL_MODE mode) = 0;
    virtual void Set(double value) = 0;
    virtual void SetRotationOffset(double rotations) = 0;
    virtual void SetVoltageRamping(double ramping) = 0;
    virtual void EnableCurrentLimiting(bool enabled) = 0;
    virtual void EnableBrakeMode(bool enabled) = 0;
    virtual void SetPIDF(double p, double i, double d, double f) = 0;
    virtual void SetInverted(bool inverted) = 0;
    virtual void SetSensorInverted(bool inverted) = 0;

protected:
    IDragonMotorController() = default;
    virtual ~IDragonMotorController() = default;
};