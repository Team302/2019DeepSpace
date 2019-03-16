/*
 * IMechanism.h
 */

#pragma once


#include <vector>
#include <xmlhw/PIDData.h>

class IMechanism
{
	public:

        enum MECHANISM_TYPE
        {
            UNKNOWN_MECHANISM = -1,
            WRIST,
            INTAKE,
            ARM,
            CLIMBER,
            HATCH_MANIPULATOR,
            MAX_MECHANISM_TYPES
        };

        enum MECHANISM_PARAM_TYPE
        {
            MECHANISM_PARAM_UNKNOWN = -1,
            LEGAL_STARTING_ANGLE,
            TEST_STARTING_ANGLE,
            EXTENDER_LEGAL_STARTING_INCHES,
            EXTENDER_TEST_STARTING_INCHES,
            HATCH_FLOOR_ANGLE,
            HATCH_HP_SECOND_ANGLE,
            HATCH_LOW_ANGLE,
            HATCH_MID_ANGLE,
            HATCH_HIGH_ANGLE,
            HATCH_LOW_SECOND_ANGLE,
            HATCH_MID_SECOND_ANGLE,
            HATCH_HIGH_SECOND_ANGLE,
            CARGO_FLOOR_ANGLE,
            CARGO_HP_ANGLE,
            CARGO_SHIP_ANGLE,
            CARGO_LOW_ANGLE,
            CARGO_MID_ANGLE,
            CARGO_HIGH_ANGLE,
            HATCH_FLOOR_EXTENSION,
            HATCH_HP_SECOND_EXTENSION,
            HATCH_LOW_EXTENSION,
            HATCH_MID_EXTENSION,
            HATCH_HIGH_EXTENSION,
            HATCH_LOW_SECOND_EXTENSION,
            HATCH_MID_SECOND_EXTENSION,
            HATCH_HIGH_SECOND_EXTENSION,
            CARGO_FLOOR_EXTENSION,
            CARGO_HP_EXTENSION,
            CARGO_HP_HOLE_EXTENSION,
            CARGO_SHIP_EXTENSION,
            CARGO_LOW_EXTENSION,
            CARGO_MID_EXTENSION,
            CARGO_HIGH_EXTENSION,
            CARGO_INTAKE_SPEED_PARAM,
            CARGO_OUTTAKE_SPEED_PARAM,
            HATCH_INTAKE_SPEED_PARAM,
            HATCH_OUTTAKE_SPEED_PARAM,
            SERVO_LOCKED_POSITION_PARAM,
            SERVO_DROPPED_POSITION_PARAM,
            HATCH_MECH_OPEN_ROTATIONS,
            MAX_MECHANISM_PARAM_TYPES
        };




        virtual MECHANISM_TYPE GetType() const = 0;
        virtual void SetParam
        (
            IMechanism::MECHANISM_PARAM_TYPE    param,          // <I> - parameter to set
            double                              value           // <I> - parameter value
        ) = 0;
        virtual void SetPID
        (
            PIDData*        pid                 // <I> - PID control information
        ) = 0;


		IMechanism() = default;
		virtual ~IMechanism() = default;
};
typedef std::vector<IMechanism*> IMechanismVector;



