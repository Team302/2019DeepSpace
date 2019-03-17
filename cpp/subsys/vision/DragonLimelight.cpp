/*
/*   Created by Austin Szczesniak
/*   Date: 1-19-2019
*/

#include "subsys/vision/DragonLimelight.h"
#include <vector>

DragonLimelight* DragonLimelight::m_instance = nullptr;

DragonLimelight::DragonLimelight() :
    table(NetworkTableInstance::GetDefault().GetTable("limelight"))
{}

std::vector<double> DragonLimelight::Get3DSolve()
{
    return table->GetNumberArray("camtran", 0);
}

double DragonLimelight::HasTarget()
{
    double v = table->GetNumber("tv", 0.0);
    return v;
}

double DragonLimelight::GetTargetHorizontalOffset()
{
    double x = table->GetNumber("tx", 0.0);
    return x;
}

double DragonLimelight::GetTargetVerticalOffset()
{
    double y = table->GetNumber("ty", 0.0);
    return y;
}

double DragonLimelight::GetTargetArea()
{
    double a = table->GetNumber("ta", 0.0);
    return a;
}

double DragonLimelight::GetTargetSkew()
{
    double s = table->GetNumber("ts", 0.0);
    return s;
}

double DragonLimelight::GetPipelineLatency()
{
    double l = table->GetNumber("tl", 0.0);
    return l;
}

void DragonLimelight::SetLEDMode(DragonLimelight::LED_MODE mode)
{
    table->PutNumber("ledMode", mode);
}

void DragonLimelight::SetCamMode(DragonLimelight::CAM_MODE mode)
{
    table->PutNumber("camMode", mode);
}

void DragonLimelight::SetPipeline(int pipeline)
{
    table->PutNumber("pipeline", pipeline);
}

void DragonLimelight::SetStreamMode(DragonLimelight::STREAM_MODE mode)
{
    table->PutNumber("stream", mode);
}

// MAX of 32 snapshots can be saved
void DragonLimelight::ToggleSnapshot(DragonLimelight::SNAPSHOT_MODE toggle)
{
    table->PutNumber("snapshot", toggle);
}

void DragonLimelight::PrintValues()
{
    printf("Has Target: %f \n", HasTarget());
    printf("X Offset: %f \n", GetTargetHorizontalOffset());
    printf("Y Offset: %f \n", GetTargetVerticalOffset());
    printf("Area: %f \n", GetTargetArea());
    printf("Skew: %f \n", GetTargetSkew());
    printf("Latency: %f \n", GetPipelineLatency());
}

DragonLimelight* DragonLimelight::GetInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new DragonLimelight();
    }

    return m_instance;
}