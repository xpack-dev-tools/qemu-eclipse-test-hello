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

# -----------------------------------------------------------------------------

// AArch64 GCC does not support naked functions, so everything should be
// written in assembly.

// In `architecture-cortexa/linker-scripts/sections-flash.ld` there is an
// `ENTRY(Reset_Handler)` to tell QEMU where to start.

    .section .after_vectors,"awx",%progbits

    .align 2
    .globl Reset_Handler
    .type Reset_Handler, %function
Reset_Handler:

    // Only CPU 0 performs initialization. Other CPUs go into WFI
    // to do this, first work out which CPU this is
    // this code typically is run before any other initialization step.
    mrs   x0, mpidr_el1 // Read Multiprocessor Affinity Register
    and   x0, x0, #3 // Extract CPU ID bits
    cmp   x0, #0
    beq   .Lcpu0_initialize // If we’re on CPU0 go to the start.

.Lcpu_sleep:
    wfi    // Other CPUs are left sleeping.
    b     .Lcpu_sleep

.Lcpu0_initialize:
    // Set vector base.
    ldr   x0, = _interrupt_vectors
    msr   vbar_el1, x0

    // Enable Advanced SIMD and floating-point.
    mrs   x0, cpacr_el1 // Architectural Feature Access Control Register.
    orr   x0, x0, #(3 << 20) // FPEN=0b11 do not trap in EL0 and EL1.
    msr   cpacr_el1, x0

    // Disable MMU to ensure phys mem addresses are used.
    mrs    x0, sctlr_el1
    bic    x0, x0, #(1<<0)
    msr    sctlr_el1, x0
    isb

    // Configure stack.
    // Address of 4KB page at a PC-relative offset.
    adrp   x0,__stack
    mov    sp, x0

    bl     _start

