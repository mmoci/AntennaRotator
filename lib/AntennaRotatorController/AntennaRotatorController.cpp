#include "AntennaRotatorController.h"

AntennaRotatorController::AntennaRotatorController(RotaryEncoder& selector, MagneticEncoder& motorSensor, MotorDriver& motor, AntennaDisplay& display) :
    m_selector{selector}, m_motorSensor{motorSensor}, m_motor{motor}, m_display{display}
{}

void AntennaRotatorController::init() noexcept
{
    m_selector.init();
    m_motorSensor.init();
    m_motor.init();
    m_display.init();

    m_selector.registerOnButtonPress([this](int targetAngle){
        m_targetAngle = targetAngle;
        Serial.println("Button pressed");

        #ifdef ENCODER_SIMULATION
        m_motorSensor.setAngle(targetAngle - 190);
        #endif
    });
}

void AntennaRotatorController::update() noexcept
{
    m_selector.updateButtonState();
    m_motorSensor.update();
    adjustPosition();
    m_display.update(m_selector.getAngleDeg(), m_motorSensor.getAngleDeg());
}

void AntennaRotatorController::adjustPosition() noexcept
{
    auto currentAngle {m_motorSensor.getAngleDeg()};
    auto deltaAngle {(m_targetAngle - currentAngle + RotaryEncoder::FULL_ROTATION) % RotaryEncoder::FULL_ROTATION};

    if(deltaAngle <= TOLERANCE)
    {
        m_motor.stop();
        Serial.println("Motor stopped...");
    }
    else if(deltaAngle <= 180)
    {
        m_motor.rotateCW();
        
        #ifdef ENCODER_SIMULATION
        m_motorSensor.setAngle((++currentAngle + 360) % 360);
        #endif
        
        Serial.println("Rotating CW...");
    }
    else
    {
        m_motor.rotateCCW();

        #ifdef ENCODER_SIMULATION
        m_motorSensor.setAngle((--currentAngle + 360) % 360);
        #endif
        
        Serial.println("Rotating CCW...");
    }
}