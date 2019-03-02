/*
 * CyclePrimitives.h
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */

#ifndef SRC_AUTON_CYCLEPRIMITIVES_H_
#define SRC_AUTON_CYCLEPRIMITIVES_H_

#include <auton/PrimitiveFactory.h>
#include <auton/AutonSelector.h>
#include <auton/IPrimitive.h>
#include <string>
#include <vector>

class CyclePrimitives {
public:
	CyclePrimitives();
	virtual ~CyclePrimitives() = default;

	void Init();
	void RunCurrentPrimitive();

protected:
	void GetNextPrim();
	void RunDoNothing();

private:
	std::vector<PrimitiveParams*> 	m_primParams;
	int 							m_currentPrimSlot;
	IPrimitive*						m_currentPrim;
	PrimitiveFactory* 				m_primFactory;
	IPrimitive* 					m_doNothing;
	AutonSelector* 					m_autonSelector;
};

#endif /* SRC_AUTON_CYCLEPRIMITIVES_H_ */
