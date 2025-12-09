#include <Arduino.h>
#include "MotorDriver.h"

class MotorDrvIBT2 : public MotorDriver
{
    private:
    uint8_t m_pinRPWM{}; 
    uint8_t m_pinLPWM{};

    public:
    MotorDrvIBT2(uint8_t pinRPWM, uint8_t pinLPWM);
    
    void init() noexcept override;
    void rotateCW(int pwm) noexcept override;
    void rotateCCW(int pwm) noexcept override;
    void stop() noexcept override;
};