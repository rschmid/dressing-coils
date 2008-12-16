#include "BCylinder.h"

#include <math.h>



BCylinder::BCylinder(float radius) {
  this->radius = radius;
  this->closed = 0;
  coil = new BCoil();
}

int BCylinder::AddNextPoint(float phi, float z) {
  if (closed) return 0;
  return coil->AddNextPoint(radius * cos(phi), radius * sin(phi), z);
}

float *BCylinder::field(float x, float y, float z) {
  return coil->field(x,y,z);
}

float *BCylinder::field_radius(float radius, float phi, float z) {
  return coil->field(radius * cos(phi), radius * sin(phi), z);
}

