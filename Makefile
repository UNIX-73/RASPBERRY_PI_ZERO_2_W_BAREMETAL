SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

SRCS_C = $(shell find $(SRC_DIR) -name '*.c')
SRCS_CPP = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS_C = $(SRCS_C:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_CPP = $(SRCS_CPP:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJS = $(OBJS_C) $(OBJS_CPP)

CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles -I$(SRC_DIR) -I$(INCLUDE_DIR)
CPPFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles -fno-rtti -fno-exceptions -I$(SRC_DIR) -I$(INCLUDE_DIR)

CC = aarch64-none-elf-gcc
CPP = aarch64-none-elf-g++
LD = aarch64-none-elf-ld
OBJCOPY = aarch64-none-elf-objcopy

all: $(BIN_DIR)/kernel8.img

$(OBJ_DIR) $(BIN_DIR):
    mkdir -p $(OBJ_DIR) $(BIN_DIR)

start.o: $(SRC_DIR)/start.S | $(OBJ_DIR)
    $(CC) $(CFLAGS) -c $(SRC_DIR)/start.S -o $(OBJ_DIR)/start.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
    $(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
    $(CPP) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/kernel8.img: $(OBJS) | $(BIN_DIR)
    $(LD) -T $(SRC_DIR)/linker.ld -o $(BIN_DIR)/kernel8.elf $(OBJS)
    $(OBJCOPY) -O binary $(BIN_DIR)/kernel8.elf $(BIN_DIR)/kernel8.img

clean:
    rm -rf $(BUILD_DIR)
