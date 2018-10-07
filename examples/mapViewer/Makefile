PATH := $(DEVKITARM)/bin:$(PATH)

#  Project settings

NAME := mapViewer
SOURCE_DIR := source/
SPECS := -specs=gba.specs

MAP := map

# Compilation settings

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

# Build commands

SOURCES := $(shell find $(SOURCE_DIR) -name '*.c')
OBJECTS := $(SOURCES:%.c=%.o)

build : $(NAME).gba

append: $(NAME).gba
	./gbfs/gbfs $(MAP).gbfs $(MAP).bin
	./gbfs/padbin 256 $<
	cat $< $(MAP).gbfs > $(NAME)_append.gba

$(NAME).gba : $(NAME).elf
	$(OBJCOPY) -v -O binary $< $@
	-@gbafix $@ -t$(NAME)

$(NAME).elf : $(OBJECTS)
	$(LD) $^ $(LDFLAGS) -o $@

$(OBJECTS) : %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cleanup settings

clean :
	@rm -fv *.gba
	@rm -fv *.elf
	@rm -fv *.gbfs
	@rm -rf $(OBJS)

#EOF
