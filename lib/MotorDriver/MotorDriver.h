#pragma once

#include "Utility.h"

class MotorDriver
{
    public:

    enum class State
    {
        STOPPED,
        CW,
        CCW
    };

    static constexpr uint16_t MIN_PWM = 400;  // ~40%
    static constexpr uint16_t MAX_PWM = 1023; // 100%

    bool isStopped() const noexcept {return m_state == State::STOPPED;}
    unsigned long stoppedStateDuration() const noexcept {return m_stoppedStateTimer.getDuration();}

    virtual void init() noexcept = 0;
    virtual void rotateCW(int pwm) noexcept = 0;
    virtual void rotateCCW(int pwm) noexcept = 0;
    virtual void stop() noexcept = 0;

    virtual ~MotorDriver() = default;

    protected:
    State m_state{State::STOPPED};
    Timer m_stoppedStateTimer{};

    // choose two different LEDC channels (0..15 supported on ESP32)
    static constexpr uint16_t PWM_FREQ = 20000;    // 20 kHz good for motors (adjust)
    static constexpr uint8_t PWM_RES_BITS = 10;    // 10-bit resolution -> duty 0..1023
    // choose channels (constants inside cpp)
    static constexpr uint8_t CH_IN1 = 0;
    static constexpr uint8_t CH_IN2 = 1;
};