################################################################################
# FreeRTOS UART Interrupt Project - Zybo Board
################################################################################

TARGET = GFH
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIRS = $(shell find $(SRC_DIR) -type d)

CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
AS = arm-none-eabi-gcc
SIZE = arm-none-eabi-size

CFLAGS = -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -O2 -Wall -ffreestanding -nostdlib $(addprefix -I, $(INCLUDE_DIRS))
ASFLAGS = $(CFLAGS)
LDFLAGS = -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostdlib -Wl,-T,$(SRC_DIR)/lscript.ld
LIBS = -Wl,--start-group,-lgcc,-lc,--end-group

FREERTOS_SRC := $(wildcard $(SRC_DIR)/freertos/Source/*.c)
FREERTOS_SRC += $(SRC_DIR)/freertos/heap_4.c

C_SRCS := $(shell find $(SRC_DIR) -name '*.c')
S_SRCS := $(shell find $(SRC_DIR) -name '*.S')
OBJS := $(C_SRCS:%.c=%.o) $(S_SRCS:%.S=%.o) $(FREERTOS_SRC:%.c=%.o)

all: $(TARGET).elf

$(TARGET).elf: $(OBJS)
	@echo "Linking: $@"
	$(LD) -o $@ $^ $(LDFLAGS) $(LIBS)
	@$(SIZE) $@

%.o: %.c
	@echo "Compiling C: $<"
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	@echo "Compiling ASM: $<"
	$(AS) $(ASFLAGS) -c $< -o $@

clean:
	find $(SRC_DIR) -name "*.o" -delete
	rm -f $(TARGET).elf
	rm -f $(SRC_DIR)/freertos/.o

.PHONY: all clean
