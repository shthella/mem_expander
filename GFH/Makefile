################################################################################
# FreeRTOS UART Interrupt Project - Zybo Board
################################################################################

# Project settings
TARGET = GFH
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIRS = $(shell find $(SRC_DIR) -type d)

# Toolchain and flags
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
SIZE = arm-none-eabi-size
CFLAGS = -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -O2 $(addprefix -I, $(INCLUDE_DIRS))
LDFLAGS = -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -Wl,-build-id=none -specs=Xilinx.spec -Wl,-T,$(SRC_DIR)/lscript.ld -Llib $(LIBS)
LIBS = -Wl,--start-group,-lxil,-lfreertos,-lgcc,-lc,--end-group

# Automatically collect all .c source files recursively
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%.c=%.o)

# Default target
all: $(TARGET).elf

# Linking
$(TARGET).elf: $(OBJS)
	@echo "Building target: $@"
	$(LD) -o $@ $^ $(LDFLAGS)
	@$(SIZE) $@

# Compilation
%.o: %.c
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(SRC_DIR)/**/*.o $(TARGET).elf
	find $(SRC_DIR) -name "*.o" -delete
	rm -f $(TARGET).elf $(TARGET).elf.size

.PHONY: all clean

