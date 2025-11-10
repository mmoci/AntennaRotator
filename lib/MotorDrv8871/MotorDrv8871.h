#include <Arduino.h>
#include "MotorDriver.h"

class MotorDrv8871 : public MotorDriver
{
    private:
    static constexpr uint16_t FULL_POWER {255};
    uint8_t m_pinIn1{}; 
    uint8_t m_pinIn2{};

    public:
    MotorDrv8871(uint8_t pinIn1, uint8_t pinIn2);
    
    void init() noexcept override;
    void rotateCW() noexcept override;
    void rotateCCW() noexcept override;
    void stop() noexcept override;
};