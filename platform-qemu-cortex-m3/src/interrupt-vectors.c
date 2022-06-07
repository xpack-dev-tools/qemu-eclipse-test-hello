/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus/)
 * Copyright (c) 2022 Liviu Ionescu.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
 */

#include <stdint.h>
#include <sys/types.h>
#include <string.h>

typedef void (*handler_ptr_t) (void);

handler_ptr_t _interrupt_vectors[];

void
Reset_Handler (void);
void
NMI_Handler (void);
void
HardFault_Handler (void);

void
MemManage_Handler (void);
void
BusFault_Handler (void);
void
UsageFault_Handler (void);
void
DebugMon_Handler (void);

void
SVC_Handler (void);

void
PendSV_Handler (void);
void
SysTick_Handler (void);

// ----------------------------------------------------------------------------

void __attribute__ ((section (".after_vectors"), weak)) NMI_Handler (void)
{
  __asm__(" bkpt #0 \n");
  while (1)
    {
      __asm__(" wfi \n");
    }
}

void __attribute__ ((section (".after_vectors"), weak))
HardFault_Handler (void)
{
  __asm__(" bkpt #0 \n");
  while (1)
    {
      __asm__(" wfi \n");
    }
}

void __attribute__ ((section (".after_vectors"), weak))
MemManage_Handler (void)
{
  __asm__(" bkpt #0 \n");
  while (1)
    {
      __asm__(" wfi \n");
    }
}

void __attribute__ ((section (".after_vectors"), weak)) BusFault_Handler (void)
{
  __asm__(" bkpt #0 \n");
  while (1)
    {
      __asm__(" wfi \n");
    }
}

void __attribute__ ((section (".after_vectors"), weak))
UsageFault_Handler (void)
{
  __asm__(" bkpt #0 \n");
  while (1)
    {
      __asm__(" wfi \n");
    }
}

void __attribute__ ((section (".after_vectors"), weak)) DebugMon_Handler (void)
{
  __asm__(" bkpt #0 \n");
  while (1)
    {
      __asm__(" wfi \n");
    }
}

void __attribute__ ((section (".after_vectors"), weak)) SVC_Handler (void)
{
  __asm__(" bkpt #0 \n");
  while (1)
    {
      __asm__(" wfi \n");
    }
}

void __attribute__ ((section (".after_vectors"), weak)) PendSV_Handler (void)
{
  __asm__(" bkpt #0 \n");
  while (1)
    {
      __asm__(" wfi \n");
    }
}

void __attribute__ ((section (".after_vectors"), weak)) SysTick_Handler (void)
{
  __asm__(" bkpt #0 \n");
  while (1)
    {
      __asm__(" wfi \n");
    }
}

extern uint32_t __stack;

// ----------------------------------------------------------------------------

// The table of interrupt handlers. It has an explicit section name
// and relies on the linker script to place it at the correct location
// in memory.

__attribute__ ((section (".interrupt_vectors"), used))
handler_ptr_t _interrupt_vectors[]
    = {
        // Cortex-M Core Handlers
        (handler_ptr_t)&__stack, // The initial stack pointer (MSP)
        Reset_Handler, // The reset handler

        NMI_Handler, // The NMI handler
        HardFault_Handler, // The hard fault handler

        MemManage_Handler, // The MPU fault handler
        BusFault_Handler, // The bus fault handler
        UsageFault_Handler, // The usage fault handler
        0, // Reserved
        0, // Reserved
        0, // Reserved
        0, // Reserved
        SVC_Handler, // SVCall handler
        DebugMon_Handler, // Debug monitor handler
        0, // Reserved
        PendSV_Handler, // The PendSV handler
        SysTick_Handler // The SysTick handler
      };
