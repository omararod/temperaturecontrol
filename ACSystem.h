#pragma once
#include "IACSystem.h"

class  ACSystem : public IACSystem
{
    public:
    ~ACSystem() = default;
    virtual void TurnOn() override;
    virtual void TurnOff() override;

};

