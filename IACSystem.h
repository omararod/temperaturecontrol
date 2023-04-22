#pragma once

class IACSystem
{
    public:
        virtual ~IACSystem() = default;
        virtual void TurnOn() = 0;
        virtual void TurnOff() = 0;
};
