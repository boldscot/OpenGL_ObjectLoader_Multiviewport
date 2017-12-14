/*
 * modelObject.cpp
 *
 *  Created on: 12 Dec 2017
 *      Author: bold-_000
 */

#include "modelObject.h"
#include <iostream>

ModelObject::ModelObject()
{}

ModelObject::ModelObject(std::istream &is) {
	std::string indicator;
	is >> name;
	bool stillGroup=true;
	do {
		is >> indicator;
		//std::cout << "----------> " << indicator << " <------------" << std::endl;
		if (indicator == "v") {
			vertices.push_back(Vector3(is));
		} else if (indicator == "f") {
			faces.push_back(Face(is));
			//std::cout << "Faces size = " << faces.size() << std::endl;
		} else if (indicator == "g") {
			stillGroup = false;
		} else {
			std::string buf;
			getline(is, buf);
		}
	} while (!is.eof());
	is.putback(indicator[0]);
}

void ModelObject::render(std::vector <Vector3> &defaultTable) {
	//std::cout << " rendering " << name << " with " << faces.size()  << std::endl;
	for (unsigned int i = 0; i < faces.size(); i++) {
		faces[i].render(defaultTable);
	}
}



