#pragma once
class ITemperatureSensor
{
public:
    virtual ~ITemperatureSensor()  = default;
    virtual float GetTemperature() = 0;
};