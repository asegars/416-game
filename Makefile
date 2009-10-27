# Compiler flags
SDL_LIB = `sdl-config --libs` -lSDL_ttf -lSDL_image
CFLAGS = `sdl-config --cflags` -W -Wall -ggdb -O0

# The name of the executable to make.
EXEC_NAME = run

all:
	g++ $(CFLAGS) $(SDL_LIB) -o $(EXEC_NAME) src/*.cpp
	
clean:
	rm -f $(EXEC_NAME)
	rm -f src/*~
