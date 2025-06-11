/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__DRIVERS__SIFIVE_TRNG0_H
#define METAL__DRIVERS__SIFIVE_TRNG0_H

#include <metal/compiler.h>
#include <metal/io.h>

#include <metal/clock.h>
#include <metal/interrupt.h>
#include <metal/trng.h>

struct __metal_driver_vtable_sifive_trng0 {
    const struct metal_trng_vtable trng;
};

struct __metal_driver_sifive_trng0;

__METAL_DECLARE_VTABLE(__metal_driver_vtable_sifive_trng0)

struct __metal_driver_sifive_trng0 {
    const struct metal_trng trng;
};

#endif
