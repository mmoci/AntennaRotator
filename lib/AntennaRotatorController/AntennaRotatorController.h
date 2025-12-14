#pragma once

#include "RotaryEncoder.h"
#include "MagneticEncoder.h"
#include "MotorDriver.h"
#include "AntennaDisplay.h"
#include "Utility.h"

class AntennaRotatorController
{
    private:
    static constexpr int ANGLE_TOLERANCE{10}; // 10 degrees
    static constexpr unsigned long ADJUSTMENT_TIMEOUT {30000}; // 30sec
    static constexpr unsigned long MOTOR_STOPPED_TIMEOUT {5000}; // 5sec

    RotaryEncoder& m_selector;
    MagneticEncoder& m_motorSensor;
    MotorDriver& m_motor;
    AntennaDisplay& m_display;
    int m_targetAngle{};
    Timer m_adjustmentTimer{};

    void adjustPosition() noexcept;

    public:
    AntennaRotatorController(RotaryEncoder& selector, MagneticEncoder& motorSensor, MotorDriver& motor, AntennaDisplay& display);

    void init() noexcept;
    void update() noexcept;
};