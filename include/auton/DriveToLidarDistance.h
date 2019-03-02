/*
 * DriveToLidarDistance.h
 *
 */

#ifndef SRC_AUTON_DRIVETOLIDARDISTANCE_H_
#define SRC_AUTON_DRIVETOLIDARDISTANCE_H_

#include <auton/DriveDistance.h>
#include <auton/PrimitiveParams.h>
#include <hw/DragonLidar.h>

class DriveToLidarDistance: public DriveDistance
{
    public:
        DriveToLidarDistance();
        virtual ~DriveToLidarDistance() = default;
        void Init(PrimitiveParams* params) override;

    private:
    DragonLidar*            m_lidar;

};

#endif /* SRC_AUTON_DRIVETOLIDARDISTANCE_H_ */
