#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include <Wrist.cpp>

class WristTest  {
 public:
  WristTest();
  void Run(PLACEMENT_HEIGHT);
  bool IsDone();
  
  private:
  double m_prevhgt = KEEP_SAME;
  bool m_isDone = false;
  int m_counts = 0;


 private:
  TimeOut 400;
}

