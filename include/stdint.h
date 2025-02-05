#ifndef _STDINT_H_
#define _STDINT_H_

#ifdef __cplusplus
extern "C"
{
#endif

    // Tipos enteros con signo
    typedef signed char int8_t;
    typedef signed short int16_t;
    typedef signed int int32_t;
    typedef signed long long int64_t;

    // Tipos enteros sin signo
    typedef unsigned char uint8_t;
    typedef unsigned short uint16_t;
    typedef unsigned int uint32_t;
    typedef unsigned long long uint64_t;

    // Tipos enteros con al menos N bits
    typedef int8_t int_least8_t;
    typedef int16_t int_least16_t;
    typedef int32_t int_least32_t;
    typedef int64_t int_least64_t;

    typedef uint8_t uint_least8_t;
    typedef uint16_t uint_least16_t;
    typedef uint32_t uint_least32_t;
    typedef uint64_t uint_least64_t;

    // Tipos enteros más rápidos con al menos N bits
    typedef int8_t int_fast8_t;
    typedef int16_t int_fast16_t;
    typedef int32_t int_fast32_t;
    typedef int64_t int_fast64_t;

    typedef uint8_t uint_fast8_t;
    typedef uint16_t uint_fast16_t;
    typedef uint32_t uint_fast32_t;
    typedef uint64_t uint_fast64_t;

    // Punteros de tamaño entero
    typedef int32_t intptr_t;
    typedef uint32_t uintptr_t;

// Constantes de ancho fijo
#define INT8_MAX 0x7F
#define INT16_MAX 0x7FFF
#define INT32_MAX 0x7FFFFFFF
#define INT64_MAX 0x7FFFFFFFFFFFFFFFLL

#define INT8_MIN (-INT8_MAX - 1)
#define INT16_MIN (-INT16_MAX - 1)
#define INT32_MIN (-INT32_MAX - 1)
#define INT64_MIN (-INT64_MAX - 1)

#define UINT8_MAX 0xFF
#define UINT16_MAX 0xFFFF
#define UINT32_MAX 0xFFFFFFFFU
#define UINT64_MAX 0xFFFFFFFFFFFFFFFFULL

#ifdef __cplusplus
}
#endif

#endif // _STDINT_H_
