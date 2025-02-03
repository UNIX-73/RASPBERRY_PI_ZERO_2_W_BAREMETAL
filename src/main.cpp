#define GPIO_BASE   0x3F200000   // Dirección base del GPIO (Raspberry Pi 3/4)
#define GPIO_FSEL2  0x08         // Offset del registro de selección de función para GPIO 20-29
#define GPIO_SET0   0x1C         // Offset para establecer pines (GPSET0)
#define GPIO_CLR0   0x28         // Offset para limpiar pines (GPCLR0)

#define PIN21       (1 << 21)    // Máscara para el Pin 21
#define PIN29       (1 << 29)    // Máscara para el Pin 29

// Puntero base a los registros GPIO (memoria volátil)
volatile unsigned int *gpio = (volatile unsigned int *)GPIO_BASE;

// Función de delay (bucle ocupado)
void delay(int count) {
    for (volatile int i = 0; i < count; i++) {
        asm("nop");  // Instrucción NOP para evitar optimización
    }
}

extern "C" void main() {
    // Configurar GPIO 21 como salida
    gpio[GPIO_FSEL2 / 4] &= ~(0b111 << 3);  // Limpiar los bits del GPIO 21
    gpio[GPIO_FSEL2 / 4] |= (0b001 << 3);   // Configurar como salida (001)

    // Configurar GPIO 29 como salida
    gpio[GPIO_FSEL2 / 4] &= ~(0b111 << 27); // Limpiar los bits del GPIO 29 (27-29)
    gpio[GPIO_FSEL2 / 4] |= (0b001 << 27);  // Configurar como salida (001)

    // Apagar GPIO 29
    gpio[GPIO_CLR0 / 4] = PIN29;

    // Bucle infinito para parpadear el LED
    while (1) {
        gpio[GPIO_SET0 / 4] = PIN21;  // Encender GPIO 21
        delay(1000000);               
        gpio[GPIO_CLR0 / 4] = PIN21;  // Apagar GPIO 21
        delay(10000000);               
    }
}
