#include "hw/DragonSparkMax.h"

DragonSparkMax::DragonSparkMax(int id, CANSparkMax::MotorType motorType) :
    m_spark(new CANSparkMax(id, motorType)),
    m_controlMode(DRAGON_CONTROL_MODE::PERCENT_OUTPUT),
    m_rotationOffset(m_spark->GetEncoder().GetPosition())
{
}

double DragonSparkMax::GetRotations() const
{
    return m_spark->GetEncoder().GetPosition() - m_rotationOffset;
}

double DragonSparkMax::GetRPS() const
{
    return m_spark->GetEncoder().GetVelocity() / 60.0;
}

void DragonSparkMax::SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE mode)
{
    m_controlMode = mode;
}

void DragonSparkMax::Set(double value)
{
    switch (m_controlMode)
    {
        case DRAGON_CONTROL_MODE::PERCENT_OUTPUT:
            m_spark->Set(value);
        break;

        case DRAGON_CONTROL_MODE::ROTATIONS:
            m_spark->Set(value);
        break;

        case DRAGON_CONTROL_MODE::RPS:
            // TODO:
        break;

        default:
            // bad news if we are in the default branch... stop the motor
            m_spark->Set(0);
        break;
    }
}

void DragonSparkMax::SetRotationOffset(double rotations)
{
    m_rotationOffset = m_spark->GetEncoder().GetPosition() - rotations;
}

void DragonSparkMax::SetVoltageRamping(double ramping)
{
    m_spark->SetRampRate(ramping);
}

void DragonSparkMax::EnableCurrentLimiting(bool enabled)
{
    // TODO:
}

void DragonSparkMax::EnableBrakeMode(bool enabled)
{
    // TODO:
}

void DragonSparkMax::SetPIDF(double p, double i, double d, double f)
{
    // TODO:
}