#include <Arduino.h>
#include "RotaryEncoder.h"

static constexpr uint8_t SW_PIN = 5;
static constexpr uint8_t A_PIN = 18;
static constexpr uint8_t B_PIN = 19;


RotaryEncoder rotary{SW_PIN, A_PIN,  B_PIN};

void setup() 
{
    Serial.begin(115200);
    rotary.init();
}

void loop() 
{
    static int lastPos = 0;

    int pos = rotary.readRotaryState();
    if (pos != lastPos)
    {
        Serial.printf("Rotary position: %d\n", pos);
        lastPos = pos;
    }

    if (rotary.isButtonPressed() == HIGH)
    {
        Serial.println("Button pressed!");
    }

    delay(10); // small delay to reduce Serial spam
}
