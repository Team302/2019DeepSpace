/*
 * DriveToLidarDistance.cpp
 *
 */

#include <auton/DriveDistance.h>
#include <auton/DriveToLidarDistance.h>
#include <auton/PrimitiveParams.h>
#include <hw/LidarFactory.h>

DriveToLidarDistance::DriveToLidarDistance() : m_lidar( nullptr )
{
    LidarFactory* factory = LidarFactory::GetLidarFactory();
    if ( factory != nullptr )
    {
        m_lidar = factory->GetLidar( DragonLidar::FORWARD_GRABBER );
    }
}


void DriveToLidarDistance::Init
(
    PrimitiveParams* params
)
{
    if ( m_lidar != nullptr )
    {
        params->SetDistance( m_lidar->GetDistance() );
        printf("dist %g \n", m_lidar->GetDistance() );
    }
    else
    {
    	printf("heyyy that lidar is nullptr \n");
    }

    DriveDistance::Init( params );
}

