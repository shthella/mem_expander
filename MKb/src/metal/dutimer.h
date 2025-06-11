/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__DUTIMER_H
#define METAL__DUTIMER_H

/*!
 * @file dutimer.h
 *
 * @brief API for configuring dual timers
 */

#include <metal/interrupt.h>

struct metal_dutimer;

#define METAL_DUTIMER_STOP            0
#define METAL_DUTIMER_RUN             1

struct metal_dutimer_vtable {
    long int (*get_value)(const struct metal_dutimer *const timer,
                            const long int id);
    long int (*get_timeout)(const struct metal_dutimer *const timer,
                            const long int id, const long int background);
    long int (*set_timeout)(const struct metal_dutimer *const timer,
                            const long int id, const long int background,
                            const long int timeout);
    long int (*configure)(const struct metal_dutimer *const timer,
                            const long int id, const long int option);
    int (*run)(const struct metal_dutimer *const timer,
                            const long int id, const long int option);
    struct metal_interrupt *(*get_interrupt)(
        const struct metal_dutimer *const timer);
    int (*get_interrupt_id)(const struct metal_dutimer *const timer);
    int (*clear_interrupt)(const struct metal_dutimer *const timer);
};

/*!
 * @brief Handle for a dutimer Timer
 */
struct metal_dutimer {
    const struct metal_dutimer_vtable *vtable;
};


/*!
 * @brief Get the dutimer timer VALUE reigster.
 *
 * @return the dutimer VALUE register. 
 */
inline long int
metal_dutimer_get_value(const struct metal_dutimer *const timer,
                            const long int id)
{
    return timer->vtable->get_value(timer, id);
}


/*!
 * @brief Get the timeout of the dutimer
 *
 * @return the dutimer timeout value
 */
inline long int
metal_dutimer_get_timeout(const struct metal_dutimer *const timer,
                            const long int id, const long int background)
{
    return timer->vtable->get_timeout(timer, id, background);
}

/*!
 * @brief Set the timeout of the dutimer
 *
 * @return the new dutimer timeout value
 */
inline long int
metal_dutimer_set_timeout(const struct metal_dutimer *const timer,
                            const long int id, const long int background,
                            const long int timeout)
{
    return timer->vtable->set_timeout(timer, id, background, timeout);
}

/*!
 * @brief configure the dutimer
 *
 * @return the new configure value.
 */
inline long int 
metal_dutimer_configure(const struct metal_dutimer *const timer,
                            const long int id, const long int option)
{
    return timer->vtable->configure(timer, id, option);
}

/*!
 * @brief start/stop the dutimer
 *
 * @return 0
 */
inline int metal_dutimer_run(const struct metal_dutimer *const timer,
                            const long int id, const long int option) {
    return timer->vtable->run(timer, id, option);
}

/*!
 * @brief Get the interrupt controller for the dutimer interrupt
 */
inline struct metal_interrupt *
metal_dutimer_get_interrupt(const struct metal_dutimer *const timer) {
    return timer->vtable->get_interrupt(timer);
}

/*!
 * @Brief Get the interrupt id for the dutimer interrupt
 */
inline int
metal_dutimer_get_interrupt_id(const struct metal_dutimer *const timer) {
    return timer->vtable->get_interrupt_id(timer);
}

/*!
 * @brief Clear the dutimer interrupt
 */
inline int
metal_dutimer_clear_interrupt(const struct metal_dutimer *const timer) {
    return timer->vtable->clear_interrupt(timer);
}

/*!
 * @brief Get a dutimer handle
 */
struct metal_dutimer *metal_dutimer_get_device(const int index);

#endif /* METAL__DUTIMER_H */
