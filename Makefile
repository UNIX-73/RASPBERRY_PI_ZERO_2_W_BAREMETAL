SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Buscar archivos .c y .cpp de forma recursiva
SRCS_C = $(shell find $(SRC_DIR) -type f -name "*.c")
SRCS_CPP = $(shell find $(SRC_DIR) -type f -name "*.cpp")

# Buscar archivos de cabecera para incluirlos en los flags de compilación
HEADERS = $(shell find $(SRC_DIR) $(INCLUDE_DIR) -type f \( -name "*.h" -o -name "*.hpp" \))

OBJS_C = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS_C))
OBJS_CPP = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS_CPP))
OBJS = $(OBJS_C) $(OBJS_CPP)

CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles $(addprefix -I, $(SRC_DIR) $(INCLUDE_DIR))
CPPFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles -fno-rtti -fno-exceptions $(addprefix -I, $(SRC_DIR) $(INCLUDE_DIR))

CC = aarch64-none-elf-gcc
CPP = aarch64-none-elf-g++
LD = aarch64-none-elf-ld
OBJCOPY = aarch64-none-elf-objcopy

all: $(BIN_DIR)/kernel8.img

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Crear los subdirectorios de obj si es necesario antes de compilar
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)/%.d
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)/%.d
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/%.d:
	mkdir -p $(dir $@)

start.o: $(SRC_DIR)/start.S | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/start.S -o $(OBJ_DIR)/start.o

$(BIN_DIR)/kernel8.img: start.o $(OBJS)
	$(LD) -nostdlib $(OBJ_DIR)/start.o $(OBJS) -T linker.ld -o $(BIN_DIR)/kernel8.elf
	$(OBJCOPY) -O binary $(BIN_DIR)/kernel8.elf $(BIN_DIR)/kernel8.img

clean:
	rm -rf $(BUILD_DIR) kernel8.elf
