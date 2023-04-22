#pragma once
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ITemperatureSensor.h"

class TemperatureSensorMock : public ITemperatureSensor
{
    public:
        MOCK_METHOD(float, GetTemperature, (), (override));
};

