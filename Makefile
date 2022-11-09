all: src/Game.c src/main.c src/InputManager.c src/OutputManager.c src/Strategies.c
	gcc -o Connect4.out src/Game.c src/main.c src/InputManager.c src/OutputManager.c src/Strategies.c
