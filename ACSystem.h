#pragma once
#include <string>
#include "IACSystem.h"
/**
 * @brief Implements the IACSystem interface as a stubbed version of a heating or cooling element.
 * 
 */
class  ACSystem : public IACSystem
{
    public:
        /**
         * @brief Construct a new ACSystem object
         * 
         * @param label Adds a label to identify the object instance. This label will be printed when calling TurnOn or TurnOff
         */
        ACSystem(std::string label);
        ~ACSystem() = default;
        /**
         * @brief Logically turns ON the heating or cooling device. It prints a message to indicate the change of state
         * 
         */
        virtual void TurnOn() override;
        /**
         * @brief Logically turns OFF the heating or cooling device. It prints a message to indicate the change of state
         * 
         */
        virtual void TurnOff() override;

    private:
        std::string m_label;


};

