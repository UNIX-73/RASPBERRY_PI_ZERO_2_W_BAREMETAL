#include "core.hpp"

void CORE::InitializeCore()
{
    this->InitializeUart();
}

void CORE::InitializeUart()
{
    UART::UartInit();
}
