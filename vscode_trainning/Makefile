# STM32F103C8T6 + 标准外设库(SPL) 工程 Makefile
# 用法: make        编译
#       make flash  通过 ST-Link 烧录
#       make clean  清理

TARGET   = blink
BUILD    = build
CROSS    ?= arm-none-eabi-

CC       = $(CROSS)gcc
OBJCOPY  = $(CROSS)objcopy
SIZE     = $(CROSS)size

LIBROOT  = ../STM32F10x_StdPeriph_Lib_V3.5.0/Libraries
SPL      = $(LIBROOT)/STM32F10x_StdPeriph_Driver
CMSIS    = $(LIBROOT)/CMSIS/CM3

# 源文件: 用户代码 + CMSIS + 全部 SPL 外设驱动
SRCS  = $(wildcard src/*.c)
SRCS += $(CMSIS)/CoreSupport/core_cm3.c
SRCS += $(CMSIS)/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
SRCS += $(wildcard $(SPL)/src/*.c)
ASM   = startup/startup_stm32f10x_md.s

OBJS  = $(addprefix $(BUILD)/,$(notdir $(SRCS:.c=.o)))
OBJS += $(BUILD)/startup_stm32f10x_md.o
vpath %.c src $(CMSIS)/CoreSupport $(CMSIS)/DeviceSupport/ST/STM32F10x $(SPL)/src
vpath %.s startup

INCS  = -Iinc -I$(SPL)/inc -I$(CMSIS)/CoreSupport -I$(CMSIS)/DeviceSupport/ST/STM32F10x

CFLAGS  = -mcpu=cortex-m3 -mthumb -Os -g -Wall
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000
CFLAGS += $(INCS)

LDFLAGS  = -mcpu=cortex-m3 -mthumb -Tstm32f103c8t6.ld
LDFLAGS += -Wl,--gc-sections -Wl,-Map=$(BUILD)/$(TARGET).map

all: $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).hex $(BUILD)/$(TARGET).bin
	$(SIZE) $(BUILD)/$(TARGET).elf

$(BUILD)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

$(BUILD)/%.hex: $(BUILD)/%.elf
	$(OBJCOPY) -O ihex $< $@

$(BUILD)/%.bin: $(BUILD)/%.elf
	$(OBJCOPY) -O binary $< $@

flash: $(BUILD)/$(TARGET).elf
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $(BUILD)/$(TARGET).elf verify reset exit"

clean:
	rm -f $(BUILD)/*.o $(BUILD)/*.elf $(BUILD)/*.hex $(BUILD)/*.bin $(BUILD)/*.map $(BUILD)/*.d

-include $(BUILD)/*.d

.PHONY: all flash clean
