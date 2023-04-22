#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "TemperatureSensorMock.h"
#include "ACSystemMock.h"
#include "TemperatureControl.h"

class TemperatureControlTest : public testing::Test
{
    public:
        void SetUp() override
        {
            auto temperatureSensorMock = std::shared_ptr<TemperatureSensorMock>();
            m_temperatureSensor = temperatureSensorMock.get();

            auto coolerMock = std::shared_ptr<ACSystemMock>();
            m_cooler = coolerMock.get();

            auto heaterMock = std::shared_ptr<ACSystemMock>();
            m_heater = heaterMock.get();

            m_sut = std::make_unique<TemperatureControl>(temperatureSensorMock,coolerMock,heaterMock);
        }
    
    
    private:
        ITemperatureSensor *m_temperatureSensor;
        IACSystem *m_cooler;
        IACSystem *m_heater;

        std::unique_ptr<TemperatureControl> m_sut;
};

TEST(TemperatureControlTest, ConstructorWorks)
{
    
}
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 