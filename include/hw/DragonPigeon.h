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
        static void CreatePigeon(int id);
        double GetPitch();
        double GetRoll();
        double GetYaw();

    private:
        DragonPigeon
        (
            int  canID
        );
        DragonPigeon() = delete;
        virtual ~DragonPigeon() = default;

        static DragonPigeon*        m_instance;
        PigeonIMU* m_pigeon;

        double m_initialRoll;
        double m_initialPitch;
        double m_initialYaw;

        // these methods correct orientation, but do not apply the initial offsets
        double GetRawRoll();
        double GetRawPitch();
        double GetRawYaw();
};

#endif /* SRC_SUBSYS_COMPONENTS_DRAGONPIGEON_H_ */


