/*
 * world.cpp
 *
 *  Created on: 12 Dec 2017
 *      Author: bold-_000
 */

#include "world.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "freeglut.h"
#include "vector3.h"
#include "color.h"
#include <math.h>
#include <fstream>
#include <iostream>
using namespace std;

World* World::s_World = NULL;
//timer controller
bool isTimerOn= false;

// Struct to hold rotations and movements for view ports
struct Camera {
	// Camera counters
	static int camCounter;
	int camNum;
	// Rotation and translate
	float angX; float angY; float angZ;
	float posX; float posY; float posZ;
	// Active cam and move mode
	bool isActive;
	bool isRotate;

	Camera() {
		camNum = ++camCounter;
		angX=angY=angZ=0.0f;
		posX=posZ=posY=0.0f;
		isRotate =isActive= false;
	}

	void rotate() {
		glRotatef(angX, 1.0f, 0.0, 0.0);
		glRotatef(angY, 0.0, 1.0f, 0.0);
		glRotatef(angZ, 0.0, 0.0, 1.0f);
	}

	void move() {
		glTranslatef(posX, posY-0.5, posZ);
	}

	void reset() {
		angX=angY=angZ=0.0f;
		posX=posZ=posY=0.0f;
	}
} view_One, view_Two, view_Three, view_Four;

//Store reference to  Active camera
Camera *activeCam= &view_One;
//init camCounter
int Camera::camCounter = 0;

//Function to change the active camera
Camera* changeCam(Camera &cam) {
	activeCam->isActive=false;
	cam.isActive=true;
	std::cout << cam.camNum << std::endl;
	return &cam;
}

void reset() {
	view_One.reset();
	view_Two.reset();
	view_Three.reset();
	view_Four.reset();
	isTimerOn = false;
}

void timerFunction(int value) {
	if (isTimerOn) {
		//view one
		view_One.angX+=1;
		view_One.angY+=3;
		//view two
		view_Two.angY+=2;
		view_Two.angZ+=2;
		//view three
		view_Three.angY+=2;
		view_Three.angZ+=2;
		//view four
		view_Four.angX-=3;
		view_Four.angZ-=1;
		glutPostRedisplay();
	}
	glutTimerFunc(40, timerFunction, 1);
}

void World::loadModel (std::string modelName) {
	ifstream inStream;
	inStream.open(modelName.c_str(), ios::in);
	if (!inStream.fail()) {
		if (modelName=="src/knight.obj")knightModel.load(inStream);
		else if (modelName=="src/cube.obj")cubeModel.load(inStream);
		else if (modelName=="src/pawn.obj")pawnModel.load(inStream);
	}
	inStream.close();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h); //set the view port to the current window specifications
	glMatrixMode ( GL_PROJECTION); //set the matrix to projection
	glLoadIdentity();
	gluPerspective(60, (GLfloat) w / (GLfloat) h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, ,depth)
	glMatrixMode ( GL_MODELVIEW); //set the matrix back to model
}

void renderScene(void){
	World::GetInstance().render();
}

void keyboard(unsigned char key, int x, int y) {
	World::GetInstance().keyPress(key);
}

World& World::GetInstance(){
	if (s_World == NULL) {
		s_World = new World();
	}
	return *s_World;
}

void World::setCmdlineParams(int*argc, char **argv) {
	this->argc = argc;
	this->argv = argv;
}

void World::render() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Move camera back to bring model into view
	Vector3(0,0,-3).translate();

	//Main viewport
	glPushMatrix();
		glViewport(0, 0, (GLsizei) glutGet(GLUT_WINDOW_WIDTH), (GLsizei) glutGet(GLUT_WINDOW_HEIGHT));
		// Change line width and colour
		glColor3f(1.0f, 0, 0);
		glLineWidth(3);
			glBegin(GL_LINES);
				glVertex3f(0.0f, -100.0f, 0.0f);
				glVertex3f(0.0f, 100.0f, 0.0f);
				glVertex3f(-100.0f, 0.0f, 0.0f);
				glVertex3f(100.0f, 0.0f, 0.0f);
			glEnd();
	glPopMatrix();

	// Change line width and colour
	glLineWidth(1);
	glColor3f(0, 1.0f, 0);

	//Viewport 1
	glPushMatrix();
		view_One.move();
		view_One.rotate();
		glViewport(0.0f, (GLsizei) glutGet(GLUT_WINDOW_HEIGHT)/2,
				(GLsizei) glutGet(GLUT_WINDOW_WIDTH)/2, (GLsizei) glutGet(GLUT_WINDOW_HEIGHT)/2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		pawnModel.render();
	glPopMatrix();

	//Viewport 2
	glPushMatrix();
		view_Two.move();
		view_Two.rotate();
		glViewport((GLsizei) glutGet(GLUT_WINDOW_WIDTH)/2, (GLsizei) glutGet(GLUT_WINDOW_HEIGHT)/2,
				(GLsizei) glutGet(GLUT_WINDOW_WIDTH)/2, (GLsizei) glutGet(GLUT_WINDOW_HEIGHT)/2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		cubeModel.render();
	glPopMatrix();

	//Viewport 3
	glPushMatrix();
		view_Three.move();
		view_Three.rotate();
		glViewport(0, 0, (GLsizei) glutGet(GLUT_WINDOW_WIDTH)/2, (GLsizei) glutGet(GLUT_WINDOW_HEIGHT)/2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		knightModel.render();
	glPopMatrix();

	glPointSize(2.0f);
	//Viewport 4
	glPushMatrix();
		view_Four.move();
		view_Four.rotate();
		glViewport((GLsizei) glutGet(GLUT_WINDOW_WIDTH)/2, 0,
				(GLsizei) glutGet(GLUT_WINDOW_WIDTH)/2, (GLsizei) glutGet(GLUT_WINDOW_HEIGHT)/2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		knightModel.render();
	glPopMatrix();

	glutSwapBuffers();
}

void World::keyPress(unsigned char ch) {
	if (ch == '1' && !view_One.isActive) activeCam=changeCam(view_One);
	if (ch == '2' && !view_Two.isActive) activeCam=changeCam(view_Two);
	if (ch == '3' && !view_Three.isActive) activeCam=changeCam(view_Three);
	if (ch == '4' && !view_Four.isActive) activeCam=changeCam(view_Four);
	if (ch == 'm' || ch == 'M') activeCam->isRotate= !activeCam->isRotate;
	if (ch == 'z' || ch == 'Z') activeCam->posZ+=0.1;
	if (ch == 'x' || ch == 'X') activeCam->posZ-=0.1;
	if (ch == 't' || ch == 'T') isTimerOn = !isTimerOn;
	if (ch == 'r' || ch == 'R') reset();
	glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		if (activeCam->isRotate) activeCam->angX-=5.0f;
		else activeCam->posY-=0.1f;
	}
	if (key == GLUT_KEY_DOWN) {
		if (activeCam->isRotate) activeCam->angX+=5.0f;
		else activeCam->posY+=0.1f;
	}
	if (key == GLUT_KEY_LEFT) {
		if (activeCam->isRotate) activeCam->angY-=5.0f;
		else activeCam->posX-=0.1f;
	}
	if (key == GLUT_KEY_RIGHT) {
		if (activeCam->isRotate) activeCam->angY+=5.0f;
		else activeCam->posX+=0.1f;
	}
	glutPostRedisplay();
}


void World::initialize(int width, int height, std::string name) {
	//set 1st view port to active window
	activeCam->isActive=true;

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow(name.c_str());

	Color::Black.renderClear();
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT,GL_LINE);
	glPolygonMode(GL_BACK,GL_LINE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 1, 1.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glTranslatef(0.0f, 0.0f, -200.0f);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	glutReshapeFunc(reshape);
	glutDisplayFunc(renderScene);
	glutTimerFunc(40, timerFunction, 1);
}

void World::start() {
	glutMainLoop();
}



