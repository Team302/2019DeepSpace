/*
 * LidarFactory.cpp
 *
 */

#include <hw/LidarFactory.h>
#include <hw/DragonLidar.h>

LidarFactory* LidarFactory::m_lidarFactory = nullptr;
DragonLidar*  LidarFactory::m_backwardLidar = nullptr;
DragonLidar*  LidarFactory::m_forwardLidar = nullptr;


LidarFactory* LidarFactory::GetLidarFactory()
{
    if ( LidarFactory::m_lidarFactory == nullptr )
    {
        LidarFactory::m_lidarFactory = new LidarFactory();
    }
    return LidarFactory::m_lidarFactory;
}

DragonLidar* LidarFactory::GetLidar
(
    DragonLidar::LIDAR_USAGE    usage
)
{
    DragonLidar* lidar = nullptr;
    switch ( usage )
    {
        case DragonLidar::BACKWARD:
            lidar = LidarFactory::m_backwardLidar;
            break;

        case DragonLidar::FORWARD:
            lidar = LidarFactory::m_forwardLidar;
            break;

        default:
            break;
    }
    return lidar;
}

//=======================================================================================
// Method:          CreateLidar
// Description:     Create a lidar from the inputs
// Returns:         Void
//=======================================================================================
DragonLidar* LidarFactory::CreateLidar
(
    DragonLidar::LIDAR_USAGE    usage,
    int                         inputPin,
    int                         triggerPin
)
{
    DragonLidar* lidar = nullptr;
    switch ( usage )
    {
        case DragonLidar::BACKWARD:
            lidar = new DragonLidar( usage, inputPin, triggerPin );
            LidarFactory::m_backwardLidar = lidar;
            break;

        case DragonLidar::FORWARD:
            lidar = new DragonLidar( usage, inputPin, triggerPin );
            LidarFactory::m_forwardLidar = lidar;
            break;

        default:
            break;
    }

    return lidar;
}

