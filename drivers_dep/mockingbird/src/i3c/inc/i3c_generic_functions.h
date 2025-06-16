
#ifndef I3C_GENERIC_H
#define I3C_GENERIC_H
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>

#define I3C_ID_1 	11
#define I3C_ID_0 	10

#define READ_REGISTER_OPCODE 0x01
#define WRITE_REGISTER_OPCODE 0x02
#define READ_REGISTER_RESPONSE_OPCODE 0x03
#define WRITE_REGISTER_RESPONSE_OPCODE 0x04
#define D2D_OPCODE 0x5
#define D2D_RESP_OPCODE 0x6
#define FW_DOWNLOAD_COMPLETE_OPCODE 0x80
#define FW_DOWNLOAD_COMPLETE_RESP_OPCODE 0x81
#define JUMP_CHECK_OPCODE 0x80
#define JUMP_CHECK_RESP_OPCODE 0x81

#define I3C_OPCODE_MASK 0xFF
#define I3C_DATALEN_MASK 0xFFFF00
#define I3C_ERROR_MASK 0xFF000000
#define I3C_DATALEN_POS 8
#define I3C_ERROR_POS 24

/* IMP NOTE:
 * I3C_RX_BUF_MAX wont work for 2 entries, SNPS handling 2 entries case
 * differently, even though we config for 2 entries its configuring
 * it for 1 entry */
#define I3C_RX_BUF_MAX 64
 
#define I3C_INTERRUPT_ID 41
#define GFH_I3C_READY	18

#define I3C_MIPI_MID 0x0528
// adress 0 to 31 transfer command 

#define TC_CMD_ATR ((uint32_t) 0x0000) 
#define TC_TID ((uint32_t) 0x0003) 
#define TC_CMD ((uint32_t) 0x0007) 
#define TC_CP ((uint32_t) 0x000f) 
#define TC_DEV_INDX ((uint32_t) 0x0010) 
#define TC_SPEED ((uint32_t) 0x0015) 
#define TC_DBP ((uint32_t) 0x0019) 
#define TC_ROC ((uint32_t) 0x001a) 
#define TC_SDAP ((uint32_t) 0x001b) 
#define TC_RnW ((uint32_t) 0x001c) 
#define TC_TOC ((uint32_t) 0x001e) 
#define TC_PEC ((uint32_t) 0x001f) 


// adress 100 to 131 transfer argument 

#define TA_CMD_ATR ((uint32_t) 0x0064) 
#define TA_DB ((uint32_t) 0x006c) 
#define TA_DATA_LENGTH ((uint32_t) 0x0074) 


//adress 200 to 231 short data argument 

#define SDA_CMD_ATR ((uint32_t) 0x00c8) 
#define SDA_BYTE_STRB ((uint32_t) 0x00cb) 
#define SDA_DATA_BYTE1 ((uint32_t) 0x00d0) 
#define SDA_DATA_BYTE2 ((uint32_t) 0x00d8) 
#define SDA_DATA_BYTE3 ((uint32_t) 0x00e0) 


//adress 300 to 331 address assignment command

#define AAC_CMD_ATR ((uint32_t) 0x012c) 
#define AAC_TID ((uint32_t) 0x012f) 
#define AAC_CMD ((uint32_t) 0x0133) 
#define AAC_RSVD ((uint32_t) 0x013b) 
#define AAC_DEV_INDX ((uint32_t) 0x013c) 
#define AAC_DEV_COUNT ((uint32_t) 0x0141) 
#define AAC_ROC ((uint32_t) 0x0146) 
#define AAC_TOC ((uint32_t) 0x014a) 

//adress 400 t0 431 target transmit command

#define TTC_CMD_ATR ((uint32_t) 0x0190) 
#define TTC_TID ((uint32_t) 0x0193) 
#define TTC_DATA_LENGTH ((uint32_t) 0x01a0) 

#define DEBUG_GPIO12 12
#define DEBUG_GPIO13 13
#define DEBUG_GPIO14 14

typedef enum
{
	LOW,
	HIGH
} e_gpio_state;

int get_i3c_address(uint8_t* i3c_address);
uint8_t set_i3c_ready(void);
uint8_t get_i3c_ready(uint8_t inst);
uint8_t  toggle_i3c_ready(void);
uint8_t  debug_gpio_set(uint8_t state);
void transfer_cmd(uint32_t field, uint32_t val);
void transfer_arg(uint32_t field, uint32_t val);
void short_data_arg(uint32_t field, uint32_t val);
void add_asgn_cmd(uint32_t field, uint32_t val);
void transmit_cmd(uint32_t field, uint32_t val);
#endif
