/*
 * face.h
 *
 *  Created on: 12 Dec 2017
 *      Author: bold-_000
 */

#include "vector3.h"
#include <vector>

struct Face {
  int vertices[3];
  int textures[3];

  Face(std::istream &is);
  void render(std::vector <Vector3> &defaultTable);
};

