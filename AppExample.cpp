#include <memory>
#include <iostream>
#include <chrono>
#include <thread>

#include "TemperatureControl.h"
#include "TemperatureSensor.h"
#include "ACSystem.h"

std::string StateToString(ACState state)
{
    switch (state)
    {
    case ACState::idle:
        return "Idle";
    case ACState::cooling :
        return "Cooling";
    case ACState::heating :
        return "Heating";
    }

    return "Unknown";
}

int main()
{
    auto temperatureSensor = std::make_shared<TemperatureSensor>();
    auto cooler = std::make_shared<ACSystem>("cooler");
    auto heater = std::make_shared<ACSystem>("heater");
    TemperatureControl tc( temperatureSensor, cooler, heater);
    tc.SetMinTemperature(15.0);
    tc.SetMaxTemperature(25.0);
    while(1)
    {
        std::cout << "State: "<<StateToString(tc.GetACState())<< std::endl << 
                  "Min temperature: " << tc.GetMinTemperature() << std::endl << 
                  "Max temperature: " << tc.GetMaxTemperature() <<std::endl;
                  
        tc.Update();
        std::cout << "----"<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}