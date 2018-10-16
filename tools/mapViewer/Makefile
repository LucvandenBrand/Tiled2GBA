PATH := $(DEVKITARM)/bin:$(PATH)

#  Project settings

NAME := mapViewer
SOURCE_DIR := src/
SPECS := -specs=gba.specs

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
	@rm -rf $(OBJECTS)

#EOF
