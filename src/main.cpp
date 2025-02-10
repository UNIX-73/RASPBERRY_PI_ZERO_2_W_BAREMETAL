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

extern "C" void c_irq_handler()
{
    GPIO::SetPin(21);

    UART::SendString("An interruption arrived\r\n");
    *P_UART0_ICR = (1 << 4);
}
