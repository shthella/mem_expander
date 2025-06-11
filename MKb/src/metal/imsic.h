/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__IMSIC_H
#define METAL__IMSIC_H

/*!
 * @file imsic.h
 *
 * @brief API for configuring IMSIC
 */

#include <metal/interrupt.h>

struct metal_imsic;

struct metal_imsic_vtable {
    int (*set_int_priority)(const struct metal_imsic *const imsic, long int pri);
    int (*get_int_priority)(const struct metal_imsic *const imsic);
    int (*set_int_pending)(const struct metal_imsic *const imsic, long int index, int enable);
    int (*get_int_pending)(const struct metal_imsic *const imsic, long int index);
    int (*set_int_enable)(const struct metal_imsic *const imsic, long int index, int enable);
    int (*get_int_enable)(const struct metal_imsic *const imsic, long int index);
    int (*get_int_topei)(const struct metal_imsic *const imsic);
    int (*set_int_mask)(const struct metal_imsic *const imsic, long int mask);
    int (*get_int_mask)(const struct metal_imsic *const imsic);
    struct metal_interrupt *(*get_interrupt)(const struct metal_imsic *const imsic);
    int (*get_interrupt_id)(const struct metal_imsic *const imsic);
    int (*clear_interrupt)(const struct metal_imsic *const imsic);
};

/*!
 * @brief Handle for a IMSIC
 */
struct metal_imsic {
    const struct metal_imsic_vtable *vtable;
};

inline int metal_imsic_set_int_priority(const struct metal_imsic *const imsic,
                            long int pri) {
    return imsic->vtable->set_int_priority(imsic, pri);
}

inline int metal_imsic_get_int_priority(const struct metal_imsic *const imsic) {
    return imsic->vtable->get_int_priority(imsic);
}

inline int metal_imsic_set_int_pending(const struct metal_imsic *const imsic,
                            long int index, int enable) {
    return imsic->vtable->set_int_pending(imsic, index, enable);
}

inline int metal_imsic_get_int_pending(const struct metal_imsic *const imsic,
                            long int index) {
    return imsic->vtable->get_int_pending(imsic, index);
}

inline int metal_imsic_set_int_enable(const struct metal_imsic *const imsic,
                            long int index, int enable) {
    return imsic->vtable->set_int_enable(imsic, index, enable);
}

inline int metal_imsic_get_int_enable(const struct metal_imsic *const imsic,
                            long int index) {
    return imsic->vtable->get_int_enable(imsic, index);
}

inline int metal_imsic_get_int_topei(const struct metal_imsic *const imsic) {
    return imsic->vtable->get_int_topei(imsic);
}

/*!
 * @brief setup interrupt mask for imsic
 *
 * @return mask value.
 */
inline int metal_imsic_set_int_mask(const struct metal_imsic *const imsic,
                            long int mask) {
    return imsic->vtable->set_int_mask(imsic, mask);
}

/*!
 * @brief getinterrupt mask for imsic
 *
 * @return mask value.
 */
inline int metal_imsic_get_int_mask(const struct metal_imsic *const imsic) {
    return imsic->vtable->get_int_mask(imsic);
}

/*!
 * @brief Get the interrupt controller for the imsic interrupt
 */
inline struct metal_interrupt *
metal_imsic_get_interrupt(const struct metal_imsic *const imsic) {
    return imsic->vtable->get_interrupt(imsic);
}

/*!
 * @Brief Get the interrupt id for the imsic interrupt
 */
inline int
metal_imsic_get_interrupt_id(const struct metal_imsic *const imsic) {
    return imsic->vtable->get_interrupt_id(imsic);
}

/*!
 * @brief Clear the imsic interrupt
 */
inline int
metal_imsic_clear_interrupt(const struct metal_imsic *const imsic) {
    return imsic->vtable->clear_interrupt(imsic);
}

/*!
 * @brief Get a imsic handle
 */
struct metal_imsic *metal_imsic_get_device(const int index);

#endif /* METAL__IMSIC_H */
