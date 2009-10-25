/*
 * main.cpp
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */
#include <string>
#include <iostream>

#include "Manager.h"

Manager* Manager::instance = new Manager();

int main() {
	try {
		Manager* manager = Manager::getInstance();
		manager->play();

		delete manager;
	} catch (std::string e) {
		std::cerr << "Exception thrown: " + e << std::endl;
	}
}
