#include <cmath>
#include <iostream>
#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor() : m_time(0.0)
{}
float TemperatureSensor::TemperatureFunction()
{
    auto temp = (sinf(m_time)+1)* 14;
    m_time += 0.1;
    return temp;
}
float TemperatureSensor::GetTemperature()
{
    auto temp = TemperatureFunction();
    std::cout <<"Current temperature: " << temp << std::endl;
    return temp;
}