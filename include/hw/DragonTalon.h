/*
* DragonTalon.h
*
* Date Created: Jan 15, 2019
* Author: Jonah Shader
*/

#pragma once

#include <vector>

#include "hw/IDragonMotorController.h"

#include <ctre/phoenix/ErrorCode.h>
#include <ctre/phoenix/MotorControl/CAN/TalonSRX.h>

// namespaces
using namespace ctre::phoenix;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

class DragonTalon : public IDragonMotorController
{
  public:
    // Enums
    enum TALON_TYPE
    {
        UNKNOWN_TALON_TYPE = -1,
        FRONT_LEFT_DRIVE,
        MIDDLE_LEFT_DRIVE,
        BACK_LEFT_DRIVE,
        FRONT_RIGHT_DRIVE,
        MIDDLE_RIGHT_DRIVE,
        BACK_RIGHT_DRIVE,
        ARM
    };

    enum TALON_SENSOR_TYPE
    {
        NO_SENSOR = -1,
        QUAD_ENCODER,
        UNKNOWN_SENSOR,
        ANALOG_POT,
        ANALOG_ENCODER,
        ENCODER_RISING,
        ENCODER_FALLING,
        CTRE_MAG_ENCODER_RELATIVE,
        CTRE_MAG_ENCODER_ABSOLUTE,
        PULSE_WIDTH,
        MAX_SENSOR_TYPES
    };

    enum TALON_CONTROL_MODE
    {
        PERCENT,
        POSITION,
        VELOCITY,
        // RPS,
        FOLLOWER,
        MOTION_MAGIC,
        MAX_TALON_MODES
    };

    // Constructors
    DragonTalon() = delete;
    DragonTalon(DragonTalon::TALON_TYPE deviceType, int deviceID, int countsPerRev, double gearRatio);
    virtual ~DragonTalon() = default;


    // Getters (override)
    double GetRotations() const override; //:D
    double GetRPS() const override; //:D

    // Setters (override)
    void SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE mode) override; //:D
    void Set(double value) override; //:D
    void SetRotationOffset(double rotations) override; //:D
    void SetVoltageRamping(double ramping) override; // :D seconds 0 to full, set to 0 to disable
    void EnableCurrentLimiting(bool enabled) override; // :D
    void EnableBrakeMode(bool enabled) override; // :D
    void SetPIDF(double p, double i, double d, double f) override; // :D
    void SetInverted(bool inverted) override; // :D
    void SetSensorInverted(bool inverted) override; // :D

    // Getters (TalonSRX)
    int GetCANID() const; //:D
    DragonTalon::TALON_TYPE GetType() const; //:D
    

    // Setters (TalonSRX)
    // more complete SetControlMode method compared to the overrided one
    void SetControlMode(TALON_CONTROL_MODE mode); //:D

	// Method:		SelectClosedLoopProfile
	// Description:	Selects which profile slot to use for closed-loop control
	// Returns:		void
	void SelectClosedLoopProfile(int slot, int pidIndex);// :D <I> - 0 for primary closed loop, 1 for cascaded closed-loop

    int ConfigSelectedFeedbackSensor(FeedbackDevice feedbackDevice, int pidIdx, int timeoutMs); //:D
    int ConfigSelectedFeedbackSensor(RemoteFeedbackDevice feedbackDevice, int pidIdx, int timeoutMs); //:D
	int ConfigPeakCurrentLimit(int amps, int timeoutMs); //:D
	int ConfigPeakCurrentDuration(int milliseconds, int timeoutMs); //:D
	int ConfigContinuousCurrentLimit(int amps, int timeoutMs); //:D

    void SetAsSlave(int masterCANID); //:D

    //Methods for Motion Magic control mode
	void ConfigMotionAcceleration(float maxMotionAcceleration); //:D
	void ConfigMotionCruiseVelocity(float maxMotionCruiseVelocity); //:D
    void ConfigPeakOutput(double percentOutput); //:D
    void ConfigNominalOutput(double nominalOutput); //:D


  private:
    TalonSRX *m_talon;
    TALON_CONTROL_MODE m_controlMode;
    TALON_TYPE m_type;

    int m_countsPerRev;
    long m_tickOffset;
    double m_gearRatio;
};

typedef std::vector<DragonTalon*> DragonTalonVector;