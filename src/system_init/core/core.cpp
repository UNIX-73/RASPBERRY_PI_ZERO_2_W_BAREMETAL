#include "core.hpp"

void CORE::InitializeCore()
{
    this->InitializeGPIO();
}

void CORE::InitializeGPIO()
{
    GPIO::SetFunctionSelect(21, 1); //  Para testeo
}

void CORE::InitializeUart()
{
    
}
