/*
 * DragonPigeon.h
 *
 *  Created on: Feb 3, 2018
 *      Author: team302
 */

#ifndef SRC_SUBSYS_COMPONENTS_DRAGONPIGEON_H_
#define SRC_SUBSYS_COMPONENTS_DRAGONPIGEON_H_

#include <string>
#include <vector>

#include <ctre/phoenix/Sensors/PigeonIMU.h>

using namespace ctre::phoenix::sensors;

class DragonPigeon : public PigeonIMU
{
    public:

        static DragonPigeon* GetPigeon();
        double GetPitch();
        double GetRoll();
        double GetYaw();
        DragonPigeon
        (
            int  canID
        );
    private:

        virtual ~DragonPigeon() = default;
        DragonPigeon() = delete;



        static DragonPigeon*        m_instance;
        PigeonIMU* m_pigeon;
};

#endif /* SRC_SUBSYS_COMPONENTS_DRAGONPIGEON_H_ */


