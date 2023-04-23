#pragma once
#include <memory>

#include "ITemperatureSensor.h"
#include "IACSystem.h"
//Enumeration of the possible states of the system
enum ACState {idle, cooling, heating};
/**
 * @brief Implements a system that interacts with:
 * 1. A temperature sensor
 * 2. A cooling device
 * 3. A heating device
 * 
 * To control the temperature in a room. The behavior is the following:
 * - The system start in an idle state
 * - If the room is too cold (min temperature minus a margin), the heater turns on
 * - If the room is too hot (max temperature plus a margin), the cooler turns on
 * - When heating or cooling, if the temperature reaches the middle point between the min and max temperatures, the system returns to idle
 * 
 */
class TemperatureControl
{
private:
    /**
     * @brief An abstraction of a temperature sensor
     * 
     */
    std::shared_ptr<ITemperatureSensor> m_temperatureSensor;
    /**
     * @brief An abstarction of a cooling device
     * 
     */
    std::shared_ptr<IACSystem> m_cooler;
    /**
     * @brief An abstraction of a heating device
     * 
     */
    std::shared_ptr<IACSystem> m_heater;
    /**
     * @brief The minimum temperature to maintain
     * 
     */
    float m_minTemperature;
    /**
     * @brief The maximum temperature to maintain
     * 
     */
    float m_maxTemperature;
    /**
     * @brief A margin added to the min and max temperatures to avoid turning them on and off too often
     * 
     */
    float m_tempMargin;
    /**
     * @brief The current state of the system (idle, cooling, heating)
     * 
     */
    ACState m_ACState;
    /**
     * @brief Turns off all devices
     * 
     */
    void Shutdown();


public:
    /**
     * @brief Construct a new Temperature Control object
     * 
     * @param temperatureSensor pointer to an abstraction of a temperature sensor
     * @param cooler pointer to an abstraction of a cooling device
     * @param heater pointer to an abstraction of a heating device
     */
    TemperatureControl(std::shared_ptr<ITemperatureSensor> temperatureSensor,
                       std::shared_ptr<IACSystem> cooler,
                       std::shared_ptr<IACSystem> heater);
    ~TemperatureControl();

    /**
     * @brief Get the Min Temperature object
     * 
     * @return float 
     */
    float GetMinTemperature();
    /**
     * @brief Set the Min Temperature object
     * 
     * @param temperature : the target min temperature
     */
    void SetMinTemperature(float temperature);
    /**
     * @brief Get the Max Temperature object
     * 
     * @return float 
     */
    float GetMaxTemperature();
    /**
     * @brief Set the Max Temperature object
     * 
     * @param temperature : the target max temperature
     */
    void SetMaxTemperature(float temperature);
    /**
     * @brief Get the Temp Margin object
     * 
     * @return float 
     */
    float GetTempMargin();
    /**
     * @brief Set the Temp Margin object
     * 
     * @param margin 
     */
    void SetTempMargin(float margin);
    /**
     * @brief Get the current state of the system
     * 
     * @return ACState enumeration
     */
    ACState GetACState();
    /**
     * @brief Get the current temperature and activates or deactivates the heater/cooler if necessary. Updates the state of the system
     * 
     */
    void Update();

};

