/*
 * IMechanism.h
 */

#ifndef SRC_INTERFACES_IMECHANISM_H_
#define SRC_INTERFACES_IMECHANISM_H_

#include <vector>

class IMechanism
{
	public:

        enum MECHANISM_TYPE
        {
            UNKNOWN_MECHANISM = -1,
            WRIST,
            MAX_MECHANISM_TYPES
        };

        virtual IMechanism::MECHANISM_TYPE GetType() const = 0;

		IMechanism() = default;
		virtual ~IMechanism() = default;
};
typedef std::vector<IMechanism*> IMechanismVector;


#endif /* SRC_INTERFACES_IMECHANISM_H_ */