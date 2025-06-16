#include "i3c.h"
#include <gpio.h>

extern uint32_t transfer_command;
extern uint32_t transfer_argument;
extern uint32_t short_data_argument;
extern uint32_t address_assignment_command;
extern uint32_t transmit_command;

// Read I3C ready pin. inst is the GFH instance number
uint8_t get_i3c_ready(uint8_t inst)
{
	struct metal_gpio *gpio;

	//gpio = metal_gpio_get_device(0);
	if (gpio == NULL) {
		return 1;
	}

	if(I3C_NUM_SLAVE_DEVICES > 0)
	{
		if(inst == 0x0)
		{
//			metal_gpio_enable_input(gpio, 18);
//			return metal_gpio_get_input_pin(gpio, 18);
			return 1;
		}
	}
	if(I3C_NUM_SLAVE_DEVICES > 1)
	{
		if(inst == 0x1)
		{
			metal_gpio_enable_input(gpio, 17);
			return metal_gpio_get_input_pin(gpio, 17);
		}
	}
	if(I3C_NUM_SLAVE_DEVICES > 2)
	{
		if(inst == 0x2)
		{
			metal_gpio_enable_input(gpio, 16);
			return metal_gpio_get_input_pin(gpio, 16);
		}
	}
	if(I3C_NUM_SLAVE_DEVICES > 3)
	{
		if(inst == 0x3)
		{
			metal_gpio_enable_input(gpio, 15);
			return metal_gpio_get_input_pin(gpio, 15);
		}
	}
}

int get_i3c_address(uint8_t* i3c_address)
{
	e_gpio_state gpio_state;

	struct metal_gpio *gpio;

//	gpio = metal_gpio_get_device(0);
	if (gpio == NULL) {
		return 1;
	}

//	metal_gpio_enable_input(gpio, I3C_ID_1);
//	metal_gpio_enable_input(gpio, I3C_ID_0);
//	gpio_state = metal_gpio_get_input_pin(gpio, I3C_ID_1);
	*i3c_address = *i3c_address | gpio_state << 1;
//	gpio_state = metal_gpio_get_input_pin(gpio, I3C_ID_0);
	*i3c_address = *i3c_address | gpio_state << 0;

	return 0;

}

uint8_t set_i3c_ready(void) 
{
	struct metal_gpio *gpio;

//	gpio = metal_gpio_get_device(0);
	if (gpio == NULL) {
		return 1;
	}

	//metal_gpio_enable_output(gpio, GFH_I3C_READY);
//	metal_gpio_set_pin(gpio, GFH_I3C_READY,1);

	return 0;
}

uint8_t toggle_i3c_ready(void)
{
	struct metal_gpio *gpio;

//	gpio = metal_gpio_get_device(0);
	if (gpio == NULL) {
		return 1;
	}

	uint8_t i3c_ready = 0;

//	i3c_ready = metal_gpio_get_input_pin(gpio, GFH_I3C_READY);
//	metal_gpio_set_pin(gpio, GFH_I3C_READY,i3c_ready ^ 0x1);

	return 0;
}

uint8_t debug_gpio_set(uint8_t state)
{
	struct metal_gpio *gpio;

//	gpio = metal_gpio_get_device(0);
	if (gpio == NULL) {
		return 1;
	}

//	metal_gpio_enable_output(gpio, DEBUG_GPIO12); //pin 12
//	metal_gpio_enable_output(gpio, DEBUG_GPIO13); //pin 13
//	metal_gpio_enable_output(gpio, DEBUG_GPIO14); //pin 14

	// Bit 2: GPIO_12, Bit 1: GPIO_13, Bit 0: GPIO_14
//	metal_gpio_set_pin(gpio, DEBUG_GPIO12, (state >> 0x2) & 0x1);
//	metal_gpio_set_pin(gpio, DEBUG_GPIO13, (state >> 0x1) & 0x1);
//	metal_gpio_set_pin(gpio, DEBUG_GPIO14, (state >> 0x0) & 0x1);

	return 0;
}

void transfer_cmd(uint32_t field, uint32_t val)
{
	if(field==31){
		transfer_command= ((0x80000000&(val<<31))|(transfer_command));}
	else if(field==30){
	         transfer_command= ((0x40000000&(val<<30))|(transfer_command));}
	else if(field==28){
	         transfer_command= ((0x10000000&(val<<28))|(transfer_command));}
	else if(field==27){
	         transfer_command= (0x08000000&(val<<27))|(transfer_command);}
	else if(field==26){
	         transfer_command= (0x04000000&(val<<26))|(transfer_command);}
	else if(field==25){
	         transfer_command= (0x02000000&(val<<25))|(transfer_command);}
	else if(field==21){
	         transfer_command= (0x00e00000&(val<<21))|(transfer_command);}
	else if(field==16){
	         transfer_command= (0x001f0000&(val<<16))|(transfer_command);}
	else if(field==15){
	         transfer_command= (0x00008000&(val<<15))|(transfer_command);}
	else if(field==7){
	         transfer_command= (0x00007f80&(val<<7))|(transfer_command);}
	else if(field==3){
	         transfer_command= (0x00000078&(val<<3))|(transfer_command);}
	else if(field==0){
		transfer_command= (0x00000007&(val<<0))|(transfer_command);}
	else{
			 //printf("Given adress is not in register field\n");
			 }
}



void transfer_arg(uint32_t field, uint32_t val)
{
	if(field==116){
		transfer_argument= ((0xffff0000&(val<<16))|(transfer_argument));}
	else if(field==108){
	         transfer_argument= ((0x0000ff00&(val<<8))|(transfer_argument));}
	else if(field==100){
	         transfer_argument= ((0x00000007&(val<<0))|(transfer_argument));}
	else{
			 //printf("Given adress is not in register field\n");
			 }
}



void short_data_arg(uint32_t field, uint32_t val)
{
	if(field==224){
	         short_data_argument= ((0xff000000&(val<<24))|(short_data_argument));}
	else if(field==216){
	         short_data_argument= ((0x00ff0000&(val<<16))|(short_data_argument));}
	else if(field==208){
	         short_data_argument= ((0x0000ff00&(val<<8))|(short_data_argument));}
	else if(field==203){
	         short_data_argument= ((0x00000078&(val<<3))|(short_data_argument));}
	else if(field==200){
	         short_data_argument= ((0x00000007&(val<<0))|(short_data_argument));}
	else{
			 //printf("Given adress is not in register field\n");
		 }
}


void add_asgn_cmd(uint32_t field, uint32_t val)
{
	if(field==330){
		address_assignment_command= ((0x40000000&(val<<30))|(address_assignment_command));}
	else if(field==326){
	         address_assignment_command= ((0x04000000&(val<<26))|(address_assignment_command));}
	else if(field==321){
	         address_assignment_command= ((0x03e00000&(val<<21))|(address_assignment_command));}
	else if(field==316){
	         address_assignment_command= (0x001f0000&(val<<16))|(address_assignment_command);}
	else if(field==315){
	         address_assignment_command= (0x00008000&(val<<15))|(address_assignment_command);}
	else if(field==307){
	         address_assignment_command= (0x00007f80&(val<<7))|(address_assignment_command);}
	else if(field==303){
	         address_assignment_command= (0x00000078&(val<<3))|(address_assignment_command);}
	else if(field==300){
	         address_assignment_command= (0x00000007&(val<<0))|(address_assignment_command);}
	else{
			 //printf("Given adress is not in register field\n");
			 }
}

void transmit_cmd(uint32_t field, uint32_t val)
{
	if(field==416){
		transmit_command= ((0xffff0000&(val<<16))|(transmit_command));}
	else if(field==403){
	         transmit_command= ((0x00000038&(val<<3))|(transmit_command));}
	else if(field==400){
	         transmit_command= ((0x00000007&(val<<0))|(transmit_command));}
	else{
			 //printf("Given adress is not in register field\n");
		 }
}
