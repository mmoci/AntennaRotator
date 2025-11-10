#pragma once

#include "RotaryEncoder.h"
#include "MagneticEncoder.h"
#include "MotorDriver.h"
#include "AntennaDisplay.h"

class AntennaRotatorController
{
    private:
    static constexpr int TOLERANCE{3}; // 3 degrees

    RotaryEncoder& m_selector;
    MagneticEncoder& m_motorSensor;
    MotorDriver& m_motor;
    AntennaDisplay& m_display;
    int m_targetAngle{};

    void adjustPosition() noexcept;

    public:
    AntennaRotatorController(RotaryEncoder& selector, MagneticEncoder& motorSensor, MotorDriver& motor, AntennaDisplay& display);

    void init() noexcept;
    void update() noexcept;
};