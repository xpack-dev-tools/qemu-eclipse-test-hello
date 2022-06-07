/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus/)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
 */

#include <micro-os-plus/architecture-cortexa/exception-handlers.h>

// ----------------------------------------------------------------------------

extern "C"
{
  void common_trap_handler(exception_frame *);
}

void common_trap_handler(exception_frame *)
{
  // TODO
  while(1);
  return;
}

// ----------------------------------------------------------------------------
