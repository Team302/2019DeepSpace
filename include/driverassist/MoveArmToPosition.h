#pragma once

#include "subsys/Arm.h"
#include "subsys/Wrist.h"
#include "subsys/PlacementHeights.h"

class MoveArmToPosition
{
public:
    MoveArmToPosition();
    ~MoveArmToPosition() {};

    void SetTargetPosition(PlacementHeights::PLACEMENT_HEIGHT height, bool cargo, bool flip);
    void Update();
    void Cancel();
    bool IsDone();

private:
    enum MOVE_STATE
    {
        PULL_IN,
        MOVE_WIRST_ARM_TO_POS,
        PUSH_OUT,
        DONE,
        UNKNOWN_STATE = -1
    };

    MOVE_STATE m_currentState;

    // target set values
    PlacementHeights::PLACEMENT_HEIGHT m_targetPos;
    bool m_cargo;
    bool m_flip;

    // Mechanism
    Arm* m_arm;
    Wrist* m_wrist;

    // constants
    const double SAFE_INCHES = 4.0;
    const double ARM_THRESH = 30.0;
    const double DONE_ARM_THRESH = 10.0;
    const double DONE_WRIST_THRESH = 10.0;
    const double DONE_EXTEND_THRESH = 1.0;
};