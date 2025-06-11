#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdbool.h>

#define SIZE 0x10000

#define REG_LEN_OFFSET      (0x00 / sizeof(uint32_t))    // Length of shift operation in bits
#define REG_TMS_OFFSET      (0x04 / sizeof(uint32_t))    // TMS (Test Mode Select) register offset
#define REG_TDI_OFFSET      (0x08 / sizeof(uint32_t))    // TDI (Test Data In) register offset
#define REG_TDO_OFFSET      (0x0c / sizeof(uint32_t))    // TDO (Test Data Out) register offset
#define REG_CTRL_OFFSET     (0x10 / sizeof(uint32_t))   // Control register offset

#define BUSY_FLAG       (1 << 0)
#define SL_ERR          (1 << 1)
#define WR_RD_CMD       (1ULL << 66)
#define PPROT           (0x0ULL << 67)
#define START_TRANSACTION (1 << 7)
#define RESET           (1 << 8)

volatile uint32_t *ptr;
uint8_t apb_command[9];

//declare structure for the apb 72 bit data 
typedef struct apb_read_write {
    uint32_t busy : 1;
    uint32_t slerr : 1;
    uint32_t pdata;
    uint32_t paddr;
    uint32_t pwrite : 1;
    uint32_t pprot : 3;
    uint32_t pstart : 1;
    uint32_t preset : 1;
} apb_rd_wr_t;

// global declaration
apb_rd_wr_t apb_data;

void jtag_send(uint32_t tms, uint64_t tdi, uint32_t len) {
    ptr[REG_LEN_OFFSET] = len;
    ptr[REG_TMS_OFFSET] = tms;
    ptr[REG_TDI_OFFSET] = tdi;
    ptr[REG_CTRL_OFFSET] = 0x1; // Trigger JTAG transfer
}

void jtag_recv(uint32_t tms, void *tdo_out, uint32_t len) {
    ptr[REG_LEN_OFFSET] = len;
    ptr[REG_TMS_OFFSET] = tms;
    ptr[REG_CTRL_OFFSET] = 0x1;  // Trigger read
    
    uint32_t tdo_data = ptr[REG_TDO_OFFSET];
    if (len <= 32) {
        memcpy(tdo_out, &tdo_data, sizeof(uint32_t));
    }
}
void jtag_send_dr_data(uint8_t apb_command[9], uint32_t *tms, bool tdo_flag, uint32_t *tdo_buffer) {
    uint64_t dr_data_low = 0;
    uint8_t dr_data_high = apb_command[8];
    memcpy(&dr_data_low, apb_command, 8);

    uint32_t tdo_0 = 0, tdo_1 = 0;
    uint8_t tdo_2 = 0;

    jtag_send(tms[0], (uint32_t)(dr_data_low & 0xFFFFFFFF), 32);
    if (tdo_flag){ 
    	jtag_recv(tms[0], &tdo_0, 32);
	}
	
    jtag_send(tms[1], (uint32_t)(dr_data_low >> 32), 32);
    if (tdo_flag){
     jtag_recv(tms[1], &tdo_1, 32);
	}
    jtag_send(tms[2], dr_data_high, 8);
    if (tdo_flag){
     jtag_recv(tms[2], &tdo_2, 8);
    }
    
   if (tdo_buffer && tdo_flag) {
    uint32_t *tdo_buff = (uint32_t *)tdo_buffer;
    tdo_buff[0] = tdo_0;
    tdo_buff[1] = tdo_1;
    ((uint8_t*)tdo_buffer)[8] = tdo_2;
    }
}
//idle to cap_ir
void idle_to_cap_ir() {
    jtag_send(0xc, 0x0, 4);
}
//exit toshift_ir
void exit_ir_to_shift_dr() {
    jtag_send(0x14, 0x0, 5);
}
//exit to idle
void exit_to_idle() {
    jtag_send(0x5, 0x0, 4);
    printf("TMS Read/Write Sequence Complete\n");
}
/*TMS state Machine sequence */
void jtag_sequence(uint8_t apb_command[]){  
    //Idle to shift_ir state 
    idle_to_cap_ir();    
    
    // Shift-IR using an array
    jtag_send(0x8, 0x1, 4);
    
    // Exit-IR to Shift-DR
    exit_ir_to_shift_dr();
    
    // Shift-DR using an array
    uint32_t dr_tms[3] = {0}; // TMS for each block
    jtag_send_dr_data(apb_command, dr_tms,0,0);
    
    //after shift_dr
    printf("Shift DR TDI DONE in read\n");
    
    //print the all 72 bits data 
    print_apb_command(apb_command); 
    
    // Exit to idle state
    exit_to_idle();
}

void register_write(uint32_t addr, uint32_t data, uint32_t read_write){
    apb_data.busy = 0;
    apb_data.slerr = 0;
    apb_data.paddr = addr;
    apb_data.pdata = data;
    apb_data.pwrite = read_write;
    apb_data.pprot = 0;
    apb_data.pstart = 1;
    apb_data.preset = 1;

    uint64_t apb_data_low = 0;
    apb_data_low |= ((uint64_t)apb_data.busy    & 0x1)  << 0;   // Bit 0
    apb_data_low |= ((uint64_t)apb_data.slerr   & 0x1)  << 1;   // Bit 1
    apb_data_low |= ((uint64_t)apb_data.pdata   & 0xFFFFFFFF) << 2;  // Bits [33:2] - Data
    apb_data_low |= ((uint64_t)apb_data.paddr) << 34;
    uint8_t apb_data_high = ((apb_data.paddr >> 30) & 0x3); 
    memcpy(apb_command, &apb_data_low, 8);
    apb_command[8] = 0;
    
    // Store the remaining 8 bits separately
    apb_command[8] |= apb_data_high;  //Bit [65:64]
    apb_command[8] |= ((apb_data.pwrite & 0x1) << 2);  // Bit [66]
    apb_command[8] |= ((apb_data.pprot  & 0x7) << 3);  // Bits [69:67]
    apb_command[8] |= ((apb_data.pstart & 0x1) << 6);  // Bit 70
    apb_command[8] |= ((apb_data.preset & 0x1) << 7);  // Bit 71

    printf("APB Command (72-bit Packed): 0x");
    for (int i = 8; i >= 0; i--) {
        printf("%02X", apb_command[i]);
    }
    printf("\n");

    jtag_sequence(apb_command);
    while ((ptr[REG_TDO_OFFSET] & BUSY_FLAG)) {
        printf("Busy flag detected, retrying JTAG sequence...\n");
        jtag_sequence(apb_command);
    }
    jtag_sequence(apb_command);
    ptr[REG_TDI_OFFSET] &= ~START_TRANSACTION;
}

void register_read(uint32_t addr, uint32_t data, uint32_t read_write) {
    apb_data.busy = 0;
    apb_data.slerr = 0;
    apb_data.paddr = addr;
    apb_data.pdata = data;
    apb_data.pwrite = read_write;
    apb_data.pprot = 0;
    apb_data.pstart = 1;
    apb_data.preset = 1;

    uint64_t apb_data_low = 0;
    apb_data_low |= ((uint64_t)apb_data.busy    & 0x1)  << 0;   // Bit 0
    apb_data_low |= ((uint64_t)apb_data.slerr   & 0x1)  << 1;   // Bit 1
    apb_data_low |= ((uint64_t)apb_data.pdata   & 0xFFFFFFFF) << 2;  // Bits [33:2] - Data
    
    apb_data_low |= ((uint64_t)apb_data.paddr) << 34;
    uint8_t apb_data_high = ((apb_data.paddr >> 30) & 0x3);
    
    memcpy(apb_command, &apb_data_low, 8);
    apb_command[8] = 0;
    
    // Store the remaining 8 bits separately
    apb_command[8] |= apb_data_high;  //Bit [65:64]
    apb_command[8] |= ((apb_data.pwrite & 0x1) << 2);  // Bit [66]
    apb_command[8] |= ((apb_data.pprot  & 0x7) << 3);  // Bits [69:67]
    apb_command[8] |= ((apb_data.pstart & 0x1) << 6);  // Bit 70
    apb_command[8] |= ((apb_data.preset & 0x1) << 7);  // Bit 71

    printf("APB Command (72-bit Packed): 0x");
    for (int i = 8; i >= 0; i--) {
        printf("%02X", apb_command[i]);
    }
    printf("\n");

    jtag_sequence(apb_command);
    while ((ptr[REG_TDO_OFFSET] & BUSY_FLAG)) {
            printf("Busy flag detected, retrying JTAG sequence...\n");
              jtag_sequence(apb_command);
   }
   
   jtag_sequence(apb_command); //shift_dr_state
    while ((ptr[REG_TDO_OFFSET] & BUSY_FLAG)) {
            printf("Busy flag detected, retrying JTAG sequence...\n");
              jtag_sequence(apb_command);
   }
   
   jtag_sequence(apb_command); //shift_dr_state
    // Read TDO data
    uint32_t tms[3]={0};
    uint32_t tdo_values[3] = {0}; // Array to hold the three 32-bit TDO values
    jtag_send_dr_data(apb_command,tms,true,tdo_values);
     
    // Combine the TDO values into a single 72-bit value
    uint64_t final_tdo_value = 0;
    final_tdo_value |= ((uint64_t)tdo_values[0]) << 0;   // First 32 bits
    final_tdo_value |= ((uint64_t)tdo_values[1]) << 32;  // Next 32 bits
    final_tdo_value |= ((uint64_t)(tdo_values[2] & 0xFF)) << 64; // Last 8 bits

    printf("Final TDO register value after read is 0x%016llX\n", final_tdo_value);
}

void print_apb_command(uint8_t apb_command[9]) {
    uint64_t apb_data_low = 0;
    memcpy(&apb_data_low, apb_command, 8);  // Extract first 64 bits
    uint8_t apb_data_high = apb_command[8];  // Extract remaining 8 bits

    // Extracting individual fields
    uint8_t busy = (apb_data_low >> 0) & 0x1;
    uint8_t slerr = (apb_data_low >> 1) & 0x1;
    uint32_t pdata = (apb_data_low >> 2) & 0xFFFFFFFF;
    uint32_t paddr = ((apb_data_low >> 34) & 0x3FFFFFFF) | ((apb_data_high & 0x03) << 30);
    uint8_t pwrite = (apb_data_high >> 2) & 0x1;
    uint8_t pprot = (apb_data_high >> 3) & 0x7;
    uint8_t pstart = (apb_data_high >> 6) & 0x1;
    uint8_t preset = (apb_data_high >> 7) & 0x1;

    printf("\nAPB Command Breakdown (72-bit)\n");
    printf("Busy    (Bit 0)   : %u\n", busy);
    printf("SLERR   (Bit 1)   : %u\n", slerr);
    printf("PDATA   (Bits 2-33): 0x%08X\n", pdata);
    printf("PADDR   (Bits 34-65): 0x%08X\n", paddr);
    printf("PWRITE  (Bit 66)  : %u\n", pwrite);
    printf("PPROT   (Bits 67-69): 0x%X\n", pprot);
    printf("PSTART  (Bit 70)  : %u\n", pstart);
    printf("PRESET  (Bit 71)  : %u\n", preset);
}
// function to check read or write on this pwrite in abp 72-bits
int main(int argc, char *argv[]) {
    int fd;
    void *mapped;
    uint32_t addr, data, rd_wr_flag;

    if (argc < 3) {
        printf("Usage:\n");
        printf("  Write: %s 1 <address> <data>\n", argv[0]); // ./a.out
        printf("  Read:  %s 0 <address>\n", argv[0]);
        return -1;
    }

    fd = open("/dev/uio0", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("open");
        return -1;
    }
    mapped = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return -1;
    }
    ptr = (volatile uint32_t *)((char *)mapped);
    printf("Mapped address for registers: %p\n", ptr);

    printf("Initial REG_LEN_OFFSET: 0x%X\n", ptr[REG_LEN_OFFSET]);
    printf("Initial REG_CTRL_OFFSET: 0x%X\n", ptr[REG_CTRL_OFFSET]);
  
    if (sscanf(argv[1], "%u", &rd_wr_flag) != 1) { // pass value rd_wr_flag argv[1]
        printf("Invalid operation type: %s\n", argv[1]);
        munmap(mapped, SIZE);
        close(fd);
        return -1;
    }
    
    // pass address as arugument  argv[2] 
        if (sscanf(argv[2], "%x", &addr) != 1) {
        printf("Invalid address: %s\n", argv[2]);
        munmap(mapped, SIZE);
        close(fd);
        return -1;
    }

    // check the rd_wr_flad for read/write fuction to call
    if (rd_wr_flag == 1) { // Write
        if (argc != 4) {
            if (argc < 4) {
                printf("Write requires address and data\n");
            } else {
                printf("Too many arguments for write operation\n");
            }
            munmap(mapped, SIZE);
            close(fd);
            return -1;
        }
        // pass data as argument
            if (sscanf(argv[3], "%x", &data) != 1) {
            printf("Invalid data: %s\n", argv[3]);
            munmap(mapped, SIZE);
            close(fd);
            return -1;
        }
        printf("Writing 0x%X to address 0x%X\n", data, addr);
        register_write(addr, data, 1);

    } else if (rd_wr_flag == 0) { // Read
        if (argc != 3) {
            printf("Read requires only address\n");
            munmap(mapped, SIZE);
            close(fd);
            return -1;
        }            
        printf("Reading  address 0x%X\n", addr); 
        register_read(addr, 0, 0);
    } else {
        printf("Invalid operation: %u\n", rd_wr_flag);
    }

    if (munmap(mapped, SIZE) < 0) {
        perror("munmap");
    }
    close(fd);
    return 0;
}
