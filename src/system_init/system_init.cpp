#include "system_init.hpp"
#include "utils.h"

const void SYSTEM_LOOP::SYSTEM_INIT()
{
    this->core.InitializeCore();
    this->RunInitializeCallbacks();
}

const void SYSTEM_LOOP::SYSTEM_MAIN_LOOP()
{
    GPIO::SetFunctionSelect(21, GPIO::FUNCTION_SELECT_OPTIONS::OUTPUT);

    while (1)
    {
        GPIO::SetPin(21);
        UART::SendString("Hello world\r\n");
        Utils::Delay(5000000);
        GPIO::ClearPin(21);
        Utils::Delay(5000000);

        this->RunMainLoopCallbacks();
    }
}

void SYSTEM_LOOP::InitializeSystem()
{
    this->SYSTEM_INIT();
    this->SYSTEM_MAIN_LOOP();
}
