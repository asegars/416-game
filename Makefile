# Change the following values to suit your system.

CFLAGS=`sdl-config --cflags` -W -Wall -ggdb -O3 -pg
SDL_LIB=`sdl-config --libs` -lSDL_ttf -lSDL_image -lSDL_mixer
CCC=g++

EXECUTABLE = run

CPP_FILES = src/*.cpp src/*/*.cpp

all:
	rm -rf build/
	rm -rf web/download/
	mkdir build
	mkdir web/download/
	zip -r latest.zip *
	cp latest.zip web/download/latest.zip
	mv latest.zip build/latest.zip
	$(CCC) $(CFLAGS) $(CPP_FILES) $(SDL_LIB) -o $(EXECUTABLE)
	

clean:
	rm -f gmon.out
	rm -f $(EXECUTABLE)
	rm -f src/*~
	rm -f build/latest.zip
