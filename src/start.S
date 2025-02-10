// --- Sección de arranque: .text.boot ---
.section ".text.boot"
.global _start

_start:
    // Leer el ID de CPU y detener núcleos esclavos
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, 2f
1:  wfe
    b       1b
2:  // Estamos en CPU 0

    // Configurar la pila
    ldr     x1, =_start
    mov     sp, x1

    // *** Configuración de la tabla de vectores de interrupciones ***
    // Se carga la dirección de la tabla y se escribe en VBAR_EL1.
    ldr     x0, =vectors
    msr     vbar_el1, x0
    isb

    // Limpieza de la sección BSS
    ldr     x1, =__bss_start
    ldr     w2, =__bss_size
3:  cbz     w2, 4f
    str     xzr, [x1], #8
    sub     w2, w2, #1
    cbnz    w2, 3b

    // Salto a la función main (en C)
4:  bl      main
    // Si main retorna, se cuelga el núcleo
    b       1b

// --- Tabla de vectores de interrupciones: .vectors ---
// Esta tabla está alineada a 128 bytes (2^7) como requiere AArch64.
.section ".vectors", "ax"
.align 11
.global vectors
vectors:
    // Vectores para excepciones en EL1 (usando SP0)
    b   vector_sync_handler       // 0x000: Excepción síncrona
    .space 124
    b   vector_irq_handler        // 0x080: IRQ
    .space 124
    b   vector_fiq_handler        // 0x100: FIQ
    .space 124
    b   vector_serr_handler       // 0x180: SError
    .space 124

    // Vectores para excepciones en EL1 (usando SPx)
    b   vector_sync_handler       // 0x200: Excepción síncrona
    .space 124
    b   vector_irq_handler        // 0x280: IRQ
    .space 124
    b   vector_fiq_handler        // 0x300: FIQ
    .space 124
    b   vector_serr_handler       // 0x380: SError
    .space 124

    // Vectores para excepciones tomadas desde un nivel inferior (AArch64)
    b   vector_sync_handler       // 0x400: Excepción síncrona
    .space 124
    b   vector_irq_handler        // 0x480: IRQ
    .space 124
    b   vector_fiq_handler        // 0x500: FIQ
    .space 124
    b   vector_serr_handler       // 0x580: SError

// --- Manejadores de interrupción (por defecto, bucle infinito) ---
.global vector_sync_handler
vector_sync_handler:
    // Aquí se podría guardar el contexto y derivar a un manejador común
    nop
    eret

.global vector_irq_handler
vector_irq_handler:
    // Manejador de IRQ: implementar el código necesario
    b   c_irq_handler
    eret

.global vector_fiq_handler
vector_fiq_handler:
    // Manejador de FIQ: implementar el código necesario
    nop
    eret
.global vector_serr_handler
vector_serr_handler:
    // Manejador de SError: implementar el código necesario
    nop
    eret
