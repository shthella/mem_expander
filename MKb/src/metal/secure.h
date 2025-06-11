/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__SECURE_H
#define METAL__SECURE_H

/*!
 * @file secure.h
 *
 * @brief API for configuring SECURE module
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <metal/interrupt.h>

struct metal_secure;

typedef struct
{
    uint32_t total[2];    /*!< Number of bytes processed */
    uint32_t *shaBuf;     /*!< Data not processed but in this temp buffer */
    uint32_t *shaPadding; /*!< Padding data */
    uint8_t shaFeed;      /*!< Sha has feed data */
} SEC_Eng_SHA256_Ctx;

typedef struct
{
    uint32_t total[2];    /*!< Number of bytes processed */
    uint32_t *shaBuf;     /*!< Data not processed but in this temp buffer */
    uint32_t *shaPadding; /*!< Padding data */
    uint32_t linkAddr;    /*!< Link configure address */
} SEC_Eng_SHA256_Link_Ctx;

typedef enum {
    SEC_ENG_SHA_ID0, /*!< SHA0 port define */
} SEC_ENG_SHA_ID_Type;

typedef enum {
    SEC_ENG_SHA256,    /*!< SHA type:SHA256 */
    SEC_ENG_SHA224,    /*!< SHA type:SHA224 */
    SEC_ENG_SHA1,      /*!< SHA type:SHA1 */
    SEC_ENG_SHA1_RSVD, /*!< SHA type:SHA1 */
} SEC_ENG_SHA_Type;

typedef enum {
    SEC_ENG_AES_ECB, /*!< AES mode type:ECB */
    SEC_ENG_AES_CTR, /*!< AES mode type:CTR */
    SEC_ENG_AES_CBC, /*!< AES mode type:CBC */
} SEC_ENG_AES_Type;

typedef enum {
    SEC_ENG_AES_KEY_128BITS,        /*!< AES KEY type:128 bits */
    SEC_ENG_AES_KEY_256BITS,        /*!< AES KEY type:256 bits */
    SEC_ENG_AES_KEY_192BITS,        /*!< AES KEY type:192 bits */
    SEC_ENG_AES_DOUBLE_KEY_128BITS, /*!< AES double KEY type:128 bits */
} SEC_ENG_AES_Key_Type;

typedef enum {
    SEC_ENG_AES_ENCRYPTION, /*!< AES encryption */
    SEC_ENG_AES_DECRYPTION, /*!< AES decryption */
} SEC_ENG_AES_EnDec_Type;

typedef enum {
    SEC_ENG_AES_KEY_SW, /*!< AES KEY from software */
    SEC_ENG_AES_KEY_HW, /*!< AES KEY from hardware */
} SEC_ENG_AES_Key_Src_Type;

typedef enum {
    SEC_ENG_AES_COUNTER_BYTE_4, /*!< AES CTR mode counter type:4 bytes */
    SEC_ENG_AES_COUNTER_BYTE_1, /*!< AES CTR mode counter type:1 byte */
    SEC_ENG_AES_COUNTER_BYTE_2, /*!< AES CTR mode counter type:2 bytes */
    SEC_ENG_AES_COUNTER_BYTE_3, /*!< AES CTR mode counter type:3 bytes */
} SEC_ENG_AES_Counter_Type;

typedef struct
{
    uint8_t aesFeed;       /*!< AES has feed data */
    SEC_ENG_AES_Type mode; /*!< AES mode */
} SEC_Eng_AES_Ctx;

typedef enum {
    SEC_ENG_AES_ID0, /*!< AES0 port define */
} SEC_ENG_AES_ID_Type;

struct metal_secure_vtable {
    int (*sha_open)(const struct metal_secure *const secure,
                SEC_ENG_SHA_Type hashType);
    int (*sha_close)(const struct metal_secure *const secure);
    int (*sha_write)(const struct metal_secure *const secure, uint32_t pos,
                const void *buffer, uint32_t size);
    int (*sha_read)(const struct metal_secure *const secure, uint32_t pos,
                void *buffer, uint32_t size);
    int (*aes_dev_init)(const struct metal_secure *const secure,
                SEC_ENG_AES_Type aesType, SEC_ENG_AES_Key_Type keyType);
    int (*aes_set_key)(const struct metal_secure *const secure,
                const uint8_t *key, uint8_t keyLen, const uint8_t *nonce,
                uint8_t dir);
    int (*aes_encrypt)(const struct metal_secure *const secure,
                const uint8_t *in, uint32_t len, size_t offset, uint8_t *out);
    int (*aes_decrypt)(const struct metal_secure *const secure,
                const uint8_t *in, uint32_t len, size_t offset, uint8_t *out);
    int (*aes_dev_deinit)(const struct metal_secure *const secure);

    int (*set_int_mask)(const struct metal_secure *const secure, long int mask);
    int (*get_int_mask)(const struct metal_secure *const secure);
    struct metal_interrupt *(*get_interrupt)(const struct metal_secure *const secure);
    int (*get_interrupt_id)(const struct metal_secure *const secure);
    int (*clear_interrupt)(const struct metal_secure *const secure);
};

/*!
 * @brief Handle for a secure module
 */
struct metal_secure {
    const struct metal_secure_vtable *vtable;
};

inline int metal_secure_sha_open(const struct metal_secure *const secure,
                SEC_ENG_SHA_Type hashType) {
    return secure->vtable->sha_open(secure, hashType);
}

inline int metal_secure_sha_close(const struct metal_secure *const secure) {
    return secure->vtable->sha_close(secure);
}

inline int metal_secure_sha_write(const struct metal_secure *const secure,
                uint32_t pos, const void *buffer, uint32_t size) {
    return secure->vtable->sha_write(secure, pos, buffer, size);
}

inline int metal_secure_sha_read(const struct metal_secure *const secure,
                uint32_t pos, void *buffer, uint32_t size) {
    return secure->vtable->sha_read(secure, pos, buffer, size);
}

inline int metal_secure_aes_dev_init(const struct metal_secure *const secure,
                SEC_ENG_AES_Type aesType, SEC_ENG_AES_Key_Type keyType) {
    return secure->vtable->aes_dev_init(secure, aesType, keyType);
}

inline int metal_secure_aes_set_key(const struct metal_secure *const secure,
                const uint8_t *key, uint8_t keyLen, const uint8_t *nonce,
                uint8_t dir) {
    return secure->vtable->aes_set_key(secure, key, keyLen, nonce, dir);
}

inline int metal_secure_aes_encrypt(const struct metal_secure *const secure,
                const uint8_t *in, uint32_t len, size_t offset, uint8_t *out) {
    return secure->vtable->aes_encrypt(secure, in, len, offset, out);
}

inline int metal_secure_aes_decrypt(const struct metal_secure *const secure,
                const uint8_t *in, uint32_t len, size_t offset, uint8_t *out) {
    return secure->vtable->aes_decrypt(secure, in, len, offset, out);
}

inline int metal_secure_aes_dev_deinit(const struct metal_secure *const secure) {
    return secure->vtable->aes_dev_deinit(secure);
}

/*!
 * @brief setup interrupt mask for secure
 *
 * @return mask value.
 */
inline int metal_secure_set_int_mask(const struct metal_secure *const secure,
                            long int mask) {
    return secure->vtable->set_int_mask(secure, mask);
}

/*!
 * @brief getinterrupt mask for secure
 *
 * @return mask value.
 */
inline int metal_secure_get_int_mask(const struct metal_secure *const secure) {
    return secure->vtable->get_int_mask(secure);
}

/*!
 * @brief Get the interrupt controller for the secure interrupt
 */
inline struct metal_interrupt *
metal_secure_get_interrupt(const struct metal_secure *const secure) {
    return secure->vtable->get_interrupt(secure);
}

/*!
 * @Brief Get the interrupt id for the secure interrupt
 */
inline int
metal_secure_get_interrupt_id(const struct metal_secure *const secure) {
    return secure->vtable->get_interrupt_id(secure);
}

/*!
 * @brief Clear the secure interrupt
 */
inline int
metal_secure_clear_interrupt(const struct metal_secure *const secure) {
    return secure->vtable->clear_interrupt(secure);
}

/*!
 * @brief Get a secure handle
 */
struct metal_secure *metal_secure_get_device(const int index);

#endif /* METAL__SECURE_H */
