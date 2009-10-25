# Change the following values to suit your system.

CFLAGS=`sdl-config --cflags` -W -Wall -ggdb -O0
SDL_LIB=`sdl-config --libs` -lSDL_ttf -lSDL_image
CCC=g++

OBJECTS = manager.o sprite.o frame.o world.o player.o

run: main.o $(OBJECTS)
	$(CCC) $(CFLAGS) main.cpp -o run $(OBJECTS) $(SDL_LIB)

main.o: main.cpp manager.h
	$(CCC) $(CFLAGS) -c main.cpp

manager.o: manager.cpp manager.h sprite.h player.h fireball.h
	$(CCC) $(CFLAGS) -c manager.cpp

player.o: player.cpp player.h frame.h viewport.h
	$(CCC) $(CFLAGS) -c player.cpp

world.o: world.cpp world.h frame.h viewport.h player.h
	$(CCC) $(CFLAGS) -c world.cpp

sprite.o: sprite.cpp sprite.h frame.h drawable.h
	$(CCC) $(CFLAGS) -c sprite.cpp

frame.o: frame.cpp frame.h 
	$(CCC) $(CFLAGS) -c frame.cpp

clean:
	rm -f run *.o
	rm -f *~
