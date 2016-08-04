MCU = atmega644p
F_CPU = 8000000
FORMAT = ihex
OBJDIR = .

DATE=$(shell date +%Y-%m-%d)
DESTDIR=a644CUL

#		../../clib/adcw.c                                    \
#		../../clib/cctemp.c                                  \

SRC = a644CUL.c                                            \
		../../clib/cc1100.c                                  \
		../../clib/cc1101_pllcheck.c                         \
		../../clib/clock.c                                   \
		../../clib/belfox.c                                  \
		../../clib/delay.c                                   \
		../../clib/display.c                                 \
		../../clib/stringfunc.c                              \
		../../clib/fncollection.c                            \
		../../clib/fband.c                                   \
		../../clib/ringbuffer.c                              \
		../../clib/fht.c                                     \
		../../clib/rf_send.c                                 \
		../../clib/rf_receive.c                              \
		../../clib/rf_receive_bucket.c                       \
		../../clib/rf_receive_tcm97001.c                     \
		../../clib/rf_receive_it.c                           \
		../../clib/rf_receive_tx3.c                          \
		../../clib/rf_receive_revolt.c                       \
		../../clib/rf_receive_esa.c                          \
		../../clib/rf_receive_hms.c                          \
		../../clib/rf_native.c                               \
		../../clib/lacrosse.c                                \
		../../clib/helper.c                                  \
		../../clib/rf_asksin.c                               \
		../../clib/rf_moritz.c                               \
		../../clib/rf_rwe.c                                  \
		../../clib/somfy_rts.c                               \
		../../clib/fastrf.c                                  \
		../../clib/intertechno.c                             \
		../../clib/kopp-fc.c                                 \
		../../clib/memory.c                                  \
		../../clib/stacking.c                                \
		../../clib/serial.c                                  \
		../../clib/ttydata.c                                 \
		../../clib/spi.c                                     \
		../../clib/rf_mbus.c                                 \
		../../clib/mbus/manchester.c                         \
		../../clib/mbus/3outof6.c                            \
		../../clib/mbus/mbus_packet.c                        \
		../../clib/mbus/crc.c                                \



OPT = s
DEBUG = dwarf-2
EXTRAINCDIRS = ../../clib
CSTANDARD = -std=gnu99
CDEFS  = -DF_CPU=$(F_CPU)UL

ADEFS = -DF_CPU=$(F_CPU)
CPPDEFS = -DF_CPU=$(F_CPU)UL

CFLAGS = -g$(DEBUG)
CFLAGS += $(CDEFS)
CFLAGS += -O$(OPT)
CFLAGS += -funsigned-char
CFLAGS += -funsigned-bitfields
CFLAGS += -ffunction-sections
CFLAGS += -fpack-struct
CFLAGS += -fshort-enums
CFLAGS += -finline-limit=20
CFLAGS += -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS  = -D$(TARGET)
#CFLAGS += -Wunreachable-code
CFLAGS += -Wa,-adhlns=$(<:%.c=$(OBJDIR)/%.lst)
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))
CFLAGS += $(CSTANDARD)
CFLAGS += -mcall-prologues
CFLAGS += -DF_CPU=$(F_CPU)UL


CPPFLAGS = -g$(DEBUG)
CPPFLAGS += $(CPPDEFS)
CPPFLAGS += -O$(OPT)
CPPFLAGS += -funsigned-char
CPPFLAGS += -funsigned-bitfields
CPPFLAGS += -fpack-struct
CPPFLAGS += -fshort-enums
CPPFLAGS += -fno-exceptions
CPPFLAGS += -Wall
CFLAGS += -Wundef
CPPFLAGS += -Wa,-adhlns=$(<:%.cpp=$(OBJDIR)/%.lst)
CPPFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))


ASFLAGS = $(ADEFS) -Wa,-adhlns=$(<:%.S=$(OBJDIR)/%.lst),-gstabs,--listing-cont-lines=100


PRINTF_LIB_MIN = -Wl,-u,vfprintf -lprintf_min
PRINTF_LIB_FLOAT = -Wl,-u,vfprintf -lprintf_flt
PRINTF_LIB = 
SCANF_LIB_MIN = -Wl,-u,vfscanf -lscanf_min
SCANF_LIB_FLOAT = -Wl,-u,vfscanf -lscanf_flt
SCANF_LIB = 
MATH_LIB = -lm
EXTRALIBDIRS = 
EXTMEMOPTS =


LDFLAGS = -Wl,-Map=$(TARGET).map,--cref
LDFLAGS += -Wl,--relax 
LDFLAGS += -Wl,--gc-sections
LDFLAGS += $(EXTMEMOPTS)
LDFLAGS += $(patsubst %,-L%,$(EXTRALIBDIRS))
LDFLAGS += $(PRINTF_LIB) $(SCANF_LIB) $(MATH_LIB)


SHELL = sh
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
AR = avr-ar rcs
NM = avr-nm
AVRDUDE = avrdude
REMOVE = rm -f
REMOVEDIR = rm -rf
COPY = cp
WINSHELL = cmd

MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- begin --------
MSG_END = --------  end  --------
MSG_SIZE_BEFORE = Size before: 
MSG_SIZE_AFTER = Size after:
MSG_COFF = Converting to AVR COFF:
MSG_EXTENDED_COFF = Converting to AVR Extended COFF:
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling C:
MSG_COMPILING_CPP = Compiling C++:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:
MSG_CREATING_LIBRARY = Creating library:




OBJ = $(SRC:%.c=$(OBJDIR)/%.o) $(CPPSRC:%.cpp=$(OBJDIR)/%.o) $(ASRC:%.S=$(OBJDIR)/%.o) 

LST = $(SRC:%.c=$(OBJDIR)/%.lst) $(CPPSRC:%.cpp=$(OBJDIR)/%.lst) $(ASRC:%.S=$(OBJDIR)/%.lst) 


GENDEPFLAGS = -MMD -MP -MF dep/$(@F).d


ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS) $(GENDEPFLAGS)
ALL_CPPFLAGS = -mmcu=$(MCU) -I. -x c++ $(CPPFLAGS) $(GENDEPFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)



all: 
	make TARGET=a644CUL868 mostly_clean build
	make TARGET=a644CUL433 mostly_clean build

build: elf hex eep lss sym


elf: $(TARGET).elf
hex: $(TARGET).hex
eep: $(TARGET).eep
lss: $(TARGET).lss
sym: $(TARGET).sym
LIBNAME=lib$(TARGET).a
lib: $(LIBNAME)



begin:
	@echo
	@echo $(MSG_BEGIN)

end:
	@echo $(MSG_END)
	@echo



COFFCONVERT = $(OBJCOPY) --debugging
COFFCONVERT += --change-section-address .data-0x800000
COFFCONVERT += --change-section-address .bss-0x800000
COFFCONVERT += --change-section-address .noinit-0x800000
COFFCONVERT += --change-section-address .eeprom-0x810000



coff: $(TARGET).elf
	@echo
	@echo $(MSG_COFF) $(TARGET).cof
	$(COFFCONVERT) -O coff-avr $< $(TARGET).cof


extcoff: $(TARGET).elf
	@echo
	@echo $(MSG_EXTENDED_COFF) $(TARGET).cof
	$(COFFCONVERT) -O coff-ext-avr $< $(TARGET).cof



%.hex: %.elf
	@echo $(MSG_FLASH) $@
	@$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

%.eep: %.elf
	@echo $(MSG_EEPROM) $@
	@-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 --no-change-warnings -O $(FORMAT) $< $@ || exit 0

%.lss: %.elf
	@echo $(MSG_EXTENDED_LISTING) $@
	@$(OBJDUMP) -h -z -S $< > $@

%.sym: %.elf
	@echo $(MSG_SYMBOL_TABLE) $@
	@$(NM) -n $< > $@



.SECONDARY : $(TARGET).a
.PRECIOUS : $(OBJ)
%.a: $(OBJ)
	@echo
	@echo $(MSG_CREATING_LIBRARY) $@
	$(AR) $@ $(OBJ)


.SECONDARY : $(TARGET).elf
.PRECIOUS : $(OBJ)
%.elf: $(OBJ)
	@echo $(MSG_LINKING) $@
	@$(CC) $(ALL_CFLAGS) $^ --output $@ $(LDFLAGS)


$(OBJDIR)/%.o : %.c
	@echo $(MSG_COMPILING) $<
	@$(CC) -c $(ALL_CFLAGS) $< -o $@ 


$(OBJDIR)/%.o : %.cpp
	@echo
	@echo $(MSG_COMPILING_CPP) $<
	$(CC) -c $(ALL_CPPFLAGS) $< -o $@ 


%.s : %.c
	$(CC) -S $(ALL_CFLAGS) $< -o $@


%.s : %.cpp
	$(CC) -S $(ALL_CPPFLAGS) $< -o $@


$(OBJDIR)/%.o : %.S
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c $(ALL_ASFLAGS) $< -o $@


%.i : %.c
	$(CC) -E -mmcu=$(MCU) -I. $(CFLAGS) $< -o $@ 

clean: clean_list clean_binary

clean_binary:
	@$(REMOVE) $(TARGET).hex

mostly_clean:
	@echo $(MSG_CLEANING)
	@$(REMOVE) $(TARGET).hex
	@$(REMOVE) $(TARGET).eep
	@$(REMOVE) $(TARGET).cof
	@$(REMOVE) $(TARGET).elf
	@$(REMOVE) $(TARGET).map
	@$(REMOVE) $(TARGET).sym
	@$(REMOVE) $(TARGET).lss
	@$(REMOVE) $(SRC:%.c=$(OBJDIR)/%.o)
	@$(REMOVE) $(SRC:%.c=$(OBJDIR)/%.lst)
	@$(REMOVE) $(SRC:.c=.s)
	@$(REMOVE) $(SRC:.c=.d)
	@$(REMOVE) $(SRC:.c=.i)

clean_list:
	@echo $(MSG_CLEANING)
	@$(REMOVE) *.eep
	@$(REMOVE) *.cof
	@$(REMOVE) *.elf
	@$(REMOVE) *.map
	@$(REMOVE) *.sym
	@$(REMOVE) *.lss
	@$(REMOVE) *.hex
	@$(REMOVE) $(SRC:%.c=$(OBJDIR)/%.o)
	@$(REMOVE) $(SRC:%.c=$(OBJDIR)/%.lst)
	@$(REMOVE) $(SRC:.c=.s)
	@$(REMOVE) $(SRC:.c=.d)
	@$(REMOVE) $(SRC:.c=.i)
	@$(REMOVEDIR) dep


$(shell mkdir $(OBJDIR) 2>/dev/null)


-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)


.PHONY : all begin  \
finish end sizebefore sizeafter gccversion  \
build elf hex eep lss sym coff extcoff      \
clean clean_list clean_binary program debug \
gdb-config
