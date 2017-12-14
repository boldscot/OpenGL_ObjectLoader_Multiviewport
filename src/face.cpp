/*
 * face.cpp
 *
 *  Created on: 12 Dec 2017
 *      Author: bold-_000
 */
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "freeglut.h"
#include "face.h"
#include <iostream>

Face::Face(std::istream &is) {
	char ch1;
	for (int i = 0; i <4; i++) {
		is >> vertices[i];
		is >> ch1;
		is >> textures[i];
		//std::cout << "VERTS = " << vertices[i] << std::endl;
		//std::cout << "CH1 = " << ch1 << std::endl;
		//std::cout << "TEXTS = " << textures[i] << std::endl;
	}
}

void Face::render(std::vector <Vector3> &defaultTable) {
	glBegin(GL_QUADS);
	for (int i=0; i<4; i++) {
		glVertex3f( defaultTable[vertices[i] - 1].X,
				defaultTable[vertices[i] - 1].Y,
				defaultTable[vertices[i] - 1].Z );
		//std::cout << defaultTable[vertices[i] - 1].X << " " << defaultTable[vertices[i] - 1].Y << " " << defaultTable[vertices[i] - 1].Z << std::endl;
	}
	glEnd();
}


