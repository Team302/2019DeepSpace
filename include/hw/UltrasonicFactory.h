/*
 * UltrasonicFactory.h
 *
 *  Created on: Feb 10, 2018
 *      Author: team302
 */

#ifndef SRC_FACTORIES_ULTRASONICFACTORY_H_
#define SRC_FACTORIES_ULTRASONICFACTORY_H_

#include <hw/DragonUltrasonic.h>

class UltrasonicFactory
{
	public:

			static UltrasonicFactory* GetUltrasonicFactory();
			DragonUltrasonic* GetDragonUltrasonic
			(
			     DragonUltrasonic::ULTRASONIC_USAGE  usage
			);

			//=======================================================================================
			// Method:  		CreateUltrasonic
			// Description:		Create an ultrasonic from the inputs
			// Returns:         Void
			//=======================================================================================
			DragonUltrasonic* CreateUltrasonic
			(
				DragonUltrasonic::ULTRASONIC_USAGE		usage,
				int								        analogInChannel
			);



	private:
		UltrasonicFactory();
		~UltrasonicFactory() = default;

		DragonUltrasonic*            m_left;
		DragonUltrasonic*            m_right;



		static UltrasonicFactory*	        m_ultrasonicFactory;
		static DragonUltrasonic*			m_ultrasonic;



};
/* namespace Ultrasonic */

#endif /* SRC_FACTORIES_ULTRASONICFACTORY_H_ */
