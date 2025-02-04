#pragma once

#define GPIO_BASE 0x3F200000
#define GPIO_FSEL_OFFSET 0x00 // 4GPIO fsel de {00}[000][000][000][000][000][000][000][000][000][000] 10 pines
#define GPIO_SET_OFFSET 0x1C
#define GPIO_CLR_OFFSET 0x28
#define GPIO_LEV_OFFSET 0x34

namespace P_GPIO
{
    volatile int *P_GPIO_BASE = reinterpret_cast<volatile int *>(GPIO_BASE);
    volatile int *P_GPIO_FSEL = reinterpret_cast<int *>(GPIO_BASE + GPIO_FSEL_OFFSET);
    volatile int *P_GPIO_SET = reinterpret_cast<int *>(GPIO_BASE + GPIO_SET_OFFSET);
    volatile int *P_GPIO_CLR = reinterpret_cast<int *>(GPIO_BASE + GPIO_CLR_OFFSET);
    volatile int *P_GPIO_LEV = reinterpret_cast<int *>(GPIO_BASE + GPIO_LEV_OFFSET);
}

namespace GPIO
{
    inline void SetFunctionSelect(int pin, int function)
    {
        if (pin < 1 || pin > 40)
            return; //  TODO: El gestor de logs

        int fselRegister = pin / 10; // FSEL0, FSEL1, FSEL2...
        int shiftAmount = (pin % 10) * 3;

        P_GPIO::P_GPIO_BASE[fselRegister] &= ~(0b111 << shiftAmount);   // Limpia los 3 bits de función
        P_GPIO::P_GPIO_BASE[fselRegister] |= (function << shiftAmount); // Establece los 3 bits de función
    }

    inline void SetPin(int pin)
    {
        if (pin < 1 || pin > 40)
            return;

        int setRegister = pin / 32;
        int bitPosition = pin % 32;

        P_GPIO::P_GPIO_SET[setRegister] = (0b1 << bitPosition);
    };

    inline void ClearPin(int pin)
    {
        int clrRegister = pin / 32;
        int bitPosition = pin % 32;

        P_GPIO::P_GPIO_CLR[clrRegister] = (0b1 << bitPosition);
    };

    inline int ReadPin(int pin)
    {
        int levRegister = pin / 32;
        int bitPosition = pin % 32;

        return (P_GPIO::P_GPIO_LEV[levRegister] >> bitPosition) & 0b1;
    };
}
