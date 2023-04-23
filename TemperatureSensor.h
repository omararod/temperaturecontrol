#pragma once
#include "ITemperatureSensor.h"
/**
 * @brief Implements the ITemperatureSensor as a software stub of a temperature sensor
 * 
 */
class TemperatureSensor : public ITemperatureSensor
{
    private:
        float TemperatureFunction();
        float m_time;
    public:
        /**
         * @brief Construct a new Temperature Sensor object
         * 
         */
        TemperatureSensor();
        /**
         * @brief Get the Temperature object. Prints a message indicating the current temperature
         * 
         * @return A float representing the current temperature
         */
        virtual float GetTemperature() override;

};