#include <Arduino.h>
#include "MotorDriver.h"

class MotorDrvIBT2 : public MotorDriver
{
    private:
    static constexpr uint16_t FULL_POWER {255};
    uint8_t m_pinRPWM{}; 
    uint8_t m_pinLPWM{};

    public:
    MotorDrvIBT2(uint8_t pinRPWM, uint8_t pinLPWM);
    
    void init() noexcept override;
    void rotateCW() noexcept override;
    void rotateCCW() noexcept override;
    void stop() noexcept override;
};