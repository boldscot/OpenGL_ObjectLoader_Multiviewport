/*
 * world.h
 *
 *  Created on: 12 Dec 2017
 *      Author: bold-_000
 */

#pragma once
#include <string>
#include "model.h"

#define theWorld World::GetInstance()

class World {
  public:
    static World& GetInstance();

    void loadModel (std::string modelName);
    void setCmdlineParams(int*argc, char **argv);
    void initialize(int width, int height, std::string name);
    void start();

    void render();
    void keyPress(unsigned char ch);

  private:
    static World* s_World;

    int   *argc;
    char **argv;
    Model theModel;
};
