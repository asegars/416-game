#include "manager.h"

Viewport* Viewport::instance = NULL;

int main(int, char*[]) {
   try {
      Manager game_manager;
      game_manager.play();
   }
   catch (const std::string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
/*
 * main.cpp
 *
 *  Created on: Oct 6, 2009

#include <string>
#include <iostream>
#include "terrain/MapReader.h"

#include "Manager.h"

Manager* Manager::instance = new Manager();

int main(int argc, char* argv[]) {
	std::string mapName;
	if (argc < 2) {
		mapName = "level1.map";
	}
	else {
		mapName = argv[1];
	}

	try {
		Manager* manager = Manager::getInstance();
		std::cout << "[Loading map...";
		manager->setMap(MapReader::readMap("maps/" + mapName));
		std::cout << "done]" << std::endl;
		manager->play();

		delete manager;
	} catch (std::string e) {
		std::cerr << "Exception thrown: " + e << std::endl;
	}
>>>>>>> 9e63ba3c144d7cbf7c8139fd063f11e33a9e535f:src/main.cpp
} */
