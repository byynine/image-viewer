CC = gcc

CFLAGS = -Wall

build: bytereader sdl2

bytereader: src/bytereader.c
	$(CC) $(CFLAGS) -o build/bytereader src/bytereader.c

sdl2: src/sdl2test.c
	$(CC) $(CFLAGS) -lSDL2 -o build/sdl2test src/sdl2test.c
