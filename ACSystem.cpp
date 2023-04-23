#include <iostream>
#include "ACSystem.h"
ACSystem::ACSystem(std::string label) : m_label(label)
{}

void ACSystem::TurnOff()
{
    std::cout<<"====================================="<< std::endl;
    std::cout<<"Turning "+ m_label +" OFF "<< std::endl; 
    std::cout<<"====================================="<< std::endl;
}

void ACSystem::TurnOn()
{
    std::cout<<"====================================="<< std::endl;
    std::cout<<"Turning "+ m_label +" ON "<< std::endl; 
    std::cout<<"====================================="<< std::endl;
}