#pragma once
/**
 * @brief This interface represent a temperature sensor installed in a room.
 * Implementations will typically represent a hardware abstraction layer
 * 
 */
class ITemperatureSensor
{
public:
    virtual ~ITemperatureSensor()  = default;
    /**
     * @brief Get the current temperature
     * 
     * @return Returns a float representing the current temperature 
     */
    virtual float GetTemperature() = 0;
};