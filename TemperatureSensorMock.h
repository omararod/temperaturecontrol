#pragma once
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ITemperatureSensor.h"

class TemperatureSensorMock : ITemperatureSensor
{
    public:
    virtual ~ITemperatureSensor() = default;
    MOCK_METHOD(float, GetTemperature, (), (override));
};

