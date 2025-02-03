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

    GPIO gpio;
    gpio.setFunction(21, 1);

    while (1)
    {
        gpio.clearPin(21); // Encender GPIO 21
        delay(5000000);
        gpio.setPin(21); // Encender GPIO 21
        delay(5000000);
    }
}
