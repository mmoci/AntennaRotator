#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "AntennaRotatorController.h"
#include "MotorDrv8871.h"

#define ENCODER_SIMULATION

static constexpr uint8_t SW_PIN = 5;
static constexpr uint8_t A_PIN = 18;
static constexpr uint8_t B_PIN = 19;
static constexpr uint8_t I2C_SCL_PIN = 22;
static constexpr uint8_t I2C_SDA_PIN = 21;
static constexpr uint8_t MOTOR_PIN_IN1 = 32;
static constexpr uint8_t MOTOR_PIN_IN2 = 33;

RotaryEncoder selector{SW_PIN, A_PIN,  B_PIN};
MagneticEncoder motorSensor{I2C_SCL_PIN, I2C_SCL_PIN};
AntennaDisplay display{I2C_SCL_PIN, I2C_SCL_PIN};
MotorDrv8871 driver{MOTOR_PIN_IN1, MOTOR_PIN_IN2};

AntennaRotatorController controller{selector, motorSensor, driver, display};

void setup() 
{
    Serial.begin(115200);
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    controller.init();
}

void loop() 
{
    controller.update();

    delay(3); // small delay to reduce Serial spam
}
