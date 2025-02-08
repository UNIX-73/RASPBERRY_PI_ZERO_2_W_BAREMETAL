#include "stdint64.h"
#include "../gpio/gpio.hpp"

// Definiciones de direcciones base (ajústalas según tu modelo y configuración)
#define PERIPHERAL_BASE 0x3F000000 // Puede variar en Pi 4 (0xFE000000)
#define UART0_BASE (PERIPHERAL_BASE + 0x201000)

#define UART0_DR_OFFSET 0x00
#define UART0_FR_OFFSET 0x18
#define UART0_IBRD_OFFSET 0x24
#define UART0_FBRD_OFFSET 0x28
#define UART0_LCRH_OFFSET 0x2C
#define UART0_CR_OFFSET 0x30
#define UART0_ICR_OFFSET 0x44

// Macros para acceder a los registros de UART
#define P_UART0_DR ((volatile uint32_t *)(UART0_BASE + UART0_DR_OFFSET))     // Data Register
#define P_UART0_FR ((volatile uint32_t *)(UART0_BASE + UART0_FR_OFFSET))     // Flag Register
#define P_UART0_IBRD ((volatile uint32_t *)(UART0_BASE + UART0_IBRD_OFFSET)) // Integer Baud Rate Divisor
#define P_UART0_FBRD ((volatile uint32_t *)(UART0_BASE + UART0_FBRD_OFFSET)) // Fractional Baud Rate Divisor
#define P_UART0_LCRH ((volatile uint32_t *)(UART0_BASE + UART0_LCRH_OFFSET)) // Line Control Register
#define P_UART0_CR ((volatile uint32_t *)(UART0_BASE + UART0_CR_OFFSET))     // Control Register
#define P_UART0_ICR ((volatile uint32_t *)(UART0_BASE + UART0_ICR_OFFSET))   // Interrupt Clear Register

namespace UART
{
    inline void UartInit()
    {
        // 1. Deshabilitar UART antes de configurarlo
        *P_UART0_CR = 0;

        // 2. Configurar los pines GPIO para UART
        GPIO::SetFunctionSelect(14, GPIO::FUNCTION_SELECT_OPTIONS::ALT0); // TX
        GPIO::SetFunctionSelect(15, GPIO::FUNCTION_SELECT_OPTIONS::ALT0); // RX

        GPIO::SetPullUpDown(14, 0); // Sin pull-up/down
        GPIO::SetPullUpDown(15, 0); // Sin pull-up/down

        // 3. Limpiar interrupciones pendientes
        *P_UART0_ICR = 0x7FF;

        // 4. Configurar la tasa de baudios
        *P_UART0_IBRD = 26; // Parte entera
        *P_UART0_FBRD = 3;  // Parte fraccionaria

        // 5. Configurar el formato del frame: 8 bits, sin paridad, 1 bit de stop
        *P_UART0_LCRH = (1 << 4) | (1 << 5) | (1 << 6); // FEN = 1 (FIFO enable), WLEN = 11 (8 bits)

        // 6. Habilitar UART, TX y RX
        *P_UART0_CR = (1 << 0) | (1 << 8) | (1 << 9); // UART Enable, TX Enable, RX Enable
    }

    inline void Send(char c)
    {
        while (*P_UART0_FR & (1 << 5)) // El bit 5 es el que indica si el FIFO está lleno
        {
            // TODO: interrupción creo
        }
        *P_UART0_DR = c;
    }

    inline void SendString(const char *str)
    {
        while (*str)
        {
            Send(*str++); // Envía el carácter actual
        }
    }
}
