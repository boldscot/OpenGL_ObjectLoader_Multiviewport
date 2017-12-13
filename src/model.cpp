/*
 * model.cpp
 *
 *  Created on: 12 Dec 2017
 *      Author: bold-_000
 */

#include "model.h"
#include <iostream>

Model::Model()
{
}

bool Model::load(std::istream &is) {
	std::string indicator;
	while (is >> indicator) {
		std::cout << "-----model> " << indicator << " <model-----" << std::endl;
		if (indicator == "#") {
			std::string buf;
			getline(is, buf);
		} else if (indicator == "g") {
			ModelObject a(is);
			if (modelObjects.find(a.name) == modelObjects.end()) {
				modelObjects[a.name] = a;
			}
		}
	}
	return true;
}

void Model::render() {
	ModelMapIterator defaultIter = modelObjects.begin();

	if (defaultIter != modelObjects.end()) {
		ModelObject defaultObject(defaultIter->second);

		for (ModelMapIterator iter = modelObjects.begin(); iter != modelObjects.end(); iter++) {
			iter->second.render(defaultObject.vertices);
		}
	}
}

