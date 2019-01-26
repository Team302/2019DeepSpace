#pragma once
#include "hw/DragonTalon.h"
#include "ctre/Phoenix.h"
#include "subsys/PlacementHeights.h"
class Arm {
  public:
    Arm();
    virtual ~Arm();
    void MoveArmToPosition
    (
      PlacementHeights::PLACEMENT_HEIGHT armHeight,
      bool cargo
    );
    void RotateArmJoystick
    (
      double joystickVal
    ); //done
    void ExtendArmJoystick
    (
      double joystickVal
    ); //done
    void RotateArmToPosition
    (
      double position
    ); //done
    void ExtendArmPercentOutput
    (
      double armPower
    ); //done
    void ExtendArmPosition
    (
      double position
    ); //done
    void RotateArmPercentOutput
    (
      double extendArmPower
    ); //done
    void Hold();
    double GetArmRotations(); //done
    double GetArmVelocity(); //done
    bool IsOverRotated(); 


  private:
    enum TALON_TACH {
    UNKNOWN_TALON_TACH = -1,
    LOW_FRONT_TACH,
    HIGH_FRONT_TACH,
    LOW_REAR_TACH,
    HIGH_REAR_TACH
    };
    
    
    void RotateArmMotionMagic();
    void ZeroArmEncoder();
    bool GetTalonTach
    (
      Arm::TALON_TACH talonTach
    ); //done

    const double CARGO_POSITIONS[7] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    const double HATCH_POSITIONS[7] = {0.0, 1.0, 0.0, 0.0, 4.0, 5.0, 6.0}; 

    const double JOYSTICK_ROTATION_ARM_CONSTANT = 1.0;
    const double JOYSTICK_EXTENSION_CONSTANT = .5; 

    const double ARM_P = 0.0;
    const double ARM_I = 0.0;
    const double ARM_D = 0.0;
    const double ARM_F = 0.0;
    const double EXTEND_P = 0.0;
    const double EXTEND_I = 0.0;
    const double EXTEND_D = 0.0;
    const double EXTEND_F = 0.0;

    const float ROTATION_ARM_MAX_CRUISE_VELOCITY = 20; 
    const float ROTATION_ARM_MAX_ACCELERATION = 10;
    const float EXTENSION_MAX_CRUISE_VELOCITY = 20;
    const float EXTENSION_MAX_ACCELERATION = 10;

    const double MAX_ARM_ROTATION_FORWARD = .1;
    const double MAX_ARM_ROTATION_REVERSE = -.1;

    DragonTalon* m_leftArmRotationMotor;
    DragonTalon* m_rightArmRotationMotor;
    DragonTalon* m_armExtensionMotor;
    CANifier* m_canifier1;
    CANifier* m_canifier2;
    double m_startPosition;
    double m_rotationForwardMax;
    double m_rotationReverseMax;   
};