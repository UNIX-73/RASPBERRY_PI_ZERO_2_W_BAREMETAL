#include "stdint64.h"

namespace Utils
{
    inline void Delay(uint64_t times)
    {
        for (uint64_t i = 0; i < times; i++)
        {
            asm("nop");
        }
    }
} // namespace Utils
