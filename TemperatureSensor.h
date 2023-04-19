#pragma once
#include "ITemperatureSensor.h"

class TemperatureSensor : public ITemperatureSensor
{
    public:
        virtual ~TemperatureSensor() override;
        virtual float GetTemperature() override;

};