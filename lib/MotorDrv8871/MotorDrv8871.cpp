#include "MotorDrv8871.h"

MotorDrv8871::MotorDrv8871(uint8_t pinIn1, uint8_t pinIn2) : 
    m_pinIn1{pinIn1}, 
    m_pinIn2{pinIn2}
{}

void MotorDrv8871::init() noexcept
{
    pinMode(m_pinIn1, OUTPUT);
    pinMode(m_pinIn2, OUTPUT);

    // setup PWM channels
    ledcSetup(CH_IN1, PWM_FREQ, PWM_RES_BITS);
    ledcSetup(CH_IN2, PWM_FREQ, PWM_RES_BITS);

    // attach pins to channels
    ledcAttachPin(m_pinIn1, CH_IN1);
    ledcAttachPin(m_pinIn2, CH_IN2);

    stop();
}

void MotorDrv8871::rotateCW(int pwm) noexcept
{
    Serial.println("Rotate CW (PWM)");
    ledcWrite(CH_IN2, LOW);
    ledcWrite(CH_IN1, pwm);
    m_state = State::CW;
    m_stoppedStateTimer.reset();
}

void MotorDrv8871::rotateCCW(int pwm) noexcept
{
    Serial.println("Rotate CCW (PWM)");
    ledcWrite(CH_IN1, LOW);
    ledcWrite(CH_IN2, pwm);
    m_state = State::CCW;
    m_stoppedStateTimer.reset();
}

void MotorDrv8871::stop() noexcept
{
    if(isStopped())
    {
        m_stoppedStateTimer.update();
        return;
    }
    
    Serial.println("Stop (coast)");
    ledcWrite(CH_IN1, LOW);
    ledcWrite(CH_IN2, LOW);
    m_stoppedStateTimer.trigger();
    m_state = State::STOPPED;
}