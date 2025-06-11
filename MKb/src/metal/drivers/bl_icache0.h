/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__DRIVERS__BL_ICACHE0_H
#define METAL__DRIVERS__BL_ICACHE0_H

#include <stdlib.h>
#include <string.h>

#include <metal/compiler.h>
#include <metal/io.h>

#include <metal/clock.h>
#include <metal/interrupt.h>
#include <metal/icache.h>

struct __metal_driver_vtable_bl_icache0 {
    const struct metal_icache_vtable icache;
};

struct __metal_driver_bl_icache0;

__METAL_DECLARE_VTABLE(__metal_driver_vtable_bl_icache0)

struct __metal_driver_bl_icache0 {
    const struct metal_icache icache;
};

#endif
