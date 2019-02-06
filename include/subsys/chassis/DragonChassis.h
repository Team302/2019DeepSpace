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

class DragonChassis {
public:

    static DragonChassis* GetInstance();
    // Constructor
    DragonChassis
    (
        std::vector<IDragonMotorController*> motorControllers, // Motor controllers
        double wheelDiameter                                   // Diameter of the wheel
    );
    DragonChassis() = delete;           // Delete default constructor
    virtual ~DragonChassis() = default; // Default deconstructor

    // Getters
    double GetVelocity() const; // in inches per second
    double GetLeftVelocity() const;
    double GetRightVelocity() const;
    double GetDistance() const;
    
    // Setters
    void EnableBrakeMode(bool enabled);
    void SetDriveMode(IDragonMotorController::DRAGON_CONTROL_MODE controlMode);
    void SetLeftRightMagnitudes(double left, double right);
    void UpdateChassis(); // Run this once per cycle
    void EnableCurrentLimiting(bool enabled);

    void ResetChassis(); // Reset chassis will zero out the GetDistance method

private:
    double GetBestValue(double a, double b, double c) const; // Returns the value of the variabe closest to the average
    double GetLeftDistance() const;
    double GetRightDistance() const;

    // Motor controllers
    IDragonMotorController* m_frontLeft;
    IDragonMotorController* m_middleLeft;
    IDragonMotorController* m_backLeft;
    IDragonMotorController* m_frontRight;
    IDragonMotorController* m_middleRight;
    IDragonMotorController* m_backRight;

    double m_wheelDiameter;

    double m_leftDistanceOffset;
    double m_rightDistanceOffset;

    static DragonChassis*   m_instance;
};