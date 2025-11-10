#include "MotorDrv8871.h"

MotorDrv8871::MotorDrv8871(uint8_t pinIn1, uint8_t pinIn2) : 
    m_pinIn1{pinIn1}, 
    m_pinIn2{pinIn2}
{}

void MotorDrv8871::init() noexcept
{
    pinMode(m_pinIn1, OUTPUT);
    pinMode(m_pinIn2, OUTPUT);
}

void MotorDrv8871::rotateCW() noexcept
{
    digitalWrite(m_pinIn2, LOW);
    analogWrite(m_pinIn1, FULL_POWER);
}

void MotorDrv8871::rotateCCW() noexcept
{
    digitalWrite(m_pinIn1, LOW);
    analogWrite(m_pinIn2, FULL_POWER);
}

void MotorDrv8871::stop() noexcept
{
    digitalWrite(m_pinIn1, LOW);
    digitalWrite(m_pinIn2, LOW);
}