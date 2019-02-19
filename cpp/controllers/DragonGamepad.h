/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#ifndef SRC_MAIN_INCLUDE_COMMON_CONTROLLERS_DRAGONGAMEPAD_H_
#define SRC_MAIN_INCLUDE_COMMON_CONTROLLERS_DRAGONGAMEPAD_H_

#include <controllers/IDragonGamePad.h>
#include <controllers/axis/AnalogAxis.h>
#include <controllers/button/AnalogButton.h>
#include <controllers/button/IButton.h>

#include <frc/GenericHID.h>
#include <frc/Joystick.h>

class DragonGamepad : public IDragonGamePad
{
 public:
  DragonGamepad
  (
    int port
  );
  ~DragonGamepad();

  

  bool IsButtonPressed
  (
    BUTTON_IDENTIFIER button
  ) const override;

  void SetAxisDeadband
  (
    AXIS_IDENTIFIER axis,
    AXIS_DEADBAND type
  );

  void SetAxisProfile
  (
    AXIS_IDENTIFIER axis,
    AXIS_PROFILE curve
  );

  void SetAxisScale
  (
    AXIS_IDENTIFIER axis,
    float scaleFactor
  );

  void SetButtonMode
  (
    BUTTON_IDENTIFIER button,
    BUTTON_MODE mode
  );

  double GetRawAxis
  (
    AXIS_IDENTIFIER axis
  );

  bool IsRawButtonPressed
  (
    BUTTON_IDENTIFIER button
  );

  bool IsRawButtonPressed
  (
    ANALOG_BUTTON_IDENTIFIER button
  );

  float GetAxisValue
  (
    AXIS_IDENTIFIER axis
  ) const override;

  bool WasButtonPressed
  (
    BUTTON_IDENTIFIER button
  ) const override;

  bool WasButtonReleased
  (
    BUTTON_IDENTIFIER button
  ) const override;

  int GetPOVValue
  (

  );
  private:
  frc::Joystick* m_gamepad;
  AnalogAxis* m_axis[MAX_GAMEPAD_AXIS];
  AnalogButton* m_analogButtons[MAX_ANALOG_BUTTONS];
  IButton* m_button[MAX_BUTTONS];
 
  int m_count;
  const int 		m_maxAxis = 25;
	float			m_axisScale[25];
	float			m_axisInversionFactor[25];
	AXIS_PROFILE m_axisProfile[25];

  int LEFT_BUTTON_AXIS_ID = 0;
  int RIGHT_BUTTON_AXIS_ID = 1;

  const double			BUTTON_1_LOWERBAND = 0.118;
	const double			BUTTON_1_UPPERBAND = 0.1182;
	const int         BUTTON_1_AXIS      = 0;

  const double			BUTTON_2_LOWERBAND = 0.10;
	const double			BUTTON_2_UPPERBAND = 0.1182;
	const int         BUTTON_2_AXIS      = 1;

  const double			BUTTON_3_LOWERBAND = 0.102;
	const double			BUTTON_3_UPPERBAND = 0.10236221;
	const int         BUTTON_3_AXIS      = 0;

  const double			BUTTON_4_LOWERBAND = 0.077;
	const double			BUTTON_4_UPPERBAND = 0.08;
	const int         BUTTON_4_AXIS      = 1;

  const double			BUTTON_5_LOWERBAND = 0.1023;
	const double			BUTTON_5_UPPERBAND = 0.1026223;
	const int         BUTTON_5_AXIS      = 1;

  const double			BUTTON_6_LOWERBAND = 0.077;
	const double			BUTTON_6_UPPERBAND = 0.079;
	const int         BUTTON_6_AXIS      = 0; 

  const double			BUTTON_7_LOWERBAND = 0.054;
	const double			BUTTON_7_UPPERBAND = 0.056;
	const int         BUTTON_7_AXIS      = 1;

  const double			BUTTON_8_LOWERBAND = 0.054;
	const double			BUTTON_8_UPPERBAND = 0.056;
	const int         BUTTON_8_AXIS      = 0;

  const double			BUTTON_9_LOWERBAND = 0.03;
	const double			BUTTON_9_UPPERBAND = 0.032;
	const int         BUTTON_9_AXIS      = 1;

  const double			BUTTON_10_LOWERBAND = 0.030;
	const double			BUTTON_10_UPPERBAND = 0.032;
	const int         BUTTON_10_AXIS      = 0;

  const double			BUTTON_11_LOWERBAND = 0.014;
	const double			BUTTON_11_UPPERBAND = 0.016;
	const int         BUTTON_11_AXIS      = 1;

  const double			BUTTON_12_LOWERBAND = 0.014;
	const double			BUTTON_12_UPPERBAND = 0.016;
	const int         BUTTON_12_AXIS      = 0;

  const double			BUTTON_13_LOWERBAND = 0.10;
	const double			BUTTON_13_UPPERBAND = 0.1182;
	const int         BUTTON_13_AXIS      = 1;

  DragonGamepad() = delete;
};

#endif
