CC = gcc

CFLAGS = -Wall

build: bytereader sdl2

bytereader: src/bytereader.c
	$(CC) $(CFLAGS) -o dist/bytereader src/bytereader.c

sdl2: src/sdl2-test.c
	$(CC) $(CFLAGS) -lSDL2 -o dist/sdl2test src/sdl2test.c
