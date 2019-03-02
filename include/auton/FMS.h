/*
 * FMS.h
 *
 *  Created on: Jan 27, 2018
 *      Author: Austin
 */

#ifndef SRC_AUTON_FMS_H_
#define SRC_AUTON_FMS_H_

#include <frc/DriverStation.h>

class FMS
{
public:
	enum POS
	{
		UNKNOWN = -1,
		LEFT,
		RIGHT
	};

	static FMS* GetFMS();

	POS GetSwitchPos();
	POS GetScalePos();
	POS GetOppSwitchPos();

	FMS();
	virtual ~FMS() = default;

private:
	// used for checking LR from FMS
	std::string gameData;
	// Pos vars
	POS switchPos;
	POS oppSwitchPos;
	POS scalePos;

	static FMS*	m_instance;
};

#endif /* SRC_AUTON_FMS_H_ */
