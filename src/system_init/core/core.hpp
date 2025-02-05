#include "stdint64.h"
#include "gpio/gpio.hpp"

class CORE
{

public:
    void InitializeCore();

private:
    void InitializeGPIO();
    void InitializeUart();
};