/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__TRNG_H
#define METAL__TRNG_H

/*!
 * @file trng.h
 *
 * @brief API for configuring TRNG
 */

#include <metal/interrupt.h>

struct metal_trng;

#define TRNG_VALID      0x1
#define TRNG_BUSY       0x2

struct metal_trng_vtable {
    int (*get_value)(const struct metal_trng *const trng, int *pval);
    int (*get_bist_cntr)(const struct metal_trng *const trng, int *pcnt);
    int (*configure)(const struct metal_trng *const trng, const long int option);
    int (*enable)(const struct metal_trng *const trng, const long int option);
    int (*sw_reset)(const struct metal_trng *const trng);
    int (*rst_bits_counter)(const struct metal_trng *const trng);
    int (*get_valid)(const struct metal_trng *const trng);
    int (*get_sample_cnt)(const struct metal_trng *const trng);
    int (*set_sample_cnt)(const struct metal_trng *const trng, const long int count);
    int (*get_autocorr_stat)(const struct metal_trng *const trng);
    int (*get_version)(const struct metal_trng *const trng);
    int (*set_int_mask)(const struct metal_trng *const trng, long int mask);
    int (*get_int_mask)(const struct metal_trng *const trng);
    struct metal_interrupt *(*get_interrupt)(const struct metal_trng *const trng);
    int (*get_interrupt_id)(const struct metal_trng *const trng);
    int (*clear_interrupt)(const struct metal_trng *const trng);
};

/*!
 * @brief Handle for a TRNG
 */
struct metal_trng {
    const struct metal_trng_vtable *vtable;
};


/*!
 * @brief Get the trng EHR_DATA reigsters.
 *
 * @return the trng EHR_DATA registers. 
 */
inline int
metal_trng_get_value(const struct metal_trng *const trng, int *pval)
{
    return trng->vtable->get_value(trng, pval);
}

/*!
 * @brief Get the trng BIST_CNTR reigsters.
 *
 * @return the trng BIST_CNTR registers. 
 */
inline int
metal_trng_get_bist_cntr(const struct metal_trng *const trng, int *pcnt)
{
    return trng->vtable->get_bist_cntr(trng, pcnt);
}

/*!
 * @brief configure the trng TRNG_CONFIG
 *
 * @return the new configure value.
 */
inline int 
metal_trng_configure(const struct metal_trng *const trng,
                            const long int option)
{
    return trng->vtable->configure(trng, option);
}

/*!
 * @brief configure the trng RND_SOURCE_ENABLE
 *
 * @return the new configure value.
 */
inline int 
metal_trng_enable(const struct metal_trng *const trng,
                            const long int option)
{
    return trng->vtable->enable(trng, option);
}

/*!
 * @brief reset trng by software.
 *
 * @return 0.
 */
inline int 
metal_trng_sw_reset(const struct metal_trng *const trng)
{
    return trng->vtable->sw_reset(trng);
}

/*!
 * @brief reset trng bits counter.
 *
 * @return 0.
 */
inline int 
metal_trng_rst_bits_counter(const struct metal_trng *const trng)
{
    return trng->vtable->rst_bits_counter(trng);
}


/*!
 * @brief get the trng valid and busy status
 *
 * @return the valid and busy status.
 */
inline int 
metal_trng_get_valid(const struct metal_trng *const trng)
{
    return trng->vtable->get_valid(trng);
}

/*!
 * @brief get the trng SAMPLE_CNT1 register
 *
 * @return the SAMPLE_CNT1 value.
 */
inline int 
metal_trng_get_sample_cnt(const struct metal_trng *const trng)
{
    return trng->vtable->get_sample_cnt(trng);
}

inline int 
metal_trng_set_sample_cnt(const struct metal_trng *const trng, const long int count)
{
    return trng->vtable->set_sample_cnt(trng, count);
}

/*!
 * @brief get the trng AUTOCORR_STATISTIC register
 *
 * @return the AUTOCORR_STATISTIC value.
 */
inline int 
metal_trng_get_autocorr_stat(const struct metal_trng *const trng)
{
    return trng->vtable->get_autocorr_stat(trng);
}

/*!
 * @brief get the trng version register
 *
 * @return the version value.
 */
inline int 
metal_trng_get_version(const struct metal_trng *const trng)
{
    return trng->vtable->get_version(trng);
}

/*!
 * @brief setup interrupt mask for trng
 *
 * @return mask value.
 */
inline int metal_trng_set_int_mask(const struct metal_trng *const trng,
                            long int mask) {
    return trng->vtable->set_int_mask(trng, mask);
}

/*!
 * @brief getinterrupt mask for trng
 *
 * @return mask value.
 */
inline int metal_trng_get_int_mask(const struct metal_trng *const trng) {
    return trng->vtable->get_int_mask(trng);
}

/*!
 * @brief Get the interrupt controller for the trng interrupt
 */
inline struct metal_interrupt *
metal_trng_get_interrupt(const struct metal_trng *const trng) {
    return trng->vtable->get_interrupt(trng);
}

/*!
 * @Brief Get the interrupt id for the trng interrupt
 */
inline int
metal_trng_get_interrupt_id(const struct metal_trng *const trng) {
    return trng->vtable->get_interrupt_id(trng);
}

/*!
 * @brief Clear the trng interrupt
 */
inline int
metal_trng_clear_interrupt(const struct metal_trng *const trng) {
    return trng->vtable->clear_interrupt(trng);
}

/*!
 * @brief Get a trng handle
 */
struct metal_trng *metal_trng_get_device(const int index);

#endif /* METAL__TRNG_H */
