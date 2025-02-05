#pragma once

#include "stdint64.h"

#define GPIO_BASE 0x3F200000
#define GPIO_FSEL_OFFSET 0x00 // 4GPIO fsel de {00}[000][000][000][000][000][000][000][000][000][000] 10 pines
#define GPIO_SET_OFFSET 0x1C
#define GPIO_CLR_OFFSET 0x28
#define GPIO_LEV_OFFSET 0x34
// Definimos las direcciones específicas para cada registro como macros
#define P_GPIO_BASE ((volatile uint32_t *)GPIO_BASE)
#define P_GPIO_FSEL ((volatile uint32_t *)(GPIO_BASE + GPIO_FSEL_OFFSET))
#define P_GPIO_SET ((volatile uint32_t *)(GPIO_BASE + GPIO_SET_OFFSET))
#define P_GPIO_CLR ((volatile uint32_t *)(GPIO_BASE + GPIO_CLR_OFFSET))
#define P_GPIO_LEV ((volatile uint32_t *)(GPIO_BASE + GPIO_LEV_OFFSET))

#define PIN_COUNT 40

namespace GPIO
{
    inline void SetFunctionSelect(uint32_t pin, uint32_t function)
    {
        if (pin < 0 || pin > 39)
            return; //  TODO: El gestor de logs

        int fselRegister = pin / 10; // FSEL0, FSEL1, FSEL2...
        int shiftAmount = (pin % 10) * 3;

        P_GPIO_BASE[fselRegister] &= ~(0b111 << shiftAmount);   // Limpia los 3 bits de función
        P_GPIO_BASE[fselRegister] |= (function << shiftAmount); // Establece los 3 bits de función
    }

    inline void SetPin(uint32_t pin)
    {
        if (pin < 0 || pin > 39)
            return;

        uint32_t setRegister = pin / 32;
        uint32_t bitPosition = pin % 32;

        P_GPIO_SET[setRegister] = (0b1 << bitPosition);
    };

    inline void ClearPin(uint32_t pin)
    {
        if (pin < 0 || pin > 39)
            return;

        uint32_t clrRegister = pin / 32;
        uint32_t bitPosition = pin % 32;

        P_GPIO_CLR[clrRegister] = (0b1 << bitPosition);
    };

    inline uint32_t ReadPin(uint32_t pin)
    {
        if (pin < 0 || pin > 39)
            return 0;

        uint32_t levRegister = pin / 32;
        uint32_t bitPosition = pin % 32;

        return (P_GPIO_LEV[levRegister] >> bitPosition) & 0b1;
    };
}
