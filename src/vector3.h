/*
 * vector3.h
 *
 *  Created on: 12 Dec 2017
 *      Author: bold-_000
 */
#pragma once
#include <istream>

struct Vector3 {
  float X;
  float Y;
  float Z;

  static Vector3 UnitX;
  static Vector3 UnitY;
  static Vector3 UnitZ;

  Vector3(float x, float y, float z);
  Vector3(float value);
  Vector3();
  Vector3(std::istream& is);

  void translate();
  void rotate (float angle);

  void render();
};
