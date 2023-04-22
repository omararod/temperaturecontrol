#include "TemperatureControl.h"

TemperatureControl::TemperatureControl(std::shared_ptr<ITemperatureSensor> temperatureSensor,
                       std::shared_ptr<IACSystem> cooler,
                       std::shared_ptr<IACSystem> heater) :
                       m_temperatureSensor(temperatureSensor),
                       m_cooler(cooler),
                       m_heater(heater)
{
   
}

TemperatureControl::~TemperatureControl()
{
}
