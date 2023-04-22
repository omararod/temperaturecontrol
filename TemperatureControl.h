#pragma once
#include <memory>

#include "ITemperatureSensor.h"
#include "IACSystem.h"

class TemperatureControl
{
private:
    std::shared_ptr<ITemperatureSensor> m_temperatureSensor;
    std::shared_ptr<IACSystem> m_cooler;
    std::shared_ptr<IACSystem> m_heater;


public:
    TemperatureControl(std::shared_ptr<ITemperatureSensor> temperatureSensor,
                       std::shared_ptr<IACSystem> cooler,
                       std::shared_ptr<IACSystem> heater);
    ~TemperatureControl();
};

