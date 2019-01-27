/*
 * DoNothing.h
 *
 *  Created on: Jan 18, 2018
 *      Author: jonah (the cool guy)
 */

#ifndef SRC_AUTON_DONOTHING_H_
#define SRC_AUTON_DONOTHING_H_

//Team302 includes
#include <auton/PrimitiveParams.h>
#include <auton/IPrimitive.h>
#include <subsys/chassis/DragonChassis.h>

class DoNothing : public IPrimitive {
public:
	DoNothing();
	virtual ~DoNothing() = default;
	void Init(PrimitiveParams* params) override;
	void Run() override;
	bool IsDone() override;

private:
	float m_maxTime;			//Target time
	float m_currentTime;		//Time since init
	DragonChassis* m_chassis;	//chassis
};

#endif /* SRC_AUTON_DONOTHING_H_ */
