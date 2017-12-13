/*
 * main.cpp
 *
 *  Created on: 12 Dec 2017
 *      Author: bold-_000
 */

#include "world.h"

int main(int argc, char* argv[]) {
  theWorld.setCmdlineParams(&argc, argv);
  theWorld.initialize(800,600, "First World");
  theWorld.loadModel("src/horse.obj");
  theWorld.start();
  return 0;
}


