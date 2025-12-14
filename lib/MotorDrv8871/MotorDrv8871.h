#pragma once

#include "MotorDriver.h"

class MotorDrv8871 : public MotorDriver
{
    private:
    uint8_t m_pinIn1{}; 
    uint8_t m_pinIn2{};

    public:
    MotorDrv8871(uint8_t pinIn1, uint8_t pinIn2);
    
    void init() noexcept override;
    void rotateCW(int pwm) noexcept override;
    void rotateCCW(int pwm) noexcept override;
    void stop() noexcept override;
};