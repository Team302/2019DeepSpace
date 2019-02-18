/*
 * LidarFactory.h
 *
 */

#ifndef SRC_FACTORIES_LIDARFACTORY_H_
#define SRC_FACTORIES_LIDARFACTORY_H_

#include <hw/DragonLidar.h>

class LidarFactory
{
    public:
        static LidarFactory* GetLidarFactory();

        static DragonLidar* GetLidar
        (
            DragonLidar::LIDAR_USAGE    usage
        );

        //=======================================================================================
        // Method:          CreateLidar
        // Description:     Create a lidar from the inputs
        // Returns:         Void
        //=======================================================================================
        DragonLidar* CreateLidar
        (
            DragonLidar::LIDAR_USAGE    usage,
            int                         inputPin,
            int                         triggerPin
        );

    private:
        LidarFactory() = default;
        ~LidarFactory() = default;

        static LidarFactory*        m_lidarFactory;
        static DragonLidar*         m_backwardLidar;
        static DragonLidar*         m_forwardLidar;


};

#endif /* SRC_FACTORIES_LIDARFACTORY_H_ */
