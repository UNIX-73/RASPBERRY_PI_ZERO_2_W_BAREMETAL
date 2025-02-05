#pragma once
#include "core/core.hpp"

#define MAX_INITIALIZE_CALLBACKS 64
#define MAX_MAIN_LOOP_CALLBACKS 64

class SYSTEM_LOOP
{
private:
    // Arrays para almacenar los callbacks (funciones de inicialización y loop)
    CORE core;

    void (*InitializeCallbacks[64])(); // Callback para inicialización
    void (*MainLoopCallbacks[64])();   // Callback para loop principal

    uint32_t initializeCount = 0; // Contador para saber cuántos callbacks hay
    uint32_t mainLoopCount = 0;   // Contador para los callbacks del loop

    // Ejecutar todos los callbacks de inicialización
    inline void RunInitializeCallbacks()
    {
        for (uint32_t i = 0; i < initializeCount; i++)
        {
            InitializeCallbacks[i]();
        }
    }

    // Ejecutar todos los callbacks del loop principal
    inline void RunMainLoopCallbacks()
    {
        for (uint32_t i = 0; i < mainLoopCount; i++)
        {
            MainLoopCallbacks[i](); // Ejecutar cada callback del loop
        }
    }

    const void SYSTEM_INIT();
    const void SYSTEM_MAIN_LOOP();

public:
    void SetInitializeCallback(void (*callback)())
    {
        if (initializeCount < MAX_INITIALIZE_CALLBACKS)
        {
            InitializeCallbacks[initializeCount++] = callback;
        }
    }

    // Método para añadir un callback para el loop principal
    void SetMainLoopCallback(void (*callback)())
    {
        if (mainLoopCount < MAX_MAIN_LOOP_CALLBACKS)
        {
            MainLoopCallbacks[mainLoopCount++] = callback;
        }
    }

    void InitializeSystem();
};
