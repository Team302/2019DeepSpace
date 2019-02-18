/*
 * IMechanism.h
 */

#ifndef SRC_INTERFACES_IMECHANISM_H_
#define SRC_INTERFACES_IMECHANISM_H_

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
            MAX_MECHANISM_TYPES
        };

        enum MECHANISM_PARAM_TYPE
        {
            MECHANISM_PARAM_UNKNOWN = -1,
            WRIST_ANGLE_OFFSET,
            ARM_ANGLE_OFFSET,
            ARM_EXTENSION_OFFSET,
            HATCH_START_ANGLE,
            HATCH_FLOOR_ANGLE,
            HATCH_HP_ANGLE,
            HATCH_LOW_ANGLE,
            HATCH_MID_ANGLE,
            HATCH_HIGH_ANGLE,
            CARGO_START_ANGLE,
            CARGO_FLOOR_ANGLE,
            CARGO_HP_ANGLE,
            CARGO_SHIP_ANGLE,
            CARGO_LOW_ANGLE,
            CARGO_MID_ANGLE,
            CARGO_HIGH_ANGLE,
            HATCH_HP_EXTENSION,
            HATCH_MID_EXTENSION,
            HATCH_HIGH_EXTENSION,
            CARGO_FLOOR_EXTENSION,
            CARGO_HP_EXTENSION,
            CARGO_SHIP_EXTENSION,
            CARGO_LOW_EXTENSION,
            CARGO_MID_EXTENSION,
            CARGO_HIGH_EXTENSION,
            CARGO_INTAKE_SPEED_PARAM,
            CARGO_OUTTAKE_SPEED_PARAM,
            HATCH_INTAKE_SPEED_PARAM,
            HATCH_OUTTAKE_SPEED_PARAM,
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



#endif /* SRC_INTERFACES_IMECHANISM_H_ */