SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles -I$(SRC_DIR)

CC = aarch64-none-elf-gcc
LD = aarch64-none-elf-ld
OBJCOPY = aarch64-none-elf-objcopy
QEMU = qemu-system-aarch64

all: $(BIN_DIR)/kernel8.img

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

start.o: $(SRC_DIR)/start.S | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/start.S -o $(OBJ_DIR)/start.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/kernel8.img: start.o $(OBJS)
	$(LD) -nostdlib $(OBJ_DIR)/start.o $(OBJS) -T linker.ld -o $(BIN_DIR)/kernel8.elf
	$(OBJCOPY) -O binary $(BIN_DIR)/kernel8.elf $(BIN_DIR)/kernel8.img

clean:
	rm -rf $(BUILD_DIR) kernel8.elf

#run: $(BIN_DIR)/kernel8.img
#	$(QEMU) -M raspi3b -kernel $(BIN_DIR)/kernel8.img -d in_asm
