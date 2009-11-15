# Change the following values to suit your system.

CFLAGS=`sdl-config --cflags` -W -Wall -ggdb -O0 -pg
SDL_LIB=`sdl-config --libs` -lSDL_ttf -lSDL_image -lSDL_mixer
CCC=g++

EXECUTABLE = run

CPP_FILES = src/*.cpp src/*/*.cpp

all:
	$(CCC) $(CFLAGS) $(CPP_FILES) $(SDL_LIB) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
	rm -f src/*~
