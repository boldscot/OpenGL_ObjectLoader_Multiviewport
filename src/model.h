/*
 * model.h
 *
 *  Created on: 12 Dec 2017
 *      Author: bold-_000
 */

#include <map>
#include <istream>
#include <string>
#include "ModelObject.h"

typedef std::map <std::string, ModelObject>  ModelMap;
typedef ModelMap::iterator ModelMapIterator;

struct Model {
	ModelMap  modelObjects;

	Model();
	bool load(std::istream &is);
	void render();
};
