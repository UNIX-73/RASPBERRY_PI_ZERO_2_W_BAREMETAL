#include "system_init.hpp"
#include "utils.h"
#define GICD_BASE 0xF0000000 // (Ejemplo, revisa tu SoC)
#define GICD_SGIR ((volatile uint32_t *)(GICD_BASE + 0xF00))
const void SYSTEM_LOOP::SYSTEM_INIT()
{
    this->core.InitializeCore();
    this->RunInitializeCallbacks();

    GPIO::SetFunctionSelect(21, GPIO::FUNCTION_SELECT_OPTIONS::OUTPUT);

    UART::SendString("SYSTEM_INIT\r\n");

    char buffer[100];

    UART::SendString("Send something:\r\n");

    while (true)
    {
        UART::ReceiveString(buffer, sizeof(buffer));
        UART::SendString("Received: ");
        UART::SendString(buffer);
        UART::SendString("\r\n");
    }
}

const void SYSTEM_LOOP::SYSTEM_MAIN_LOOP()
{
    while (1)
    {
        this->RunMainLoopCallbacks();
        asm("nop");
    }
}

void SYSTEM_LOOP::InitializeSystem()
{
    this->SYSTEM_INIT();
    this->SYSTEM_MAIN_LOOP();
}
