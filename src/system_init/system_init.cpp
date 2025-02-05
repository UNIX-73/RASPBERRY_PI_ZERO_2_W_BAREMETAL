#include "system_init.hpp"

const void SYSTEM_LOOP::SYSTEM_INIT()
{
    this->core.InitializeCore();
    this->RunInitializeCallbacks();
}

const void SYSTEM_LOOP::SYSTEM_MAIN_LOOP()
{
    while (1)
    {
        this->RunMainLoopCallbacks();

        GPIO::SetPin(21);
    }
}

void SYSTEM_LOOP::InitializeSystem()
{
    this->SYSTEM_INIT();
    this->SYSTEM_MAIN_LOOP();
}
