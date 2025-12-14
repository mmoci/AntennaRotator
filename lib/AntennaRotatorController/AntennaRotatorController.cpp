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
        m_adjustmentTimer.trigger();
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
    auto selectedAngle{m_selector.getAngleDeg()};
    auto currentAngle{ m_motorSensor.getAngleDeg()};
    m_display.update(selectedAngle, currentAngle);
    Serial.printf("selectedAngle: %d, currentAngle: %d\n", selectedAngle, currentAngle);
}

void AntennaRotatorController::adjustPosition() noexcept
{
    // ensure timer duration is up-to-date before checking it
    m_adjustmentTimer.update();
    auto currentAngle {m_motorSensor.getAngleDeg()};
    auto deltaAngle {(m_targetAngle - currentAngle + RotaryEncoder::FULL_ROTATION) % RotaryEncoder::FULL_ROTATION};
    int signedDeltaAngle {(deltaAngle > 180) ? (deltaAngle - RotaryEncoder::FULL_ROTATION) : deltaAngle};
    int absDeltaAngle {std::abs(signedDeltaAngle)};
    int pwm {map(absDeltaAngle, 0, 180, MotorDriver::MIN_PWM, MotorDriver::MAX_PWM)};
    
    pwm = constrain(pwm, MotorDriver::MIN_PWM, MotorDriver::MAX_PWM);

    if(deltaAngle <= ANGLE_TOLERANCE || m_adjustmentTimer.getDuration() > ADJUSTMENT_TIMEOUT)
    {
        m_motor.stop();

        // If stop state takes more than 5sec we can consider adjustment of position successful (no oscilations), reset adjustment timer
        if(m_motor.isStopped() && m_motor.stoppedStateDuration() > MOTOR_STOPPED_TIMEOUT)
            m_adjustmentTimer.reset();
        return;
    }

    if(signedDeltaAngle > 0)
    {
        m_motor.rotateCW(pwm);
        
        #ifdef ENCODER_SIMULATION
        m_motorSensor.setAngle((++currentAngle + 360) % 360);
        #endif
    }
    else
    {
        m_motor.rotateCCW(pwm);

        #ifdef ENCODER_SIMULATION
        m_motorSensor.setAngle((--currentAngle + 360) % 360);
        #endif
    }
}