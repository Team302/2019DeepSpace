/*
 * CyclePrimitives.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */
#include <frc/SmartDashboard/SmartDashboard.h>

#include <auton/CyclePrimitives.h>
#include <auton/PrimitiveFactory.h>
#include <auton/AutonSelector.h>
#include <auton/PrimitiveEnums.h>
#include <auton/PrimitiveParser.h>
#include <auton/PrimitiveParams.h>


CyclePrimitives::CyclePrimitives() :
		m_primParams(), m_currentPrimSlot(0), m_currentPrim(nullptr), m_primFactory(
				PrimitiveFactory::GetInstance()), m_doNothing(nullptr), m_autonSelector(
				new AutonSelector()) {
}

void CyclePrimitives::Init()
{
	m_currentPrimSlot = 0; //Reset current prim
	m_primParams.clear();
	m_primParams = PrimitiveParser::ParseXML( m_autonSelector->GetSelectedAutoFile() );

	if (!m_primParams.empty())
	{
		GetNextPrim();
	}

//	printf("Finished Cycle Prim Init");
}

void CyclePrimitives::RunCurrentPrimitive()
{
	if (m_currentPrim != nullptr)
	{
		m_currentPrim->Run();
		if (m_currentPrim->IsDone())
		{
			GetNextPrim();
		}
	}
	else
	{
		m_primParams.clear();	// clear the primitive params vector
		m_currentPrimSlot = 0;  //Reset current prim slot
		RunDoNothing();
	}
}

void CyclePrimitives::GetNextPrim()
{
	PrimitiveParams* currentPrimParam =
			(m_currentPrimSlot < (int) m_primParams.size()) ?
					m_primParams[m_currentPrimSlot] : nullptr;

	m_currentPrim =
			(currentPrimParam != nullptr) ?
					m_primFactory->GetIPrimitive(currentPrimParam) : nullptr;
	if (m_currentPrim != nullptr)
	{
		m_currentPrim->Init(currentPrimParam);
	}

	m_currentPrimSlot++;
}

void CyclePrimitives::RunDoNothing()
{
	if (m_doNothing == nullptr)
	{
		auto params = new PrimitiveParams( DO_NOTHING,          // identifier
		                                   100000.0,            // time
		                                   0.0,                 // distance
		                                   0.0,                 // target x location
		                                   0.0,                 // target y location
		                                   0.0,                 // heading
		                                   0.0,                 // start drive speed
		                                   0.0                  // end drive speed
						);             
		m_doNothing = m_primFactory->GetIPrimitive(params);
		m_doNothing->Init(params);
	}
	m_doNothing->Run();
}
