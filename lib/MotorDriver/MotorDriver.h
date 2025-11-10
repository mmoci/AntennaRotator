#pragma once

class MotorDriver
{
    public:
    virtual void init() noexcept = 0;
    virtual void rotateCW() noexcept = 0;
    virtual void rotateCCW() noexcept = 0;
    virtual void stop() noexcept = 0;

    virtual ~MotorDriver() = default;
};