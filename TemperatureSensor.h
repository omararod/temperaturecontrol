#pragma once
#include "ITemperatureSensor.h"

class TemperatureSensor : public ITemperatureSensor
{
    public:
        virtual float GetTemperature() override;

};