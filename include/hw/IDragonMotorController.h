/*
 * IDragonMotorController.h
 *
 *  Created on: Jan 15, 2019
 *      Author: Jonah Shader
 */

#pragma once

#include <vector>

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
        ARM_MASTER,
        ARM_SLAVE,
        ARM_EXTENSION,
        WRIST,
        INTAKE,
        ELEVATOR_WINCH,
        ELEVATOR_DRIVE,
        HATCH_MECH_MOTOR,
        MAX_TALON_TYPES
    };

    // Getters
    virtual double GetRotations() const = 0;
    virtual double GetRPS() const = 0;
    virtual TALON_TYPE GetType() const = 0;
    double GetCurrent();
    virtual int GetID() const = 0;

    // Setters
    virtual void SetControlMode(DRAGON_CONTROL_MODE mode) = 0;
    virtual void Set(double value) = 0;
    virtual void SetRotationOffset(double rotations) = 0;
    virtual void SetVoltageRamping(double ramping, double closedLoopRamping = -1) = 0;
    virtual void EnableCurrentLimiting(bool enabled) = 0;
    virtual void EnableBrakeMode(bool enabled) = 0;
    virtual void SetPIDF(double p, double i, double d, double f, int slot = 0) = 0; // 0 is pos, 1 is vel
    virtual void Invert(bool inverted) = 0;

protected:
    IDragonMotorController() = default;
    virtual ~IDragonMotorController() = default;
};

typedef std::vector<IDragonMotorController*> IDragonMotorControllerVector;
