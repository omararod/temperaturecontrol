#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IACSystem.h"
class ACSystemMock : public IACSystem
{
    MOCK_METHOD(void, TurnOn,(), (override));
    MOCK_METHOD(void, TurnOff,(), (override));
};
