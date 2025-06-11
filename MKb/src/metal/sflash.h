/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__SFLASH_H
#define METAL__SFLASH_H

/*!
 * @file sflash.h
 *
 * @brief API for configuring SFLASH module
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <metal/interrupt.h>

struct metal_sflash;

typedef struct
{
    uint8_t ioMode;               /*!< Serail flash interface mode,bit0-3:IF mode,bit4:unwrap */
    uint8_t resetEnCmd;           /*!< Flash enable reset command */
    uint8_t resetCmd;             /*!< Flash reset command */
    uint8_t jedecIdCmd;           /*!< JEDEC ID command */
    uint8_t jedecIdCmdDmyClk;     /*!< JEDEC ID command dummy clock */
    uint8_t qpiJedecIdCmd;        /*!< QPI JEDEC ID comamnd */
    uint8_t qpiJedecIdCmdDmyClk;  /*!< QPI JEDEC ID command dummy clock */
    uint16_t sectorSize;           /*!< *1024bytes */
    uint16_t pageSize;            /*!< Page size */
    uint8_t sectorEraseCmd;       /*!< Sector erase command */
    uint8_t blk64EraseCmd;        /*!< Block 64K erase command */
    uint8_t writeEnableCmd;       /*!< Need before every erase or program */
    uint8_t pageProgramCmd;       /*!< Page program cmd */
    uint8_t qpageProgramCmd;      /*!< QIO page program cmd */
    uint8_t fastReadCmd;          /*!< Fast read command */
    uint8_t frDmyClk;             /*!< Fast read command dummy clock */
    uint8_t qpiFastReadCmd;       /*!< QPI fast read command */
    uint8_t qpiFrDmyClk;          /*!< QPI fast read command dummy clock */
    uint8_t fastReadDoCmd;        /*!< Fast read dual output command */
    uint8_t frDoDmyClk;           /*!< Fast read dual output command dummy clock */
    uint8_t fastReadDioCmd;       /*!< Fast read dual io comamnd */
    uint8_t frDioDmyClk;          /*!< Fast read dual io command dummy clock */
    uint8_t fastReadQoCmd;        /*!< Fast read quad output comamnd */
    uint8_t frQoDmyClk;           /*!< Fast read quad output comamnd dummy clock */
    uint8_t fastReadQioCmd;       /*!< Fast read quad io comamnd */
    uint8_t frQioDmyClk;          /*!< Fast read quad io comamnd dummy clock */
    uint8_t qpiFastReadQioCmd;    /*!< QPI fast read quad io comamnd */
    uint8_t qpiFrQioDmyClk;       /*!< QPI fast read QIO dummy clock */
    uint8_t qpiPageProgramCmd;    /*!< QPI program command */
    uint8_t wrEnableIndex;        /*!< Write enable register index */
    uint8_t qeIndex;              /*!< Quad mode enable register index */
    uint8_t busyIndex;            /*!< Busy status register index */
    uint8_t wrEnableBit;          /*!< Write enable bit pos */
    uint8_t qeBit;                /*!< Quad enable bit pos */
    uint8_t busyBit;              /*!< Busy status bit pos */
    uint8_t wrEnableReadRegLen;   /*!< Register length of write enable status */
    uint8_t qeWriteRegLen;        /*!< Register length of contain quad enable */
    uint8_t busyReadRegLen;       /*!< Register length of contain busy status */
    uint8_t readRegCmd[4];        /*!< Read register command buffer */
    uint8_t writeRegCmd[4];       /*!< Write register command buffer */
    uint16_t timeEsector;         /*!< 4K erase time */
    uint16_t timeE64k;            /*!< 64K erase time */
    uint16_t timePagePgm;         /*!< Page program time */

    uint8_t evcrIndex;          /* index of ENHANCED VOLATILE CONFIGURATION REGISTER*/
    uint8_t vcrIndex;            /* index of VOLATILE CONFIGURATION REGISTER*/
    uint8_t evcrWriteRegLen;
    uint8_t evcrReadRegLen;
    uint8_t vcrWriteRegLen;
    uint8_t vcrReadRegLen;

    /* For S25FL512S */
    uint8_t sr1Index;
    uint8_t crIndex;
    uint8_t sr1WriteRegLen;
    uint8_t sr1ReadRegLen;
    uint8_t crWriteRegLen;
    uint8_t crReadRegLen;
    uint8_t lcVal;                   /* Value of CR.LC */
    uint8_t bankIndex;
    uint8_t bankWriteRegLen;
    uint8_t bankReadRegLen;
} __attribute__((packed)) SPI_Flash_Cfg_Type;

#define BFLB_SPIFLASH_BLK32K_SIZE (32 * 1024)
#define BFLB_SPIFLASH_BLK64K_SIZE (64 * 1024)
#define BFLB_SPIFLASH_CMD_INVALID 0xff

struct metal_sflash_vtable {
    int (*config_init)(const struct metal_sflash *const sflash,
                        SPI_Flash_Cfg_Type *p_flash_cfg, uint8_t *jedec_id);
    int (*init)(const struct metal_sflash *const sflash);
    int (*read_jedec_id)(const struct metal_sflash *const sflash, uint8_t *data);
    int (*read_via_xip)(const struct metal_sflash *const sflash,
                        uint32_t addr, uint8_t *data, uint32_t len);
    int (*read)(const struct metal_sflash *const sflash,
                        uint32_t addr, uint8_t *data, uint32_t len);
    int (*write)(const struct metal_sflash *const sflash,
                        uint32_t addr, uint8_t *data, uint32_t len);
    int (*erase)(const struct metal_sflash *const sflash,
                        uint32_t addr, uint32_t len);
    int (*set_cache)(const struct metal_sflash *const sflash,
                        uint8_t contRead, uint8_t cacheEnable, 
                        uint8_t cacheWayDisable, uint32_t flashOffset);

    int (*set_int_mask)(const struct metal_sflash *const sflash, long int mask);
    int (*get_int_mask)(const struct metal_sflash *const sflash);
    struct metal_interrupt *(*get_interrupt)(const struct metal_sflash *const sflash);
    int (*get_interrupt_id)(const struct metal_sflash *const sflash);
    int (*clear_interrupt)(const struct metal_sflash *const sflash);
};

/*!
 * @brief Handle for a sflash module
 */
struct metal_sflash {
    const struct metal_sflash_vtable *vtable;
};

inline int metal_sflash_config_init(const struct metal_sflash *const sflash,
                        SPI_Flash_Cfg_Type *pFlashCfg, uint8_t *jedecId) {
    return sflash->vtable->config_init(sflash, pFlashCfg, jedecId);
}

inline int metal_sflash_init(const struct metal_sflash *const sflash) {
    return sflash->vtable->init(sflash);
}

inline int metal_sflash_read_jedec_id(const struct metal_sflash *const sflash,
                        uint8_t *data) {
    return sflash->vtable->read_jedec_id(sflash, data);
}

inline int metal_sflash_read_via_xip(const struct metal_sflash *const sflash, 
                        uint32_t addr, uint8_t *data, uint32_t len) {
    return sflash->vtable->read_via_xip(sflash, addr, data, len);
}

inline int metal_sflash_read(const struct metal_sflash *const sflash, 
                        uint32_t addr, uint8_t *data, uint32_t len) {
    return sflash->vtable->read(sflash, addr, data, len);
}

inline int metal_sflash_write(const struct metal_sflash *const sflash, 
                        uint32_t addr, uint8_t *data, uint32_t len) {
    return sflash->vtable->write(sflash, addr, data, len);
}

inline int metal_sflash_erase(const struct metal_sflash *const sflash, 
                        uint32_t addr, uint32_t len) {
    return sflash->vtable->erase(sflash, addr, len);
}

inline int metal_sflash_set_cache(const struct metal_sflash *const sflash, 
                        uint8_t contRead, uint8_t cacheEnable,
                        uint8_t cacheWayDisable, uint32_t flashOffset) {
    return sflash->vtable->set_cache(sflash, contRead, cacheEnable,
                        cacheWayDisable, flashOffset);
}

/*!
 * @brief setup interrupt mask for sflash
 *
 * @return mask value.
 */
inline int metal_sflash_set_int_mask(const struct metal_sflash *const sflash,
                            long int mask) {
    return sflash->vtable->set_int_mask(sflash, mask);
}

/*!
 * @brief getinterrupt mask for sflash
 *
 * @return mask value.
 */
inline int metal_sflash_get_int_mask(const struct metal_sflash *const sflash) {
    return sflash->vtable->get_int_mask(sflash);
}

/*!
 * @brief Get the interrupt controller for the sflash interrupt
 */
inline struct metal_interrupt *
metal_sflash_get_interrupt(const struct metal_sflash *const sflash) {
    return sflash->vtable->get_interrupt(sflash);
}

/*!
 * @Brief Get the interrupt id for the sflash interrupt
 */
inline int
metal_sflash_get_interrupt_id(const struct metal_sflash *const sflash) {
    return sflash->vtable->get_interrupt_id(sflash);
}

/*!
 * @brief Clear the sflash interrupt
 */
inline int
metal_sflash_clear_interrupt(const struct metal_sflash *const sflash) {
    return sflash->vtable->clear_interrupt(sflash);
}

/*!
 * @brief Get a sflash handle
 */
struct metal_sflash *metal_sflash_get_device(const int index);

#endif /* METAL__SFLASH_H */
