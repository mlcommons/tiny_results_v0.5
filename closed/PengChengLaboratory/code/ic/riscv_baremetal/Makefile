# --------------------------------- #
#  Generic Makefile (based on gcc)  #
# --------------------------------- #
ARCH ?= 32
ifeq ($(ARCH),64)
	SRCARCH := arch/rv64
	QEMU := qemu-system-riscv64
endif
ifeq ($(ARCH),32)
	SRCARCH := arch/rv32
	QEMU := qemu-system-riscv32
endif

#####################################
# Target
#####################################
TARGET = riscv$(ARCH)_baremetal


#####################################
# Building Variables
#####################################
# debug build?
DEBUG = 1
# optimization
OPT = -O0


#####################################
# Paths
#####################################
# build path
BUILD_DIR = build
# cross tools path
TOOLS_PATH = $(PWD)/tools
GCC_PATH = $(TOOLS_PATH)/toolchain/bin
BIN2HEX_PATH = $(TOOLS_PATH)/bin2hex


#####################################
# Sources
#####################################
# C sources
C_SOURCES = \
main.c \
lib/debug.c \
lib/event_unit.c \
lib/riscv.c \
lib/system.c \
lib/syscall_stubs.c \
drivers/uart.c \
drivers/wdt.c \
drivers/trng.c \
drivers/gpio.c \
drivers/dma.c \
drivers/timer.c \
drivers/i2c.c \
drivers/spi.c \
test/coremark/core_list_join.c \
test/coremark/core_main.c \
test/coremark/core_matrix.c \
test/coremark/core_portme.c \
test/coremark/core_state.c \
test/coremark/core_util.c \
test/coremark/cvt.c \
test/whets.c \
test/dma_test.c \
test/gpio_test.c \
test/gpio_count.c \
test/wdt_test.c \
test/timer_test.c \
test/regs_probe.c \
test/dual_io_test.c

# Asm sources
ASM_SOURCES = \
$(SRCARCH)/startup.s

#####################################
# Binaries
#####################################
PREFIX = riscv-none-embed-
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
HEX = $(BIN2HEX_PATH)/Bin2Hex1B
HEX4B = $(BIN2HEX_PATH)/Bin2Hex4B
BIN = $(CP) -O binary -S
GDB = $(GCC_PATH)/$(PREFIX)gdb
OBJDUMP = $(GCC_PATH)/$(PREFIX)objdump


#####################################
# CFLAGS
#####################################
# cpu
ifeq ($(ARCH),64)
CPU = -march=rv64ima -mabi=lp64 -mcmodel=medany
endif
ifeq ($(ARCH),32)
CPU = -march=rv32imaf -mabi=ilp32f -mcmodel=medany
endif
# fpu
FPU =
# float-abi
FLOAT_ABI =
# mcu
MCU = $(CPU) $(FPU) $(FLOAT_ABI)

# macros for gcc
# AS defines
AS_DEFS =
# C defines
C_DEFS =

# AS includes
AS_INCLUDES =
# C includes
C_INCLUDES = \
-Iinclude \
-Iinclude/cmsis \
-Iinclude/device \
-Iinclude/drivers \
-Iinclude/lib

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif
# generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

#####################################
# LDFLAGS
#####################################
# link script
LDSCRIPT = $(SRCARCH)/rv32_flash.ld
# libraries
LIBS = -lc -lm -lnosys
LIBDIR = ./
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) -L$(LIBDIR) $(LIBS) -nostartfiles -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections


#####################################
# Build the Applications
#####################################
# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).4B.hex $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).S

# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of assembly program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.bin | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.4B.hex: $(BUILD_DIR)/%.bin | $(BUILD_DIR)
	$(HEX4B) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR)/%.S: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(OBJDUMP) -S $< > $@

$(BUILD_DIR):
	mkdir $@


#####################################
# Clean Up
#####################################
clean:
	-rm -fR $(BUILD_DIR)


run:
	$(QEMU) -m 256M -M virt -nographic -serial mon:stdio -kernel build/riscv$(ARCH)_baremetal.elf

debug:
	$(QEMU) -m 256M -M virt -nographic -serial mon:stdio -kernel build/riscv$(ARCH)_baremetal.elf -S -s

gdb:
	$(GDB) build/$(ARCH)_baremetal.elf

cscope:
	find . -name "*.[chs]" > cscope.files
	cscope -k -q -b

#####################################
# Dependencies
#####################################
-include $(wildcard $(BUILD_DIR)/$.d)


# -------------- EOF -------------- #
