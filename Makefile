# Compiler and Flags
CC = gcc
CFLAGS = -I include
LDFLAGS = -L lib/ -lraylib -lgdi32 -lwinmm

# Output file
OUT = game.exe
SRC = src/main.cc

# Default target
all: $(OUT)

# Compile the program
$(OUT): $(SRC)
	$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LDFLAGS)

# Clean compiled files
clean:
	del /f /q $(OUT)