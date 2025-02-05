#include "system_init/system_init.hpp"

// Función de delay (bucle ocupado)
void delay(uint32_t count)
{
    for (volatile uint32_t i = 0; i < count; i++)
    {
        asm("nop"); // Instrucción NOP para evitar optimización
    }
}

extern "C" void main()
{

    SYSTEM_LOOP systemLoop;
    systemLoop.InitializeSystem();

    while (1)
    {
        asm("nop");
    }
}
