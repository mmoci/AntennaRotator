#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(uint8_t swithPin, uint8_t pinA, uint8_t pinB) : 
    m_pins{std::make_tuple(swithPin, pinA, pinB)}
{}

void RotaryEncoder::init() noexcept
{
    pinMode(std::get<0>(m_pins), INPUT_PULLUP);
    pinMode(std::get<1>(m_pins), INPUT_PULLUP);
    pinMode(std::get<2>(m_pins), INPUT_PULLUP);
    attachInterruptArg(std::get<1>(m_pins), handlePinAInterruptStaticWrapper, this, RISING); // Attached A pin
}

void RotaryEncoder::registerOnButtonPress(OnButtonPressCb onButtonPressCb)
{
    m_onButtonPressCb = std::move(onButtonPressCb);
}

bool RotaryEncoder::isButtonPressed() const noexcept
{
    return m_buttonPressed;
}

void RotaryEncoder::updateButtonState() noexcept
{
    uint8_t currentState {static_cast<uint8_t>(digitalRead(std::get<0>(m_pins)))};

    if(m_lastButtonState != currentState)
    {
        m_lastButtonChangeTime = millis();
    }

    if(millis() - m_lastButtonChangeTime > BUTTON_DEBOUNCING_TIME)
    {
        if(!m_buttonPressed && !currentState) // Button was not pressed and new state reads LOW - i.e. that press occur.
        {
            m_buttonPressed = HIGH;
            if(m_onButtonPressCb) m_onButtonPressCb(getAngleDeg());
        }
        else if(m_buttonPressed && currentState)
            m_buttonPressed = LOW;
    }

    m_lastButtonState = currentState;
}

int RotaryEncoder::getAngleDeg() const noexcept
{
    return (m_position.load() + FULL_ROTATION) % FULL_ROTATION;
}

void IRAM_ATTR RotaryEncoder::handlePinAInterruptStaticWrapper(void* ptr)
{
    static_cast<RotaryEncoder*>(ptr)->handlePinAInterrupt();
}

void IRAM_ATTR RotaryEncoder::handlePinAInterrupt()
{
    unsigned long now = micros();
    if (now - m_lastPinAInterrupt < ROTARY_DEBOUNCING_TIME)
        return;

     m_lastPinAInterrupt = now;

    uint8_t pinB {std::get<2>(m_pins)};
    m_position.fetch_add((digitalRead(pinB)) ? 1 : -1, std::memory_order_relaxed);
}