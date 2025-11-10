#pragma once

#include <Arduino.h>
#include <tuple>
#include <utility>
#include <atomic>

class RotaryEncoder
{
    public:
    using OnButtonPressCb = std::function<void(int)>;
    static constexpr uint16_t FULL_ROTATION {360}; // 360 degrees

    RotaryEncoder(uint8_t swithPin, uint8_t pinA, uint8_t pinB);

    void init() noexcept;
    int getAngleDeg() const noexcept;
    bool isButtonPressed() const noexcept;
    void updateButtonState() noexcept;
    void registerOnButtonPress(OnButtonPressCb onButtonPressCb);

    private:
    static constexpr uint8_t BUTTON_DEBOUNCING_TIME {20};  // ms
    static constexpr uint16_t ROTARY_DEBOUNCING_TIME {300};  // us (defalut: 200)
    std::tuple<uint8_t, uint8_t, uint8_t> m_pins{};
    std::atomic<int> m_position{0};
    volatile unsigned long m_lastPinAInterrupt{};
    uint8_t m_buttonPressed{LOW};
    uint8_t m_lastButtonState{HIGH};
    unsigned long m_lastButtonChangeTime{};
    OnButtonPressCb m_onButtonPressCb{};

    static void IRAM_ATTR handlePinAInterruptStaticWrapper(void* ptr);
    void IRAM_ATTR handlePinAInterrupt();
};