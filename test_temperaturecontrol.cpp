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
            auto temperatureSensorMock = std::make_shared<TemperatureSensorMock>();
            m_temperatureSensor = temperatureSensorMock.get();

            auto coolerMock = std::make_shared<ACSystemMock>();
            m_cooler = coolerMock.get();

            auto heaterMock = std::make_shared<ACSystemMock>();
            m_heater = heaterMock.get();

            m_sut = std::make_unique<TemperatureControl>(temperatureSensorMock,coolerMock,heaterMock);
        }
    
    
    
    TemperatureSensorMock *m_temperatureSensor;
    ACSystemMock *m_cooler;
    ACSystemMock *m_heater;

    std::unique_ptr<TemperatureControl> m_sut;
};

TEST_F(TemperatureControlTest, DefaultConstructorHasCorrectDefaultValues)
{
    EXPECT_FLOAT_EQ(m_sut->GetMinTemperature(),19.0);
    EXPECT_FLOAT_EQ(m_sut->GetMaxTemperature(),21.0);
    EXPECT_FLOAT_EQ(m_sut->GetTempMargin(),0.5);
    EXPECT_FLOAT_EQ(m_sut->GetACState(),ACState::idle);
}
TEST_F(TemperatureControlTest, SetMinTemperatureReducesMinTemperature)
{
    EXPECT_FLOAT_EQ(m_sut->GetMinTemperature(),19.0);
    m_sut->SetMinTemperature(18.7);
    EXPECT_FLOAT_EQ(m_sut->GetMinTemperature(),18.7);
    
}
TEST_F(TemperatureControlTest, SetMinTemperatureIncreasesMinTemperature)
{
    EXPECT_FLOAT_EQ(m_sut->GetMinTemperature(),19.0);
    m_sut->SetMinTemperature(19.5);
    EXPECT_FLOAT_EQ(m_sut->GetMinTemperature(),19.5);
    
}
TEST_F(TemperatureControlTest,SetMinTemperatureAdjustsMaxTemperature)
{
    EXPECT_FLOAT_EQ(m_sut->GetMinTemperature(),19.0);
    EXPECT_FLOAT_EQ(m_sut->GetMaxTemperature(),21.0);

    m_sut->SetMinTemperature(21.5);

    EXPECT_FLOAT_EQ(m_sut->GetMinTemperature(),m_sut->GetMaxTemperature());
}
TEST_F(TemperatureControlTest, SetMaxTemperatureReducesMaxTemperature)
{
    EXPECT_FLOAT_EQ(m_sut->GetMaxTemperature(),21.0);
    m_sut->SetMaxTemperature(20.5);
    EXPECT_FLOAT_EQ(m_sut->GetMaxTemperature(),20.5);
    
}
TEST_F(TemperatureControlTest, SetMaxTemperatureIncreasesMaxTemperature)
{
    EXPECT_FLOAT_EQ(m_sut->GetMaxTemperature(),21.0);
    m_sut->SetMaxTemperature(21.5);
    EXPECT_FLOAT_EQ(m_sut->GetMaxTemperature(),21.5);
}
TEST_F(TemperatureControlTest,SetaxTemperatureAdjustsMinTemperature)
{
    EXPECT_FLOAT_EQ(m_sut->GetMinTemperature(),19.0);
    EXPECT_FLOAT_EQ(m_sut->GetMaxTemperature(),21.0);

    m_sut->SetMaxTemperature(18.5);

    EXPECT_FLOAT_EQ(m_sut->GetMinTemperature(),m_sut->GetMaxTemperature());
}
TEST_F(TemperatureControlTest,SetTempMarginDecreasesTempMargin)
{
    EXPECT_FLOAT_EQ(m_sut->GetTempMargin(),0.5);

    m_sut->SetTempMargin(0.3);

    EXPECT_FLOAT_EQ(m_sut->GetTempMargin(),0.3);
}
TEST_F(TemperatureControlTest,SetTempMarginIncreasesTempMargin)
{
    EXPECT_FLOAT_EQ(m_sut->GetTempMargin(),0.5);

    m_sut->SetTempMargin(1.0);

    EXPECT_FLOAT_EQ(m_sut->GetTempMargin(),1.0);
}
TEST_F(TemperatureControlTest,HeaterTurnsOnWhenItsCold)
{
    EXPECT_CALL(*m_temperatureSensor, GetTemperature()).Times(1).WillRepeatedly(testing::Return(0.0));
    EXPECT_CALL(*m_heater,TurnOn());

    m_sut->Update();
    EXPECT_EQ(m_sut->GetACState(),ACState::heating);
}
TEST_F(TemperatureControlTest,HeaterDoesntTurnsOnWhenColdButWithinMargin)
{
    EXPECT_CALL(*m_temperatureSensor, GetTemperature()).Times(1).WillRepeatedly(testing::Return(m_sut->GetMinTemperature()));
    m_sut->Update();
    EXPECT_EQ(m_sut->GetACState(),ACState::idle);
}

TEST_F(TemperatureControlTest,HeaterTurnsOffWhenMidPointIsReached)
{
    auto midPoint = (m_sut->GetMinTemperature()+m_sut->GetMaxTemperature())/2.0;
    EXPECT_CALL(*m_temperatureSensor, GetTemperature()).Times(2)
                .WillOnce(testing::Return(0.0))
                .WillOnce(testing::Return(midPoint));
    EXPECT_CALL(*m_heater,TurnOn());
    EXPECT_CALL(*m_heater,TurnOff());
    //Start heating                
    m_sut->Update();
    EXPECT_EQ(m_sut->GetACState(),ACState::heating);
    //stop heating
    m_sut->Update();
    EXPECT_EQ(m_sut->GetACState(),ACState::idle);
}
TEST_F(TemperatureControlTest,HeaterTurnsOffWhenMidPointIsSlightlySurpassed)
{
    auto midPoint = (m_sut->GetMinTemperature()+m_sut->GetMaxTemperature())/2.0;
    EXPECT_CALL(*m_temperatureSensor, GetTemperature()).Times(2)
                .WillOnce(testing::Return(0.0))
                .WillOnce(testing::Return(midPoint+0.5));
    EXPECT_CALL(*m_heater,TurnOn());
    EXPECT_CALL(*m_heater,TurnOff());
    //Start heating                
    m_sut->Update();
    EXPECT_EQ(m_sut->GetACState(),ACState::heating);
    //stop heating
    m_sut->Update();
    EXPECT_EQ(m_sut->GetACState(),ACState::idle);
}
TEST_F(TemperatureControlTest,HeaterTurnsOffWhenMidPointIsGreatlySurpassed)
{
    auto midPoint = (m_sut->GetMinTemperature()+m_sut->GetMaxTemperature())/2.0;
    EXPECT_CALL(*m_temperatureSensor, GetTemperature()).Times(2)
                .WillOnce(testing::Return(0.0))
                .WillOnce(testing::Return(midPoint+100));
    EXPECT_CALL(*m_heater,TurnOn());
    EXPECT_CALL(*m_heater,TurnOff());
    //Start heating                
    m_sut->Update();
    EXPECT_EQ(m_sut->GetACState(),ACState::heating);
    //stop heating
    m_sut->Update();
    EXPECT_EQ(m_sut->GetACState(),ACState::idle);
}
TEST_F(TemperatureControlTest,CoolerTurnsOnWhenItsHot)
{
    EXPECT_CALL(*m_temperatureSensor, GetTemperature()).Times(1).WillRepeatedly(testing::Return(100));
    EXPECT_CALL(*m_cooler,TurnOn());
    m_sut->Update();
}
TEST_F(TemperatureControlTest,CoolerDoesntTurnsOnWhenHotButWithinMargin)
{
    EXPECT_CALL(*m_temperatureSensor, GetTemperature()).Times(1).WillRepeatedly(testing::Return(m_sut->GetMaxTemperature()));
    m_sut->Update();
    EXPECT_EQ(m_sut->GetACState(),ACState::idle);
}
TEST_F(TemperatureControlTest,CoolerTurnsOffWhenMidPointIsReached)
{
    auto midPoint = (m_sut->GetMinTemperature()+m_sut->GetMaxTemperature())/2.0;
    EXPECT_CALL(*m_temperatureSensor, GetTemperature()).Times(2)
                .WillOnce(testing::Return(100.0))
                .WillOnce(testing::Return(midPoint));
    EXPECT_CALL(*m_cooler,TurnOn());
    EXPECT_CALL(*m_cooler,TurnOff());
    //Start cooling                
    m_sut->Update();
    EXPECT_EQ(m_sut->GetACState(),ACState::cooling);
    //stop cooling
    m_sut->Update();
    EXPECT_EQ(m_sut->GetACState(),ACState::idle);
}
TEST_F(TemperatureControlTest,CoolerTurnsOffWhenMidPointIsSlightlySurpassed)
{
    auto midPoint = (m_sut->GetMinTemperature()+m_sut->GetMaxTemperature())/2.0;
    EXPECT_CALL(*m_temperatureSensor, GetTemperature()).Times(2)
                .WillOnce(testing::Return(100.0))
                .WillOnce(testing::Return(midPoint-0.5));
    EXPECT_CALL(*m_cooler,TurnOn());
    EXPECT_CALL(*m_cooler,TurnOff());
    //Start cooling                
    m_sut->Update();
    EXPECT_EQ(m_sut->GetACState(),ACState::cooling);
    //stop cooling
    m_sut->Update();
    EXPECT_EQ(m_sut->GetACState(),ACState::idle);
}
TEST_F(TemperatureControlTest,CoolerTurnsOffWhenMidPointIsGreatlySurpassed)
{
    auto midPoint = (m_sut->GetMinTemperature()+m_sut->GetMaxTemperature())/2.0;
    EXPECT_CALL(*m_temperatureSensor, GetTemperature()).Times(2)
                .WillOnce(testing::Return(100.0))
                .WillOnce(testing::Return(midPoint-100.0));
    EXPECT_CALL(*m_cooler,TurnOn());
    EXPECT_CALL(*m_cooler,TurnOff());
    //Start cooling                
    m_sut->Update();
    EXPECT_EQ(m_sut->GetACState(),ACState::cooling);
    //stop cooling
    m_sut->Update();
    EXPECT_EQ(m_sut->GetACState(),ACState::idle);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 