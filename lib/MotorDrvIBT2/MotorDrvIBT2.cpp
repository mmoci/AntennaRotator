#include "MotorDrvIBT2.h"

MotorDrvIBT2::MotorDrvIBT2(uint8_t pinRPWM, uint8_t pinLPWM) : 
    m_pinRPWM{pinRPWM}, 
    m_pinLPWM{pinLPWM}
{}

void MotorDrvIBT2::init() noexcept
{
    pinMode(m_pinRPWM, OUTPUT);
    pinMode(m_pinLPWM, OUTPUT);

    // setup PWM channels
    ledcSetup(CH_IN1, PWM_FREQ, PWM_RES_BITS);
    ledcSetup(CH_IN2, PWM_FREQ, PWM_RES_BITS);

    // attach pins to channels
    ledcAttachPin(m_pinRPWM, CH_IN1);
    ledcAttachPin(m_pinLPWM, CH_IN2);

    stop();
}

void MotorDrvIBT2::rotateCW(int pwm) noexcept
{
    Serial.println("Rotate CW (PWM)");
    ledcWrite(CH_IN2, LOW);
    ledcWrite(CH_IN1, pwm);
    m_state = State::CW;
    m_stoppedStateTimer.reset();
}

void MotorDrvIBT2::rotateCCW(int pwm) noexcept
{
    Serial.println("Rotate CCW (PWM)");
    ledcWrite(CH_IN1, LOW);
    ledcWrite(CH_IN2, pwm);
    m_state = State::CCW;
    m_stoppedStateTimer.reset();
}

void MotorDrvIBT2::stop() noexcept
{
    if(isStopped())
    {
        m_stoppedStateTimer.update();
        return;
    }

    Serial.println("Stop (coast)");
    ledcWrite(m_pinRPWM, LOW);
    ledcWrite(m_pinLPWM, LOW);
    m_stoppedStateTimer.trigger();
    m_state = State::STOPPED;
}