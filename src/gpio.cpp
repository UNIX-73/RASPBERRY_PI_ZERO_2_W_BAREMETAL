#include "gpio.hpp"

GPIO::GPIO()
{
    this->gpio = reinterpret_cast<int *>(GPIO_BASE);
}

/**
 * function values can be 0 1 or 2. (0 input, 1 output, 2 alt)
 */
void GPIO::setFunction(int pin, int function)
{
    if (pin < 1 || pin > 40)
        return; //  TODO: El gestor de logs

    int fselRegister = pin / 10; // FSEL0, FSEL1, FSEL2...
    int shiftAmount = (pin % 10) * 3;

    gpio[fselRegister] &= ~(0b111 << shiftAmount);   // Limpia los 3 bits de función
    gpio[fselRegister] |= (function << shiftAmount); // Establece los 3 bits de función
}

void GPIO::setPin(int pin)
{
    int setRegister = pin / 32;
    int bitPosition = pin % 32;

    int *pSet = reinterpret_cast<int *>(GPIO_BASE + GPIO_SET_OFFSET);

    pSet[setRegister] = (1 << bitPosition);
}

void GPIO::clearPin(int pin)
{
    int clrRegister = pin / 32;
    int bitPosition = pin % 32;

    int *pClr = reinterpret_cast<int *>(GPIO_BASE + GPIO_CLR_OFFSET);

    pClr[clrRegister] = (1 << bitPosition);
}

void GPIO::readPin(int pin)
{
}
