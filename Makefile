ifeq ($(OS), Windows_NT)
	out = Connect4.exe
else 
	out = Connect4.out
endif
all: src/Game.c src/main.c src/InputManager.c src/OutputManager.c src/Strategies.c src/Utils.c src/Types.c
	gcc -o $(out) src/Game.c src/main.c src/InputManager.c src/OutputManager.c src/Strategies.c src/Utils.c src/Types.c 