/*
 * ResourceManager.h
 *
 *  Created on: Nov 9, 2009
 *
 *  This class acts as a base class for all resource manager derivates (sound, graphics,
 *  fonts, etc).  It allows the developer to call load() to retrieve a resource and will cache
 *  that resource to reduce the load time of later calls.  In addition, all resources
 *  are freed when the manager exits.
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <string>
#include <map>

template <class T>
class ResourceManager {
public:
	// TODO: Is there a way to encapsulate the destruction of objects
	//   so that it doesn't have to be customized for each type of manager?
	virtual ~ResourceManager();


	T load(std::string resName);
protected:
	ResourceManager();
	/**
	 * Pure virtual function that should be written to describe how the managed
	 * resources is loaded.
	 *
	 * The parameter resName will not have the baseDir appended to it yet --
	 * it will be identical to the form passed in to the load() method.
	 */
	virtual T read(std::string resName) = 0;
	virtual void clear(T resource);

	std::string baseDir;
	std::map<std::string, T> resources;
};

#include "ResourceManager.hpp"

#endif /* RESOURCEMANAGER_H_ */
