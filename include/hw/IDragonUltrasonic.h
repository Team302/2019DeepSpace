/*
 * IDragonUltrasonic.h
 *
 *  Created on: Feb 15, 2018
 *      Author: jonah
 */

#ifndef SRC_INTERFACES_IDRAGONULTRASONIC_H_
#define SRC_INTERFACES_IDRAGONULTRASONIC_H_

class IDragonUltrasonic {
public:
	enum ULTRASONIC_USAGE {
		LEFT_SIDE_DISTANCE,
		RIGHT_SIDE_DISTANCE
	};

	IDragonUltrasonic() = default;
	virtual ~IDragonUltrasonic() = default;

	virtual double GetDistance() const = 0; //In inches
	virtual ULTRASONIC_USAGE GetUsage() const = 0;
};

#endif /* SRC_INTERFACES_IDRAGONULTRASONIC_H_ */
