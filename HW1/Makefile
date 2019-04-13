## General Flags
MCU = atmega128
CC = avr-gcc
CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)
F_CPU  = 11059200

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -DF_CPU=$(F_CPU)UL
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -Os
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
# CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += -Wl,-u,vfprintf  -Wl,-u,vfscanf
# map file to debug
# LDFLAGS += -Wl,-Map=$*.map

## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature
HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings

## Libraries
LIBS = -lm -lprintf_flt -lscanf_flt

## Objects that must be built in order to link
# 把要加入編譯的.c檔目錄加到 LIBSRC 中
# Ex : LIBSRC += $(wildcard lib/*.c) (引用lib資料夾中所有c file)
# Ex : LIBSRC += HMI/ASA_Lib_HMI.c (引用HMI資料夾中的 "ASA_Lib_HMI.c")
# LIBSRC += lib/ASA_Lib_M128.c
# LIBSRC += LIB/asa_lib_m128_spi.c
LIBSRC += $(wildcard /*.c)
LIBSRC += $(wildcard LIB/*.c)
LIBOBJ = $(patsubst %.c,%.o,$(LIBSRC))

## Objects explicitly added by the user
# 把要連結的的.o檔加到 LINKONLYOBJECTS 中
# Ex : LINKONLYOBJECTS = ASA_lib.o (連結與Makefile同目錄的 "ASA_lib.o")
LINKONLYOBJECTS = ASA_lib.o

## Build
help:
	@echo "use \"make {filename}.a\" to complie .c to .hex in dir ./hex"

##Link
%.elf: %.o $(LIBOBJ)
	 $(CC) $(LDFLAGS) $< $(LIBOBJ) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $@

%.hex: %.elf
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.a: %.elf %.hex
	@echo
	@avr-size -C --mcu=${MCU} $<
	@-mkdir -p hex
	@-mv $*.hex hex/
	@-rm -rf $(OBJECTS) $*.map $*.o $<

%.eep: %.elf
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: %.elf
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) *.elf *.hex *.map ./hex/*
