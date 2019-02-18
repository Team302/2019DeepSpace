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
    DragonTalon(IDragonMotorController::TALON_TYPE deviceType, int deviceID, int countsPerRev, double gearRatio);
    virtual ~DragonTalon() = default;


    // Getters (override)
    double GetRotations() const override;
    double GetRPS() const override;
    IDragonMotorController::TALON_TYPE GetType() const override;
    int GetID() const override;

    // Setters (override)
    void SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE mode) override; //:D
    void Set(double value) override;
    void SetRotationOffset(double rotations) override;
    void SetVoltageRamping(double ramping, double rampingClosedLoop = -1) override; // seconds 0 to full, set to 0 to disable
    void EnableCurrentLimiting(bool enabled) override; 
    void EnableBrakeMode(bool enabled) override; 
    void SetPIDF(double p, double i, double d, double f, int slot = 0) override; 
    void Invert(bool inverted) override; 

    // Setters (TalonSRX)
    // more complete SetControlMode method compared to the overrided one
    void SetControlMode(TALON_CONTROL_MODE mode); 
    void SetSensorInverted(bool inverted);

	// Method:		SelectClosedLoopProfile
	// Description:	Selects which profile slot to use for closed-loop control
	// Returns:		void
	void SelectClosedLoopProfile(int slot, int pidIndex);// <I> - 0 for primary closed loop, 1 for cascaded closed-loop

    int ConfigSelectedFeedbackSensor(FeedbackDevice feedbackDevice, int pidIdx, int timeoutMs); //:D
    int ConfigSelectedFeedbackSensor(RemoteFeedbackDevice feedbackDevice, int pidIdx, int timeoutMs); //:D
	int ConfigPeakCurrentLimit(int amps, int timeoutMs); 
	int ConfigPeakCurrentDuration(int milliseconds, int timeoutMs); 
	int ConfigContinuousCurrentLimit(int amps, int timeoutMs); 

    void SetAsSlave(int masterCANID); 

    //Methods for Motion Magic control mode
	void ConfigMotionAcceleration(float maxMotionAcceleration);      // in rotations per second per second
	void ConfigMotionCruiseVelocity(float maxMotionCruiseVelocity);  // in rotations per second
    void ConfigPeakOutput(double percentOutput);
    void ConfigNominalOutput(double nominalOutput);


  private:
    TalonSRX *m_talon;
    TALON_CONTROL_MODE m_controlMode;
    IDragonMotorController::TALON_TYPE m_type;

    int m_id;
    int m_countsPerRev;
    int m_tickOffset;
    double m_gearRatio;
};

typedef std::vector<DragonTalon*> DragonTalonVector;