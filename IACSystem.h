#pragma once
/**
 * @brief This interface represents a heating or cooling device. Implementations
 * will typically represent a hardware abstraction layer
 * 
 */
class IACSystem
{
    public:
        virtual ~IACSystem() = default;
        /**
         * @brief Turn On the heating or cooling device
         * 
         */
        virtual void TurnOn() = 0;
        /**
         * @brief Turn Off the heating or cooling device
         * 
         */
        virtual void TurnOff() = 0;
};
