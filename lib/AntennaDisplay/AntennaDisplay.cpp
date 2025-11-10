#include "AntennaDisplay.h"

AntennaDisplay::AntennaDisplay(uint8_t i2cSclPin, uint8_t i2cSdaPin) :
    m_i2cSclPin{i2cSclPin}, 
    m_i2cSdaPin{i2cSdaPin}, 
    m_display{U8G2_R0, U8X8_PIN_NONE, i2cSclPin, i2cSdaPin}
{}


void AntennaDisplay::init()
{
    //Wire.begin(m_i2cSdaPin, m_i2cSclPin);
    m_display.begin();
    m_display.clearBuffer();
    m_display.sendBuffer();
}


void AntennaDisplay::update(int targetAngle, int currentAngle)
{
    // Here we could later add logic to choose what to draw (gauge, menu, etc.)
    drawGauge(targetAngle, currentAngle);
}

void AntennaDisplay::drawGauge(int targetAngle, int currentAngle)
{
    const int cx = 64;
    const int cy = 60;
    const int radius = 50;
    const int mainTicks = 5;
    const int minorTicks = 5;
    const int angleRange = 90;
    const float degPerTick = float(angleRange) / (mainTicks - 1);

    m_display.clearBuffer();

    // Draw target arrow
    const int arrowHalfWidth = 5;
    const int arrowHeight = 12;
    m_display.drawTriangle(
        cx - arrowHalfWidth, cy - radius + arrowHeight,
        cx + arrowHalfWidth, cy - radius + arrowHeight,
        cx, cy - radius
    );

    // Show target angle value
    char valStr[8];
    snprintf(valStr, sizeof(valStr), "%d°", targetAngle);
    m_display.setFont(u8g2_font_ncenB14_tr);
    int valWidth = m_display.getStrWidth(valStr);
    m_display.drawStr(cx - valWidth / 2, cy - radius + 30, valStr);

    // Draw gauge ticks
    for (int i = -mainTicks / 2; i <= mainTicks / 2; i++) {
        int tickValue = (targetAngle + i * 10 + 360) % 360;
        float angle = i * degPerTick;
        float rad = radians(angle);

        int x = cx + radius * sin(rad);
        int y = cy - radius * cos(rad);

        m_display.drawLine(x, y, x, y + 3);

        char buf[6];
        snprintf(buf, sizeof(buf), "%d", tickValue);
        m_display.setFont(u8g2_font_6x10_tr);
        m_display.drawStr(x - 6, y - 2, buf);

        if (i != mainTicks / 2) {
            for (int j = 1; j < minorTicks; j++) {
                float subAngle = rad + j * (degPerTick / minorTicks) * (PI / 180);
                int sx = cx + radius * sin(subAngle);
                int sy = cy - radius * cos(subAngle);
                m_display.drawPixel(sx, sy);
            }
        }
    }

    // Show textual info
    m_display.setFont(u8g2_font_6x12_tr);
    char textBuf[32]{};

    snprintf(textBuf, sizeof(textBuf), "CURRENT: %3d°", currentAngle);
    m_display.drawStr(5, 62, textBuf);

    m_display.sendBuffer();
}