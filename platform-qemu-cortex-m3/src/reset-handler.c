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

// ----------------------------------------------------------------------------

typedef void (*handler_ptr_t) (void);

extern handler_ptr_t _interrupt_vectors[];

void
Reset_Handler (void);

extern void __attribute__ ((noreturn, weak)) _start (void);

// ----------------------------------------------------------------------------

// Begin address for the initialisation values of the .data section.
extern uintptr_t __data_load_addr__;
// Begin address for the .data section.
extern uintptr_t __data_begin__;
// End address for the .data section.
extern uintptr_t __data_end__;

extern uint32_t __stack;

// ----------------------------------------------------------------------------

// QEMU sets SP to the first word in flash.
void __attribute__ ((section (".after_vectors"), noreturn, naked))
Reset_Handler (void)
{

  __asm__(" MSR msp, %0 " : : "r"(&__stack) :);
  // cortexm_architecture_set_msp(&__stack);

  // SCB
  // https://developer.arm.com/documentation/dui0552/a/cortex-m3-peripherals/system-control-block

  // SCB->VTOR
  // https://developer.arm.com/documentation/dui0552/a/cortex-m3-peripherals/system-control-block/vector-table-offset-register
  // Mandatory when running from RAM. Not available on Cortex-M0.
#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
  *((uint32_t*)0xE000ED08) = ((uint32_t)_interrupt_vectors & (~0x3F));
#endif

#if defined(__ARM_FP)
  // Enable CP10 and CP11 coprocessor.
  // SCB->CPACR |= (0xF << 20);
  *((uint32_t*)0xE000ED88) |= (uint32_t)(0xF << 20);

  // Lazy save.
  // FPU->FPCCR |= FPU_FPCCR_ASPEN_Msk | FPU_FPCCR_LSPEN_Msk;
  *((uint32_t*)0xE000EF34) |= (uint32_t)(0x3 << 29);
#endif // defined(__ARM_FP)

  // Newlib _start() does not copy initialised data. Do it here.
  if (&__data_load_addr__ != &__data_begin__)
    {

      // Iterate and copy word by word.
      // Assume that the pointers are word aligned.
      uintptr_t* from = &__data_load_addr__;
      uintptr_t* p = &__data_begin__;
      while (p < &__data_end__)
        {
          *p++ = *from++;
        }
    }

  _start ();
}

// ----------------------------------------------------------------------------
