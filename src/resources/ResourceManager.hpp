/*
 * ResourceManager.cpp
 *
 *  Created on: Nov 9, 2009
 *      Author: luke
 */

#include <iostream>
#include <string>
#include <map>
#include "ResourceManager.h"

template <class T>
ResourceManager<T>::ResourceManager() {

}

template <class T>
ResourceManager<T>::~ResourceManager() {
//	typename std::map<std::string, T>::const_iterator iter = resources.begin();
//
//	while (iter != resources.end()) {
//		clear(iter->second);
//	}
}

template <class T>
T ResourceManager<T>::load(std::string resName) {
	T newResource;
	// If the key was in the map, return it
	if (resources.find(resName) != resources.end()) {
		newResource = resources[resName];
	}
	// Otherwise, we need to load it and store it in the map
	else {
		try {
			newResource = read(resName);
			resources[resName] = newResource;
		}
		catch (std::string e) {
			std::cerr << "[Manager exception] " + e;
			exit(1);
		}
	}
	
	return newResource;
}

template <class T>
void ResourceManager<T>::clear(T resource) {
	std::cerr << "Warning: manager is clearing resource with generic clear() method" << std::endl;
	delete resource;
}
