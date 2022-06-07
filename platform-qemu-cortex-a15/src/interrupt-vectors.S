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

#define __ASSEMBLY__ 1

// ----------------------------------------------------------------------------

    .globl _interrupt_vectors
    // "x" makes it visible in the listing.
    .section .interrupt_vectors,"awx",%progbits

    .align  7
_interrupt_vectors:

    .balign 4
    b     Reset_Handler
    b     undefined_handler
    b     swi_handler
    b     prefetch_handler
    b     data_handler
    nop   // Reserved vector
    b     irq_handler
    b     fiq_handler

// ----------------------------------------------------------------------------

    .section .after_vectors,"awx",%progbits

    .balign 4
undefined_handler:
    wfi
    b     undefined_handler

    .balign 4
swi_handler:
    wfi
    b     swi_handler

    .balign 4
prefetch_handler:
    wfi
    b     prefetch_handler

    .balign 4
data_handler:
    wfi
    b     data_handler

    .balign 4
irq_handler:
    SUB   lr, lr, #4
    SRSFD sp!, #0x1f
    CPS   #0x1f
    PUSH  {r0-r3, r12}
    AND   r1, sp, #4
    SUB   sp, sp, r1
    PUSH  {r1, lr}
    BL    identify_and_clear_source
    CPSIE i
    BL    c_irq_handler
    CPSID i
    POP   {r1, lr}
    ADD   sp, sp, r1
    POP   {r0-r3, r12}
    RFEFD sp!

identify_and_clear_source:
    bx    lr

    .balign 4
fiq_handler:
    wfi
    b     fiq_handler

// ----------------------------------------------------------------------------
