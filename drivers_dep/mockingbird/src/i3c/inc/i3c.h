#ifndef I3C_H
#define I3C_H
#include <inttypes.h>
#include "i3c_generic_functions.h"
#include "common/common.h"
#include <stddef.h>
#include <stdio.h>

// HCI Registers
#define I3CM_HCI_BASE_ADDR	      0x2A000000
#define I3CM_HCI_HCI_VERSION          (I3CM_HCI_BASE_ADDR+ 0x0)
#define I3CM_HCI_DEVICE_CTRL_ADDR     (I3CM_HCI_BASE_ADDR+ 0x4)
#define I3CM_HCI_DEVICE_ADDR_ADDR     (I3CM_HCI_BASE_ADDR+ 0x8)
#define I3CM_HCI_HC_CAPABILITIES      (I3CM_HCI_BASE_ADDR+ 0xc)
#define I3CM_HCI_RESET_CONTROL        (I3CM_HCI_BASE_ADDR+ 0x10)
#define I3CM_HCI_PRESENT_STATE        (I3CM_HCI_BASE_ADDR+ 0x14)
#define I3CM_HCI_INTR_STATUS          (I3CM_HCI_BASE_ADDR+ 0x20)
#define I3CM_HCI_INTR_STATUS_ENABLE   (I3CM_HCI_BASE_ADDR+ 0x24)
#define I3CM_HCI_INTR_SIGNAL_ENABLE   (I3CM_HCI_BASE_ADDR+ 0x28)
#define I3CM_HCI_INTR_FORCE           (I3CM_HCI_BASE_ADDR+ 0x2c)
#define I3CM_HCI_DAT_SECTION_OFFSET   (I3CM_HCI_BASE_ADDR+ 0x30)
#define I3CM_HCI_DCT_SECTION_OFFSET   (I3CM_HCI_BASE_ADDR+ 0x34)
#define I3CM_HCI_RING_HEADERS_SECTION_OFFSET   (I3CM_HCI_BASE_ADDR+ 0x38)
#define I3CM_HCI_PIO_SECTION_OFFSET   (I3CM_HCI_BASE_ADDR+ 0x3c)
#define I3CM_HCI_EXTCAPS_SECTION_OFFSET   (I3CM_HCI_BASE_ADDR+ 0x40)
#define I3CM_HCI_IBI_NOTIFY_CTRL      (I3CM-HCI_BASE_ADDR+ 0x58)
#define I3CM_HCI_DEV_CTX_BASE_LO      (I3CM-HCI_BASE_ADDR+ 0x60)
#define I3CM_HCI_DEV_CTX_BASE_HI      (I3CM-HCI_BASE_ADDR+ 0x64)

#define I3CS_HCI_BASE_ADDR	      0x2A010000
#define I3CS_HCI_HCI_VERSION        (I3CS_HCI_BASE_ADDR+ 0x0)
#define I3CS_HCI_DEVICE_CTRL_ADDR   (I3CS_HCI_BASE_ADDR+ 0x4)
#define I3CS_HCI_DEVICE_ADDR_ADDR   (I3CS_HCI_BASE_ADDR+ 0x8)
#define I3CS_HCI_HC_CAPABILITIES    (I3CS_HCI_BASE_ADDR+ 0xc)
#define I3CS_HCI_RESET_CONTROL      (I3CS_HCI_BASE_ADDR+ 0x10)
#define I3CS_HCI_PRESENT_STATE      (I3CS_HCI_BASE_ADDR+ 0x14)
#define I3CS_HCI_INTR_STATUS        (I3CS_HCI_BASE_ADDR+ 0x20)
#define I3CS_HCI_INTR_STATUS_ENABLE (I3CS_HCI_BASE_ADDR+ 0x24)
#define I3CS_HCI_INTR_SIGNAL_ENABLE (I3CS_HCI_BASE_ADDR+ 0x28)
#define I3CS_HCI_INTR_FORCE         (I3CS_HCI_BASE_ADDR+ 0x2c)
#define I3CS_HCI_DAT_SECTION_OFFSET (I3CS_HCI_BASE_ADDR+ 0x30)
#define I3CS_HCI_DCT_SECTION_OFFSET (I3CS_HCI_BASE_ADDR+ 0x34)
#define I3CS_HCI_RING_HEADERS_SECTION_OFFSET   (I3CS_HCI_BASE_ADDR+ 0x38)
#define I3CS_HCI_PIO_SECTION_OFFSET   (I3CS_HCI_BASE_ADDR+ 0x3c)
#define I3CS_HCI_EXTCAPS_SECTION_OFFSET   (I3CS_HCI_BASE_ADDR+ 0x40)
#define I3CS_HCI_IBI_NOTIFY_CTRL    (I3CS_HCI_BASE_ADDR+ 0x58)
#define I3CS_HCI_DEV_CTX_BASE_LO    (I3CS_HCI_BASE_ADDR+ 0x60)
#define I3CS_HCI_DEV_CTX_BASE_HI    (I3CS_HCI_BASE_ADDR+ 0x64)


//Non  HCI registers
#define I3CM_BASE_ADDR	            0x2A000000
#define I3CM_DEVICE_CTRL            (I3CM_BASE_ADDR+ 0x0)
#define I3CM_DEVICE_ADDR_ADDR            (I3CM_BASE_ADDR+ 0x4)
#define I3CM_HW_CAPABILITY          (I3CM_BASE_ADDR+ 0x8)
#define I3CM_COMMAND_QUEUE_PORT     (I3CM_BASE_ADDR+ 0xc)
#define I3CM_RESPONSE_QUEUE_PORT    (I3CM_BASE_ADDR+ 0x10)
#define I3CM_TX_DATA_PORT           (I3CM_BASE_ADDR+ 0x14)
#define I3CM_RX_DATA_PORT           (I3CM_BASE_ADDR+ 0x14)
#define I3CM_IBI_QUEUE_STATUS       (I3CM_BASE_ADDR+ 0x18)
#define I3CM_IBI_QUEUE_DATA         (I3CM_BASE_ADDR+ 0x18)
#define I3CM_QUEUE_THLD_CTRL        (I3CM_BASE_ADDR+ 0x1c)
#define I3CM_DATA_BUFFER_THLD_CTRL  (I3CM_BASE_ADDR+ 0x20)
#define I3CM_IBI_QUEUE_CTRL         (I3CM_BASE_ADDR+ 0x24)
#define I3CM_IBI_MR_REQ_REJECT      (I3CM_BASE_ADDR+ 0x2c)
#define I3CM_IBI_SIR_REQ_REJECT     (I3CM_BASE_ADDR+ 0x30)
#define I3CM_RESET_CTRL             (I3CM_BASE_ADDR+ 0x34)
#define I3CM_SLV_EVENT_STATUS       (I3CM_BASE_ADDR+ 0x38)
#define I3CM_INTR_STATUS            (I3CM_BASE_ADDR+ 0x3c)
#define I3CM_INTR_STATUS_EN         (I3CM_BASE_ADDR+ 0x40)
#define I3CM_INTR_SIGNAL_EN         (I3CM_BASE_ADDR+ 0x44)
#define I3CM_INTR_FORCE             (I3CM_BASE_ADDR+ 0x48)
#define I3CM_QUEUE_STATUS_LEVEL     (I3CM_BASE_ADDR+ 0x4c)
#define I3CM_DATA_BUFFER_STATUS_LEVEL     (I3CM_BASE_ADDR+ 0x50)
#define I3CM_PRESENT_STATE                (I3CM_BASE_ADDR+ 0x54)
#define I3CM_CCC_DEVICE_STATUS            (I3CM_BASE_ADDR+ 0x58)
#define I3CM_DEVICE_ADDR_TABLE_POINTER    (I3CM_BASE_ADDR+ 0x5c)
#define I3CM_DEV_CHAR_TABLE_POINTER       (I3CM_BASE_ADDR+ 0x60)
#define I3CM_VENDOR_SPECIFIC_REG_POINTER  (I3CM_BASE_ADDR+ 0x6c)
#define I3CM_SLV_MIPI_ID_VALUE            (I3CM_BASE_ADDR+ 0x70)
#define I3CM_SLV_PID_VALUE                (I3CM_BASE_ADDR+ 0x74)
#define I3CM_SLV_CHAR_CTRL                (I3CM_BASE_ADDR+ 0x78)
#define I3CM_SLV_MAX_LEN                  (I3CM_BASE_ADDR+ 0x7c)
#define I3CM_MAX_READ_TURNAROUND          (I3CM_BASE_ADDR+ 0x80)
#define I3CM_MAX_DATA_SPEED               (I3CM_BASE_ADDR+ 0x84)
#define I3CM_SLV_INTR_REQ                 (I3CM_BASE_ADDR+ 0x8c)
#define I3CM_SLV_TSX_SYMBL_TIMING         (I3CM_BASE_ADDR+ 0x90)
#define I3CM_SLV_SIR_DATA                 (I3CM_BASE_ADDR+ 0x94)
#define I3CM_SLV_IBI_RESP                 (I3CM_BASE_ADDR+ 0x98)
#define I3CM_SLV_NACK_REQ                 (I3CM_BASE_ADDR+ 0x9c)
#define I3CM_SLV_NACK_CONF                (I3CM_BASE_ADDR+ 0xa0)
#define I3CM_SLV_INSTANT_STATUS           (I3CM_BASE_ADDR+ 0xa4)
#define I3CM_DEVICE_CTRL_EXTENDED         (I3CM_BASE_ADDR+ 0xb0)
#define I3CM_SCL_I3C_OD_TIMING            (I3CM_BASE_ADDR+ 0xb4)
#define I3CM_SCL_I3C_PP_TIMING            (I3CM_BASE_ADDR+ 0xb8)
#define I3CM_SCL_I2C_FM_TIMING            (I3CM_BASE_ADDR+ 0xbc)
#define I3CM_SCL_I2C_FMP_TIMING           (I3CM_BASE_ADDR+ 0xc0)
#define I3CM_SCL_EXT_LCNT_TIMING          (I3CM_BASE_ADDR+ 0xc8)
#define I3CM_SCL_EXT_TERMN_LCNT_TIMING    (I3CM_BASE_ADDR+ 0xcc)
#define I3CM_SDA_HOLD_SWITCH_DLY_TIMING   (I3CM_BASE_ADDR+ 0xd0)
#define I3CM_BUS_FREE_AVAIL_TIMING        (I3CM_BASE_ADDR+ 0xd4)
#define I3CM_BUS_IDLE_TIMING              (I3CM_BASE_ADDR+ 0xd8)
#define I3CM_SCL_LOW_MST_EXT_TIMEOUT      (I3CM_BASE_ADDR+ 0xdc)
#define I3CM_I3C_VER_ID                   (I3CM_BASE_ADDR+ 0xe0)
#define I3CM_I3C_VER_TYPE                 (I3CM_BASE_ADDR+ 0xe4)
#define I3CM_QUEUE_SIZE_CAPABILITY          (I3CM_BASE_ADDR+ 0xe8)
#define I3CM_SEC_DEV_CHAR_TABLE1            (I3CM_BASE_ADDR+ 0x200) // Change base address
#define I3CM_DEV_CHAR_TABLE1_LOC1           (I3CM_BASE_ADDR+ 0x200)
#define I3CM_DEV_CHAR_TABLE1_LOC2           (I3CM_BASE_ADDR+ 0x204)
#define I3CM_DEV_CHAR_TABLE1_LOC3           (I3CM_BASE_ADDR+ 0x208)
#define I3CM_DEV_CHAR_TABLE1_LOC4           (I3CM_BASE_ADDR+ 0x20c)
#define I3CM_DEV_CHAR_TABLE2_LOC1           (I3CM_BASE_ADDR+ 0x210)
#define I3CM_DEV_CHAR_TABLE2_LOC2           (I3CM_BASE_ADDR+ 0x214)
#define I3CM_DEV_CHAR_TABLE2_LOC3           (I3CM_BASE_ADDR+ 0x218)
#define I3CM_DEV_CHAR_TABLE2_LOC4           (I3CM_BASE_ADDR+ 0x21c)
#define I3CM_DEV_CHAR_TABLE3_LOC1           (I3CM_BASE_ADDR+ 0x220)
#define I3CM_DEV_CHAR_TABLE3_LOC2           (I3CM_BASE_ADDR+ 0x224)
#define I3CM_DEV_CHAR_TABLE3_LOC3           (I3CM_BASE_ADDR+ 0x228)
#define I3CM_DEV_CHAR_TABLE3_LOC4           (I3CM_BASE_ADDR+ 0x22c)
#define I3CM_DEV_CHAR_TABLE4_LOC1           (I3CM_BASE_ADDR+ 0x230)
#define I3CM_DEV_CHAR_TABLE4_LOC2           (I3CM_BASE_ADDR+ 0x234)
#define I3CM_DEV_CHAR_TABLE4_LOC3           (I3CM_BASE_ADDR+ 0x238)
#define I3CM_DEV_CHAR_TABLE4_LOC4           (I3CM_BASE_ADDR+ 0x23c)
//#define I3CM_DEV_ADDR_TABLE_LOC1           (I3CM_BASE_ADDR+ 0x220)
//#define I3CM_DEV_ADDR_TABLE1_LOC1           (I3CM_BASE_ADDR+ 0x220)
#define I3CM_DEV_ADDR_TABLE_LOC1           (I3CM_BASE_ADDR+ 0x380)
#define I3CM_DEV_ADDR_TABLE_LOC2           (I3CM_BASE_ADDR+ 0x384)
#define I3CM_DEV_ADDR_TABLE_LOC3           (I3CM_BASE_ADDR+ 0x388)
#define I3CM_DEV_ADDR_TABLE_LOC4           (I3CM_BASE_ADDR+ 0x38c)
//I3CM_DEV_ADDR_TABLE_LOC1 


#define I3CS_BASE_ADDR	                  0x2A010000
#define I3CS_DEVICE_CTRL                  (I3CS_BASE_ADDR+ 0x0)
#define I3CS_DEVICE_ADDR_ADDR             (I3CS_BASE_ADDR+ 0x4)
#define I3CS_HW_CAPABILITY                (I3CS_BASE_ADDR+ 0x8)
#define I3CS_COMMAND_QUEUE_PORT           (I3CS_BASE_ADDR+ 0xc)
#define I3CS_RESPONSE_QUEUE_PORT          (I3CS_BASE_ADDR+ 0x10)
#define I3CS_TX_DATA_PORT                 (I3CS_BASE_ADDR+ 0x14)
#define I3CS_RX_DATA_PORT                 (I3CS_BASE_ADDR+ 0x14)
#define I3CS_IBI_QUEUE_STATUS             (I3CS_BASE_ADDR+ 0x18)
#define I3CS_IBI_QUEUE_DATA               (I3CS_BASE_ADDR+ 0x18)
#define I3CS_QUEUE_THLD_CTRL              (I3CS_BASE_ADDR+ 0x1c)
#define I3CS_DATA_BUFFER_THLD_CTRL        (I3CS_BASE_ADDR+ 0x20)
#define I3CS_IBI_QUEUE_CTRL               (I3CS_BASE_ADDR+ 0x24)
#define I3CS_IBI_MR_REQ_REJECT            (I3CS_BASE_ADDR+ 0x2c)
#define I3CS_IBI_SIR_REQ_REJECT           (I3CS_BASE_ADDR+ 0x30)
#define I3CS_RESET_CTRL                   (I3CS_BASE_ADDR+ 0x34)
#define I3CS_SLV_EVENT_STATUS             (I3CS_BASE_ADDR+ 0x38)
#define I3CS_INTR_STATUS                  (I3CS_BASE_ADDR+ 0x3c)
#define I3CS_INTR_STATUS_EN               (I3CS_BASE_ADDR+ 0x40)
#define I3CS_INTR_SIGNAL_EN               (I3CS_BASE_ADDR+ 0x44)
#define I3CS_INTR_FORCE                   (I3CS_BASE_ADDR+ 0x48)
#define I3CS_QUEUE_STATUS_LEVEL           (I3CS_BASE_ADDR+ 0x4c)
#define I3CS_DATA_BUFFER_STATUS_LEVEL     (I3CS_BASE_ADDR+ 0x50)
#define I3CS_PRESENT_STATE                (I3CS_BASE_ADDR+ 0x54)
#define I3CS_CCC_DEVICE_STATUS            (I3CS_BASE_ADDR+ 0x58)
#define I3CS_DEVICE_ADDR_TABLE_POINTER    (I3CS_BASE_ADDR+ 0x5c)
#define I3CS_DEV_CHAR_TABLE_POINTER       (I3CS_BASE_ADDR+ 0x60)
#define I3CS_VENDOR_SPECIFIC_REG_POINTER  (I3CS_BASE_ADDR+ 0x6c)
#define I3CS_SLV_MIPI_ID_VALUE            (I3CS_BASE_ADDR+ 0x70)
#define I3CS_SLV_PID_VALUE                (I3CS_BASE_ADDR+ 0x74)
#define I3CS_SLV_CHAR_CTRL                (I3CS_BASE_ADDR+ 0x78)
#define I3CS_SLV_MAX_LEN                  (I3CS_BASE_ADDR+ 0x7c)
#define I3CS_MAX_READ_TURNAROUND          (I3CS_BASE_ADDR+ 0x80)
#define I3CS_MAX_DATA_SPEED               (I3CS_BASE_ADDR+ 0x84)
#define I3CS_SLV_INTR_REQ                 (I3CS_BASE_ADDR+ 0x8c)
#define I3CS_SLV_TSX_SYMBL_TIMING         (I3CS_BASE_ADDR+ 0x90)
#define I3CS_SLV_SIR_DATA                 (I3CS_BASE_ADDR+ 0x94)
#define I3CS_SLV_IBI_RESP                 (I3CS_BASE_ADDR+ 0x98)
#define I3CS_SLV_NACK_REQ                 (I3CS_BASE_ADDR+ 0x9c)
#define I3CS_SLV_NACK_CONF                (I3CS_BASE_ADDR+ 0xa0)
#define I3CS_SLV_INSTANT_STATUS           (I3CS_BASE_ADDR+ 0xa4)
#define I3CS_DEVICE_CTRL_EXTENDED         (I3CS_BASE_ADDR+ 0xb0)
#define I3CS_SCL_I3C_OD_TIMING            (I3CS_BASE_ADDR+ 0xb4)
#define I3CS_SCL_I3C_PP_TIMING            (I3CS_BASE_ADDR+ 0xb8)
#define I3CS_SCL_I2C_FM_TIMING            (I3CS_BASE_ADDR+ 0xbc)
#define I3CS_SCL_I2C_FMP_TIMING           (I3CS_BASE_ADDR+ 0xc0)
#define I3CS_BUS_FREE_AVAIL_TIMING           (I3CS_BASE_ADDR+ 0xd4)
#define I3CS_BUS_IDLE_TIMING              (I3CS_BASE_ADDR+ 0xd8)
#define I3CS_I3C_VER_ID                   (I3CS_BASE_ADDR+ 0xe0)
#define I3CS_I3C_VER_TYPE                 (I3CS_BASE_ADDR+ 0xe4)
#define I3CS_QUEUE_SIZE_CAPABILITY           (I3CS_BASE_ADDR+ 0xe8)

//#define I3C_REG_READ       printf("Value %x\n", a)
//#define I3C_REG_WRITE	   printf("0x%x 0x%x\n", a, v)
#define I3C_REG_READ_C(a)      (*(volatile uint8_t *)(a))
#define I3C_REG_WRITE_C(v, a)  (*(volatile uint8_t *)(a)) = (uint8_t)(v)
#define I3C_REG_READ_S(a)      (*(volatile uint16_t *)(a))
#define I3C_REG_WRITE_S(v, a)  (*(volatile uint16_t *)(a)) = (uint16_t)(v)
#define I3C_REG_READ(a)      (*(volatile uint32_t *)(a))
#define I3C_REG_WRITE(v, a)  (*(volatile uint32_t *)(a)) = (uint32_t)(v)
#define I3C_REG_READ_W(a)      (*(volatile uint64_t *)(a))
#define I3C_REG_WRITE_W(v, a)  (*(volatile uint64_t *)(a)) = (uint64_t)(v)

#define I3C_NUM_SLAVE_DEVICES   1
#if 0
static inline uint32_t i3c_reg_read(uint32_t addr) {
    return *(volatile uint32_t *)addr;
}

static inline void i3c_reg_write(uint32_t value, uint32_t addr) {
    *(volatile uint32_t *)addr = value;
}

#endif
struct slave_table
{
	uint32_t gfh_inst;
	uint32_t dev_index;
};

typedef struct {
    uint32_t opCode;
    uint32_t data0;
    uint32_t *pData;
} I3C_CMD;




void map_devIndx_to_DA(struct slave_table (*gfh_slave_table)[]);
int32_t i3c_slave_init(void);
int32_t i3c_master_init(void);
void i3c_master_assign_address(void);
int32_t i3c_master_write(struct slave_table *pGfh, uint32_t address, uint32_t *pData, uint32_t len);
int32_t i3c_master_read(struct slave_table *pGfh, uint32_t address, uint32_t *pData, uint32_t len);
void i3c_master_interrupt_handler(void);
int32_t i3c_private_read(uint8_t dev_index, I3C_CMD *pI3cCmd);
int32_t i3c_master_copy_data(struct slave_table *pGfh, uint32_t sAddr, uint32_t dAddr, uint32_t length);
int32_t i3c_master_send_jump_to_tim(struct slave_table *pGfh, uint32_t address);
void i3c_slave_interrupt_handler(void) __attribute__((interrupt));
int32_t i3c_slave_send_fw_dnld_resp(void);

uint32_t i3c_slave_get_jump_addr(void);
int32_t i3c_master_send_d2d_status(struct slave_table *pGfh, uint32_t d2d_mode);
uint32_t i3c_slave_get_d2d_status(void);
int32_t i3c_slave_send_d2d_resp(uint32_t d2d_status);

#endif
