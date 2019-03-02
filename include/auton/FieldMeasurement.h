/*
 * FieldMeasurement.h
 *
 *  Created on: Mar 8, 2018
 *      Author: team302
 */


#ifndef FIELDMEASUREMENT_H_
#define FIELDMEASUREMENT_H_

#include <auton/FieldDefn.h>

class FieldMeasurement
{
public:
	static 	FieldMeasurement* GetFieldMeasurement();

	float distances[2] { 24, 34.5 }; // L Scale, R Scale, L Switch, R Switch

	enum Measurement
	{
		BLUE_SWITCH_RIGHT,
		BLUE_SWITCH_LEFT,
		BLUE_SCALE_RIGHT,
		BLUE_SCALE_LEFT,
		RED_SWITCH_RIGHT,
		RED_SWITCH_LEFT,
		RED_SCALE_RIGHT,
		RED_SCALE_LEFT,
		UNKNOWN_FIELD,
		MAX_POSITIONS
	};
	float GetXLoc(Measurement location);
	float GetYLoc(Measurement location);
	void AddLocation
	(
			Measurement location,
			float x,
			float y
	);
	float GetKeyPoint( Measurement keyPointLocation );
private:
	FieldMeasurement();
	virtual ~FieldMeasurement() =default;

	static FieldMeasurement* m_fieldMeasurement;

	float m_xLoc[9];
	float m_yLoc[9];
};

#endif /* FIELDMEASUREMENT_H_ */
