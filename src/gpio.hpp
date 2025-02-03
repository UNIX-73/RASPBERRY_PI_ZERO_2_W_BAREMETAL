#pragma once

#define GPIO_BASE 0x3F200000
#define GPIO_FSEL_OFFSET 0x00 // 4GPIO fsel de {00}[000][000][000][000][000][000][000][000][000][000] 10 pines
#define GPIO_SET_OFFSET 0x1C
#define GPIO_CLR_OFFSET 0x28
#define GPIO_LEV_OFFSET 0x34

class GPIO
{
private:
    volatile int *gpio;

public:
    GPIO();
    void setFunction(int pin, int function);
    void setPin(int pin);
    void clearPin(int pin);
    void readPin(int pin);
};
