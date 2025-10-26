#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(uint8_t swithPin, uint8_t pinA, uint8_t pinB) : 
    m_pins{std::make_tuple(swithPin, pinA, pinB)}
{}

void RotaryEncoder::init() noexcept
{
    pinMode(std::get<0>(m_pins), INPUT_PULLUP);
    pinMode(std::get<1>(m_pins), INPUT_PULLUP);
    pinMode(std::get<2>(m_pins), INPUT_PULLUP);
    attachInterruptArg(std::get<0>(m_pins), handleButtonPinInterruptStaticWrapper, this, FALLING); // Attached SW pin
    attachInterruptArg(std::get<1>(m_pins), handlePinAInterruptStaticWrapper, this, RISING); // Attached A pin
}

int RotaryEncoder::readRotaryState() noexcept
{
    auto position {m_position.load()};
    auto modifiedPosition{position};

    do 
    {
       modifiedPosition = (position + FULL_ROTATION) % FULL_ROTATION;
    } while (!m_position.compare_exchange_weak(position, modifiedPosition));

    return modifiedPosition;

    /* SIMPLER VERSION WITH POSSIBLE SKIPS
    auto position = m_position.load();
    auto modifiedPosition = (position + FULL_ROTATION) % FULL_ROTATION;
    m_position.store(modifiedPosition);
    return modifiedPosition;
    */
}

uint8_t RotaryEncoder::isButtonPressed() noexcept
{
    return m_buttonPressed.exchange(LOW);
}

void IRAM_ATTR RotaryEncoder::handleButtonPinInterruptStaticWrapper(void* ptr)
{
    static_cast<RotaryEncoder*>(ptr)->handleButtonPinInterrupt();
}

void IRAM_ATTR RotaryEncoder::handlePinAInterruptStaticWrapper(void* ptr)
{
    static_cast<RotaryEncoder*>(ptr)->handlePinAInterrupt();
}

void IRAM_ATTR RotaryEncoder::handleButtonPinInterrupt()
{
    unsigned long now = micros();
    if(now - m_lastButtonPinInterrupt > (BUTTON_DEBOUNCING_TIME * 1000UL))
    {
        m_buttonPressed = HIGH;
        m_lastButtonPinInterrupt = now;
    }
}

void IRAM_ATTR RotaryEncoder::handlePinAInterrupt()
{
    unsigned long now = micros();
    if (now - m_lastPinAInterrupt < (ROTARY_DEBOUNCING_TIME * 1000UL))
        return;

    uint8_t pinB {std::get<2>(m_pins)};
    int pinBState {digitalRead(pinB)};
    m_position += (pinBState) ? 1 : -1;
}