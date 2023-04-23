#include "TemperatureControl.h"
#include <stdexcept>
#include <iostream>
TemperatureControl::TemperatureControl(std::shared_ptr<ITemperatureSensor> temperatureSensor,
                       std::shared_ptr<IACSystem> cooler,
                       std::shared_ptr<IACSystem> heater) :
                       m_temperatureSensor(temperatureSensor),
                       m_cooler(cooler),
                       m_heater(heater),
                       m_minTemperature(19.0),
                       m_maxTemperature(21.0),
                       m_tempMargin(0.5),
                       m_ACState(ACState::idle)
{
   
}

TemperatureControl::~TemperatureControl()
{
}

float TemperatureControl::GetMinTemperature()
{
    return m_minTemperature;
}
void TemperatureControl::SetMinTemperature(float temperature)
{
    m_minTemperature = temperature;
    if(m_minTemperature > m_maxTemperature)
    {
        m_maxTemperature = m_minTemperature;
    }
}
float TemperatureControl::GetMaxTemperature()
{
    return m_maxTemperature;
}
void TemperatureControl::SetMaxTemperature(float temperature)
{
    m_maxTemperature = temperature;
    if(m_maxTemperature < m_minTemperature)
    {
        m_minTemperature = m_maxTemperature;
    }
}

void TemperatureControl::SetTempMargin(float margin)
{
    m_tempMargin = margin;
}
float TemperatureControl::GetTempMargin()
{
    return m_tempMargin;
}
ACState TemperatureControl::GetACState()
{
    return m_ACState;
}

void TemperatureControl::Shutdown()
{
    m_cooler->TurnOff();
    m_heater->TurnOff();
}

void TemperatureControl::Update()
{
    auto temperature = m_temperatureSensor->GetTemperature();
    auto midPoint = (m_maxTemperature+m_minTemperature)/2.0;
    switch (m_ACState)
    {
    case ACState::idle:
                    
        if(temperature <= (m_minTemperature - m_tempMargin))
        {
            m_heater->TurnOn();
            m_ACState = ACState::heating;
        }
        if(temperature >= (m_maxTemperature + m_tempMargin))
        {
            m_cooler->TurnOn();
            m_ACState = ACState::cooling;
        }
    
        break;
    case ACState::cooling:
        if(temperature <= midPoint)
        {
            m_cooler->TurnOff();
            m_ACState = ACState::idle;
        }
        break;
    case ACState::heating:
        if(temperature >= midPoint)
        {
            m_heater->TurnOff();
            m_ACState = ACState::idle;
        }
        break;
    default:
        Shutdown();
        throw std::runtime_error("AC is in an unknown state");
    }
}