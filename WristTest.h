#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "subsys/Wrist.h"


class WristTest  {
 public:
  WristTest();
  void Run(Wrist::PLACEMENT_HEIGHT);
  bool IsDone();
  
  private:
  Wrist::PLACEMENT_HEIGHT m_prevhgt; 
  bool m_isDone = false;
  int m_counts = 0;

  Wrist* m_wrist;

  //TimeOut 400;
};

