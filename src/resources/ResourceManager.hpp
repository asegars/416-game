/*
 * ResourceManager.cpp
 *
 *  Created on: Nov 9, 2009
 *      Author: luke
 */

#include <string>
#include <map>
#include "ResourceManager.h"

template <class T>
ResourceManager<T>::ResourceManager() {

}

template <class T>
ResourceManager<T>::~ResourceManager() {
	typename std::map<std::string, T>::const_iterator iter = resources.begin();
	
	while (iter != resources.end()) {
		delete iter->second;
	}
}

template <class T>
T ResourceManager<T>::load(std::string resName) {
	T newResource;
	// If the key was in the map, return it
	if (resources.find(resName) != std::map<std::string, T>::end()) {
		newResource = resources[resName];
	}
	// Otherwise, we need to load it and store it in the map
	else {
		newResource = read(resName);
		resources[resName] = newResource;
	}
	
	return newResource;
}