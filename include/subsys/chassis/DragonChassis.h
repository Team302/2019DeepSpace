/*
* DragonChassis.h
*
* Date Created: Jan 21, 2019
* Author: Jonah Shader
*/

#pragma once

// Includes
#include <vector>
#include "hw/IDragonMotorController.h"
#include "xmlhw/PIDData.h"

class DragonChassis {
public:
    // Constructor
    DragonChassis
    (
        IDragonMotorControllerVector motorControllers, // Motor controllers
        double wheelDiameter,
        double base,
        double track
    );
    DragonChassis() = delete;           // Delete default constructor
    virtual ~DragonChassis() = default; // Default deconstructor

    enum DRIVE_MODE
    {
        PERCENT_POWER,
        POSITION_INCHES,
        VELOCITY_INCH_SEC
    };

    // Singleton thingys
    static void CreateDragonChassis(IDragonMotorControllerVector motorControllers, double wheelDiameter, double base, double track);
    static DragonChassis* GetInstance();

    // Getters
    double GetVelocity() const; // in inches per second
    // double GetLeftVelocity() const;
    // double GetRightVelocity() const;
    double GetLeftMiddleVelocity() const;
    double GetRightMiddleVelocity() const;
    double GetDistance() const; // in inches
    // double GetLeftDistance() const;
    // double GetRightDistance() const;
    double GetLeftMiddleDistance() const;
    double GetRightMiddleDistance() const;
    
    // Setters
    void EnableBrakeMode(bool enabled);
    void SetDriveMode(DRIVE_MODE controlMode);
    void SetDriveMode(IDragonMotorController::DRAGON_CONTROL_MODE controlMode);
    void SetLeftRightMagnitudes(double left, double right);
    void UpdateChassis(); // Run this once per cycle
    void EnableCurrentLimiting(bool enabled);
    void SetVoltageRamping(double secondsToMax, double secondsToMaxClosedLoop = -1);
    void SetPID(PIDData* pidData);

    void ResetChassis(); // Reset chassis will zero out the GetDistance method

private:
    double GetBestValue(double a, double b, double c) const; // Returns the value of the variabe closest to the average

    static DragonChassis* m_dragonChassis;
    double m_wheelDiameter;
    double m_base;
    double m_track;

    DRIVE_MODE m_controlMode;

    // Motor controllers
    IDragonMotorController* m_frontLeft;
    IDragonMotorController* m_middleLeft;
    IDragonMotorController* m_backLeft;
    IDragonMotorController* m_frontRight;
    IDragonMotorController* m_middleRight;
    IDragonMotorController* m_backRight;


};