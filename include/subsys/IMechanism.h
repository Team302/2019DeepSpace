/*
 * IMechanism.h
 */

#ifndef SRC_INTERFACES_IMECHANISM_H_
#define SRC_INTERFACES_IMECHANISM_H_

#include <vector>
#include <utility>

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
            MECHANISM_DATA_UNKNOWN=-1,
            WRIST_ANGLE_OFFSET,
            ARM_ANGLE_OFFSET,
            ARM_EXTENSION_OFFSET,
            MAX_MECHANISM_PARAM_TYPES
        };





        virtual IMechanism::MECHANISM_TYPE GetType() const = 0;

		IMechanism() = default;
		virtual ~IMechanism() = default;
};
typedef std::vector<IMechanism*> IMechanismVector;
typedef std::pair <IMechanism::MECHANISM_PARAM_TYPE, double> mechParamData;
typedef std::vector<mechParamData> mechParameters;


#endif /* SRC_INTERFACES_IMECHANISM_H_ */