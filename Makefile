# Output file
SRC = src/main.cc src/ghost.cc src/pacman.cc src/game.cc src/pellet.cc src/scoreboard.cc src/sprite.cc src/wall.cc
OBJ = src/main.o src/ghost.o src/pacman.o src/game.o src/pellet.o src/scoreboard.o src/sprite.o src/wall.o

# Default target
all: game.exe

# Compile the program
game.exe: $(OBJ)
	g++ -o game.exe $(OBJ) -L lib/ -lraylib -lgdi32 -lwinmm

src/%.o: src/%.cc
	g++ -I include -c -o $@ $<

# Clean compiled files
clean:
	del /f /q game.exe