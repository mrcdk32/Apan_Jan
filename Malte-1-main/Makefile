CC := g++
FLAGS := -std=c++17
LIB := -L${SFML_ROOT}/lib -I${SFML_ROOT}/include -lsfml-window -lsfml-graphics -lsfml-system
run: game
	./game

all: src/Game_State.cc src/Game.cc src/Menu_State.cc src/main.cc src/Pause_State.cc src/Object.cc src/State.cc src/End_State.cc src/Manager.cc src/level.cc includes/constants.h  src/Player.cc src/Barrel.cc src/Gorilla.cc
	$(CC) $(FLAGS) src/Game_State.cc src/Game.cc src/Menu_State.cc src/main.cc src/Pause_State.cc src/Object.cc src/State.cc src/End_State.cc src/Manager.cc src/level.cc src/Player.cc  src/Barrel.cc src/Gorilla.cc -o game $(LIB)

# make sure that 'clean' is not run accidentally
.PHONY: clean

clean:
	rm start v1 v2 v3 v4 v5 v6 v7 v8 v9
