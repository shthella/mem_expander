/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__DRIVERS__QEMU_IMSIC0_H
#define METAL__DRIVERS__QEMU_IMSIC0_H

#include <metal/compiler.h>
#include <metal/io.h>

#include <metal/clock.h>
#include <metal/interrupt.h>
#include <metal/imsic.h>

struct __metal_driver_vtable_qemu_imsic0 {
    const struct metal_imsic_vtable imsic;
};

struct __metal_driver_qemu_imsic0;

__METAL_DECLARE_VTABLE(__metal_driver_vtable_qemu_imsic0)

struct __metal_driver_qemu_imsic0 {
    const struct metal_imsic imsic;
};

#endif
