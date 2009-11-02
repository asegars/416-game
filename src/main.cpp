/*
 * main.cpp
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */
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
		manager->setMap(MapReader::readMap("maps/" + mapName));
		std::cout << "[Map loaded]" << std::endl;
		manager->play();

		delete manager;
	} catch (std::string e) {
		std::cerr << "Exception thrown: " + e << std::endl;
	}
}
