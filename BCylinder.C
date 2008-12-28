#include "BCylinder.h"

#include <math.h>



BCylinder::BCylinder(float radius) {
  this->radius = radius;
}

int BCylinder::AddNextPoint(float phi, float z) {
  return BChain::AddNextPoint(radius * cos(phi), radius * sin(phi), z);
}

float *BCylinder::field_polar(float radius, float phi, float z) {
  return BChain::field(radius * cos(phi), radius * sin(phi), z);
}

