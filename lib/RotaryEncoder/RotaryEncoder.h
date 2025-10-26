#pragma once
#include <Arduino.h>
#include <tuple>
#include <utility>
#include <atomic>

class RotaryEncoder
{
    public:
    RotaryEncoder(uint8_t swithPin, uint8_t pinA, uint8_t pinB);

    void init() noexcept;
    int readRotaryState() noexcept;
    uint8_t isButtonPressed() noexcept;

    private:
    static constexpr uint8_t BUTTON_DEBOUNCING_TIME {5};  // ms
    static constexpr uint8_t ROTARY_DEBOUNCING_TIME {2};  // ms
    static constexpr uint16_t FULL_ROTATION {360}; // 360 degrees
    std::tuple<uint8_t, uint8_t, uint8_t> m_pins{};
    std::atomic<int> m_position{0};
    std::atomic<uint8_t> m_buttonPressed{LOW};
    volatile unsigned long m_lastPinAInterrupt{};
    volatile unsigned long m_lastButtonPinInterrupt{};

    static void IRAM_ATTR handleButtonPinInterruptStaticWrapper(void* ptr);
    static void IRAM_ATTR handlePinAInterruptStaticWrapper(void* ptr);
    void IRAM_ATTR handleButtonPinInterrupt();
    void IRAM_ATTR handlePinAInterrupt();
};