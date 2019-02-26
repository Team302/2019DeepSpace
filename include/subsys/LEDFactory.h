/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "hw/LED.h"

class LEDFactory {
 public:
  enum LED_LOCATIONS
  {
    FRONT,
    BACK,
    TOP,
    UNKNOWN_LOCATION
  };
  static LEDFactory* GetLEDFactory();
  LED* GetLED
  (
    LED_LOCATIONS location
  );

  

  LED* CreateLEDs
  (
    LED_LOCATIONS location
  );

 private:
  LEDFactory();
	virtual ~LEDFactory();
  static LEDFactory* m_ledfactory;
	static LED* m_leds;
  LED* m_frontled;
  LED* m_backled;
  LED* m_topled;


};
