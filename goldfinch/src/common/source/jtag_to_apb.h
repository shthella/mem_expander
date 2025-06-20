
#ifndef JTAG_APB_H
#define JTAG_APB_H

#include <stdint.h>
#include <stdbool.h>
#define JTAG_BASE_ADDR  0x40000000U

//jtag flow 
void jtag_send(uint32_t tms, uint64_t tdi, uint32_t len);
void jtag_recv(uint32_t tms, void *tdo_out, uint32_t len);
void jtag_send_dr_data(uint8_t apb_command[9], uint32_t *tms, bool tdo_flag, uint32_t *tdo_buffer);

// TAP FSM state transitions
void idle_to_cap_ir(void);
void exit_ir_to_shift_dr(void);
void exit_to_idle(void);

// APB operation sequencing
void jtag_sequence(uint8_t apb_command[]);

// Register read/write interfaces
void jtag_register_write(uint32_t addr, uint32_t data);
void jtag_register_read(uint32_t addr);


int jtag_main();
#endif

