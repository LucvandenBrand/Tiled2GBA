#  Project settings

NAME := gbfs
SOURCE_DIR := src/

# Compilation settings

CC		:= gcc
LD		:= gcc

.PHONY : build clean

# Build commands

SOURCES := $(shell find $(SOURCE_DIR) -name '*.c')
OBJECTS := $(SOURCES:%.c=%.o)

build : $(NAME)

$(NAME) : $(OBJECTS)
	$(LD) $^ -o $@

$(OBJECTS) : %.o : %.c
	$(CC) -c $< -o $@

# Cleanup settings

clean :
	@rm -fv $(NAME)
	@rm -rf $(OBJECTS)

#EOF
