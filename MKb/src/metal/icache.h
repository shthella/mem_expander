/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__ICACHE_H
#define METAL__ICACHE_H

/*!
 * @file icache.h
 *
 * @brief API for configuring ICACHE module
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <metal/interrupt.h>

struct metal_icache;

struct metal_icache_vtable {

    int (*set_int_mask)(const struct metal_icache *const icache, long int mask);
    int (*get_int_mask)(const struct metal_icache *const icache);
    struct metal_interrupt *(*get_interrupt)(const struct metal_icache *const icache);
    int (*get_interrupt_id)(const struct metal_icache *const icache);
    int (*clear_interrupt)(const struct metal_icache *const icache);
};

/*!
 * @brief Handle for a icache module
 */
struct metal_icache {
    const struct metal_icache_vtable *vtable;
};


/*!
 * @brief setup interrupt mask for icache
 *
 * @return mask value.
 */
inline int metal_icache_set_int_mask(const struct metal_icache *const icache,
                            long int mask) {
    return icache->vtable->set_int_mask(icache, mask);
}

/*!
 * @brief getinterrupt mask for icache
 *
 * @return mask value.
 */
inline int metal_icache_get_int_mask(const struct metal_icache *const icache) {
    return icache->vtable->get_int_mask(icache);
}

/*!
 * @brief Get the interrupt controller for the icache interrupt
 */
inline struct metal_interrupt *
metal_icache_get_interrupt(const struct metal_icache *const icache) {
    return icache->vtable->get_interrupt(icache);
}

/*!
 * @Brief Get the interrupt id for the icache interrupt
 */
inline int
metal_icache_get_interrupt_id(const struct metal_icache *const icache) {
    return icache->vtable->get_interrupt_id(icache);
}

/*!
 * @brief Clear the icache interrupt
 */
inline int
metal_icache_clear_interrupt(const struct metal_icache *const icache) {
    return icache->vtable->clear_interrupt(icache);
}

/*!
 * @brief Get a icache handle
 */
struct metal_icache *metal_icache_get_device(const int index);

#endif /* METAL__ICACHE_H */
