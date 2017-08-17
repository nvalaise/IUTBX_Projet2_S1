#LDFLAGS=-F/Library/Frameworks -framework SDL2 -framework Cocoa -framework SDL2_mixer -framework SDL2_ttf -I/System/Library/Frameworks/OpenGL.framework/Headers -framework OpenGL
#CFLAGS=-g -O2 -Wall -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_mixer.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers -I/System/Library/Frameworks/OpenGL.framework/Headers
CFLAGS=-g -Wall `sdl-config --cflags` -lSDL -lSDLmain -lSDL_image -lSDL_mixer -lSDL_ttf
LDFLAGS=-g -Wall `sdl-config --cflags --libs` -lSDL -lSDLmain -lSDL_image -lSDL_mixer -lSDL_ttf


all: treasure

treasure: gestion.c joueur.c main.c piece.c plateau.c
	g++ $^ -o $@ ${CFLAGS}

clean:
	rm treasure *.o *~
