#include "gpio/gpio.hpp"
// Función de delay (bucle ocupado)
void delay(int count)
{
    for (volatile int i = 0; i < count; i++)
    {
        asm("nop"); // Instrucción NOP para evitar optimización
    }
}

extern "C" void main()
{
    GPIO::SetFunctionSelect(21, 1);

    while (1)
    {
        GPIO::ClearPin(21); // Encender GPIO 21
        delay(5000000);
        GPIO::SetPin(21); // Encender GPIO 21
        delay(5000000);
    }
}
