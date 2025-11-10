#include "MotorDrvIBT2.h"

MotorDrvIBT2::MotorDrvIBT2(uint8_t pinRPWM, uint8_t pinLPWM) : 
    m_pinRPWM{pinRPWM}, 
    m_pinLPWM{pinLPWM}
{}

void MotorDrvIBT2::init() noexcept
{
    pinMode(m_pinRPWM, OUTPUT);
    pinMode(m_pinLPWM, OUTPUT);
}

void MotorDrvIBT2::rotateCW() noexcept
{
    digitalWrite(m_pinLPWM, LOW);
    analogWrite(m_pinRPWM, FULL_POWER);
}

void MotorDrvIBT2::rotateCCW() noexcept
{
    digitalWrite(m_pinRPWM, LOW);
    analogWrite(m_pinLPWM, FULL_POWER);
}

void MotorDrvIBT2::stop() noexcept
{
    digitalWrite(m_pinRPWM, LOW);
    digitalWrite(m_pinLPWM, LOW);
}