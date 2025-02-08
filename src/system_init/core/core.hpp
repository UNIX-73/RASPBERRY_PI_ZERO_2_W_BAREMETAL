#include "stdint64.h"
#include "gpio/gpio.hpp"
#include "uart/uart.hpp"

class CORE
{

public:
    void InitializeCore();

private:
    void InitializeUart();
};