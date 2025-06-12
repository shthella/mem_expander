#ifndef FLASH_MEM_LAYOUT_H
#define FLASH_MEM_LAYOUT_H

#define FLASH_MAX_ADDR (256*1024*1024)

#define LC_MKB_FSBL             0x01
#define LC_QSPI_TEST_DATA       0x02
#define LC_MKB_FW               0x03
#define LC_GFH_FSBL             0x04
#define LC_GFH_D2D              0x05
#define LC_GFH_FW               0x06
#define LC_GFH_DDR_IMEM_CFG1    0x06
#define LC_GFH_DDR_DMEM_CFG1    0x07

typedef struct {
    uint32_t flashDataStart;
    uint32_t numOfNodes;
    uint8_t flashMemVer[32];
    uint32_t rsvd;
}FlashBlockInfo;

typedef struct {
    uint32_t sAddr;      // Starting address where it will be stored in flash (4 bytes)
    uint32_t len;        // Length of the file (4 bytes)
    uint32_t labelCode;  // Integer code to identify the memory block (4 bytes)
    uint32_t isLastNode; // Flag to indicate if it's the last node (4 bytes)
} FlashData;

typedef struct {
    FlashData flash_data;
    uint8_t flashFirmware[32];
} FlashDataInfo;

#endif /* FLASH_MEM_LAYOUT_H */
