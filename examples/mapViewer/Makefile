PATH := $(DEVKITARM)/bin:$(PATH)

# --- Project details -------------------------------------------------

PROJ    := mapViewer
TITLE   := $(PROJ)

GAMEOBJS   := main.o map/loadMap.o map/loadMapFromCode.o map/loadMapFromROM.o shiftMap.o
ASSETSOBJS := map.o
LIBOBJS    := gbfs/libgbfs.o

GAMEOBJS   := $(addprefix source/mapViewer/,$(GAMEOBJS))
ASSETSOBJS := $(addprefix source/map/,$(ASSETSOBJS))
LIBOBJS    := $(addprefix source/gbaLib/,$(LIBOBJS))

OBJS	:= $(GAMEOBJS) $(ASSETSOBJS) $(LIBOBJS)

# --- boot type (MB=0 : normal. MB=1 : multiboot) ---

MB = 0

ifeq ($(MB),1)

TARGET	:= $(PROJ).mb
SPECS	:= -specs=gba_mb.specs

else

TARGET	:= $(PROJ)
SPECS	:= -specs=gba.specs

endif

# --- Compiling -------------------------------------------------------

CROSS	?= arm-none-eabi-
AS		:= $(CROSS)as
CC		:= $(CROSS)gcc
LD		:= $(CROSS)gcc
OBJCOPY	:= $(CROSS)objcopy

ARCH	:= -mthumb-interwork -mthumb

ASFLAGS	:= -mthumb-interwork
CFLAGS	:= $(ARCH) -O2 -Wall -fno-strict-aliasing
LDFLAGS	:= $(ARCH) $(SPECS)

.PHONY : build clean

# --- Build -----------------------------------------------------------

build : $(TARGET).gba

play: build
	vba $(TARGET).gba

append: $(TARGET).gba
	./gbfs/gbfs map.gbfs map.bin
	./gbfs/padbin 256 $<
	cat $< map.gbfs > $(TARGET)_append.gba

$(TARGET).gba : $(TARGET).elf
	$(OBJCOPY) -v -O binary $< $@
	-@gbafix $@ -t$(TITLE)

$(TARGET).elf : $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

$(OBJS) : %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Clean -----------------------------------------------------------

clean :
	@rm -fv *.gba
	@rm -fv *.elf
	@rm -fv *.gbfs
	@rm -rf $(OBJS)

#EOF
