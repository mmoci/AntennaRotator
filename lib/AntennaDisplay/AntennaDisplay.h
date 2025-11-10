#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

class AntennaDisplay
{
    private:
    uint8_t m_i2cSclPin{};
    uint8_t m_i2cSdaPin{};
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C m_display;

    void drawGauge(int targetAngle, int currentAngle);

    public:
    AntennaDisplay(uint8_t i2cSclPin, uint8_t i2cSdaPin);

    void init();
    void update(int targetAngle, int currentAngle);
};