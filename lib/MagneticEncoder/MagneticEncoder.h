#pragma once

#include <Arduino.h>
#include <Wire.h>

class MagneticEncoder
{
    private:
    static constexpr int DEVICE_ADDRESS = 0x36;
    static constexpr int REGISTER_ADDRESS_HIGH = 0x0E;
    static constexpr int REGISTER_ADDRESS_LOW = 0x0F;
    static constexpr uint16_t NUM_OF_BYTES = 2;
    static constexpr uint16_t MAX_VALUE_12_BITS = 4095; // For 12bits range of values is [0-4095]
    static constexpr uint16_t FULL_ROTATION = 360;

    uint8_t m_i2cSclPin{};
    uint8_t m_i2cSdaPin{};
    int m_angle{};

    public:
    MagneticEncoder(uint8_t i2cSclPin, uint8_t i2cSdaPin);

    void init() noexcept;
    void update() noexcept;
    int getAngleDeg() const noexcept;
    
    #ifdef ENCODER_SIMULATION
    void setAngle(int angle)
    {
        m_angle = angle;
    }
    #endif
};