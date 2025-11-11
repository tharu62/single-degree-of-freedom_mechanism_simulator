# Variables
CC = gcc
CFLAGS = -Wall -O2
SRC_DIR = src
BUILD_DIR = build
INCL_DIR = include

ifeq ($(OS),Windows_NT)
	RAYLIB_INCL_DIR = raylib/include
	RAYLIB_LIB_DIR = raylib/lib
else
	RAYLIB_INCL_DIR = raylib_linux/include
	RAYLIB_LIB_DIR = raylib_linux/lib
endif

# Find source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Convert to object paths
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Include and library path flags
INCLUDE_FLAGS = -I$(INCL_DIR) -I$(RAYLIB_INCL_DIR)
LIBRARY_PATH_FLAGS = -L$(RAYLIB_LIB_DIR)

# Libraries to link
ifeq ($(OS),Windows_NT)
	LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
else
	LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Default target
all: sim

# Link executable
sim: $(OBJS)
ifeq ($(OS),Windows_NT)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(LIBRARY_PATH_FLAGS) -o $@ $^ $(LIBS)
else
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(LIBRARY_PATH_FLAGS) -Wl,-rpath,$(RAYLIB_LIB_DIR) -o $@ $^ $(LIBS)
endif

# Compile each .c to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run:
ifeq ($(OS),Windows_NT)
	@sim.exe
else
	@./sim 
endif	

# Clean target
clean:
ifeq ($(OS),Windows_NT)
	@echo Cleaning Windows build files...
	@del /Q /F $(BUILD_DIR)\*.o 2>nul || echo No files to delete.
	@del /Q /F sim.exe 2>nul || echo No files to delete.
else
	@echo Cleaning Linux build files...
	@rm -rf $(BUILD_DIR)/*.o
	@rm -f sim 2>/dev/null || echo No files to delete.
endif
