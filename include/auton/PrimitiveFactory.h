/*
 * PrimitiveFactory.h
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */

#ifndef SRC_AUTON_PRIMITIVEFACTORY_H_
#define SRC_AUTON_PRIMITIVEFACTORY_H_

#include <auton/PrimitiveEnums.h>
#include <auton/PrimitiveParams.h>
#include <auton/IPrimitive.h>

class PrimitiveFactory {
public:


	PrimitiveFactory();
	virtual ~PrimitiveFactory();
	static PrimitiveFactory* GetInstance();
	IPrimitive* GetIPrimitive(PrimitiveParams* primitivePasser);

private:
    static PrimitiveFactory* m_instance;
    IPrimitive* m_doNothing;
    IPrimitive* m_driveTime;
    IPrimitive* m_driveDistance;
    IPrimitive* m_turnAngle;
    IPrimitive* m_holdPosition;
    IPrimitive* m_driveToWall;
    IPrimitive* m_driveLidarDistance;
};

#endif /* SRC_AUTON_PRIMITIVEFACTORY_H_ */
