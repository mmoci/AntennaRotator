#include "MagneticEncoder.h"

MagneticEncoder::MagneticEncoder(uint8_t i2cSclPin, uint8_t i2cSdaPin) : 
        m_i2cSclPin{i2cSclPin}, m_i2cSdaPin{i2cSdaPin}
{}

void MagneticEncoder::init() noexcept
{
    //Wire.begin(m_i2cSdaPin, m_i2cSclPin);
}

void MagneticEncoder::update() noexcept
{
    #ifdef ENCODER_SIMULATION

    #else
        Wire.beginTransmission(DEVICE_ADDRESS);
        Wire.write(REGISTER_ADDRESS_HIGH);
        Wire.endTransmission(false);
        Wire.requestFrom(DEVICE_ADDRESS, NUM_OF_BYTES);

        if (Wire.available() < NUM_OF_BYTES) return;

        int highByte {Wire.read()};
        int lowByte {Wire.read()};
        int rawValue {(highByte << 8) | lowByte};
        rawValue &= 0xFFF;

        m_angle = (rawValue * FULL_ROTATION / MAX_VALUE_12_BITS);
    #endif
}

int MagneticEncoder::getAngleDeg() const noexcept
{
    return m_angle;
}