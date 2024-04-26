PROJECT_NAME = Free_RTOS
INC_DIR = Lib/Inc
SRC_DIR = Lib/Src
OUTPUT_DIR = Output
STARTUP_DIR = Startup_file
LINKER_DIR = Linker
MAIN_DIR = Core

INC_RTOS_DIR = FreeRTOS/FreeRTOS-Kernel/include
SRC_RTOS_DIR = FreeRTOS/FreeRTOS-Kernel

INC_PORT_DIR = FreeRTOS/FreeRTOS-Kernel/portable/GCC/ARM_CM3
SRC_PORT_DIR = FreeRTOS/FreeRTOS-Kernel/portable/GCC/ARM_CM3

SRC_MEM_DIR = FreeRTOS/FreeRTOS-Kernel/portable/MemMang

#compiler
CC = arm-none-eabi-gcc
#asembler
AS = arm-none-eabi-as
#linker
LD = arm-none-eabi-ld
#objcopy
OBJCOPY = arm-none-eabi-objcopy
#size
SIZE = arm-none-eabi-size
#st-link
STLINK = ST-LINK_CLI

CFLAGS = -mcpu=cortex-m3 -mthumb -Wall -std=gnu11 -I$(INC_DIR)/ -I$(INC_RTOS_DIR)/ -I$(INC_PORT_DIR)/
ASFLAGS = -mcpu=cortex-m3 -mthumb
LDFLAGS = -mcpu=cortex-m3 -T"$(LINKER_DIR)/STM32F103C8TX_FLASH.ld" -Wl,-Map=$(OUTPUT_DIR)/$(PROJECT_NAME).map -Wl,--no-warn-rwx -Wl,--gc-sections -N -static
STFLAGS = $(OUTPUT_DIR)/$(PROJECT_NAME).hex

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OUTPUT_DIR)/%.o,$(SRCS))

SRCS1 = $(wildcard $(SRC_RTOS_DIR)/*.c)
OBJS1 = $(patsubst $(SRC_RTOS_DIR)/%.c,$(OUTPUT_DIR)/%.o,$(SRCS1))

all: $(OUTPUT_DIR)/$(PROJECT_NAME).elf flash

$(OUTPUT_DIR)/main.o: $(MAIN_DIR)/main.c
	$(CC) -c $(CFLAGS) -o $@ $<
	
$(OUTPUT_DIR)/port.o: $(SRC_PORT_DIR)/port.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(OUTPUT_DIR)/heap_4.o: $(SRC_MEM_DIR)/heap_2.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(OUTPUT_DIR)/startup_stm32f103c8tx.o: $(STARTUP_DIR)/startup_stm32f103c8tx.s
	$(AS) -c $(ASFLAGS) -o $@ $<

$(OUTPUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(OUTPUT_DIR)/%.o: $(SRC_RTOS_DIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(OUTPUT_DIR)/$(PROJECT_NAME).elf: $(OUTPUT_DIR)/port.o $(OUTPUT_DIR)/heap_4.o $(OUTPUT_DIR)/main.o $(OBJS) $(OBJS1) $(OUTPUT_DIR)/startup_stm32f103c8tx.o
# $(CC) $(OUTPUT_DIR)/port.o $(OUTPUT_DIR)/heap_4.o $(OBJS) $(OBJS1) $(OUTPUT_DIR)/main.o $(OUTPUT_DIR)/startup_stm32f103c8tx.o $(LDFLAGS) -o $@
	$(CC) $^ $(LDFLAGS) -o $@
	$(OBJCOPY) -O ihex $@ $(OUTPUT_DIR)/$(PROJECT_NAME).hex
	$(OBJCOPY) -O binary $@ $(OUTPUT_DIR)/$(PROJECT_NAME).bin
	$(SIZE) $@
	@echo "-----------------------------------------Done.Please, connect microcontroller!--------------------------------------------------"
clear:
	rm -rf $(OUTPUT_DIR)/*
flash:
	$(STLINK) -c SWD -P $(STFLAGS) -V -Run
test: $(SRCS) $(OBJS)
	@echo "gia tri : $(OBJS)"
	@echo "gia tri : $(SRCS)"
	@echo "gia tri @ : $@"
	@echo "gia tri ^: $^"
	@echo "gia tri <: $<"
.PHONY: all clear flash test
