/*
 * modelObject.h
 *
 *  Created on: 12 Dec 2017
 *      Author: bold-_000
 */
#include "vector3.h"
#include <vector>
#include "face.h"

struct ModelObject {
  std::string name;
  std::vector<Face> faces;
  std::vector <Vector3> vertices;

  ModelObject();
  ModelObject(std::istream &is);
  void render(std::vector <Vector3> &defaultTable);
};
