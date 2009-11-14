# Change the following values to suit your system.

CFLAGS=`sdl-config --cflags` -W -Wall -ggdb -O0
SDL_LIB=`sdl-config --libs` -lSDL_ttf -lSDL_image
CCC=g++

EXECUTABLE = run

CPP_FILES = src/*.cpp

all:
	$(CCC) $(CFLAGS) $(CPP_FILES) $(SDL_LIB) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
	rm -f src/*~
