CFLAGS=`sdl-config --cflags` -W -Wall -ggdb -O0
SDL_LIB=`sdl-config --libs` -lSDL_ttf -lSDL_image
CCC=g++

OBJECTS = manager.o player.o enemy.o sprite.o frame.o world.o viewport.o

run: main.o $(OBJECTS)
	$(CCC) $(CFLAGS) main.cpp -o run $(OBJECTS) $(SDL_LIB)

main.o: main.cpp manager.h
	$(CCC) $(CFLAGS) -c main.cpp

manager.o: manager.cpp manager.h sprite.h player.h enemy.h
	$(CCC) $(CFLAGS) -c manager.cpp

player.o: player.cpp player.h frame.h viewport.h sprite.h
	$(CCC) $(CFLAGS) -c player.cpp

enemy.o: enemy.cpp enemy.h frame.h viewport.h sprite.h
	$(CCC) $(CFLAGS) -c enemy.cpp

sprite.o: sprite.cpp sprite.h frame.h drawable.h
	$(CCC) $(CFLAGS) -c sprite.cpp

frame.o: frame.cpp frame.h 
	$(CCC) $(CFLAGS) -c frame.cpp

world.o: world.cpp world.h frame.h viewport.h
	$(CCC) $(CFLAGS) -c world.cpp

viewport.o: viewport.cpp viewport.h sprite.h
	$(CCC) $(CFLAGS) -c viewport.cpp

clean:
	rm -f run *.o
	rm -f *~
