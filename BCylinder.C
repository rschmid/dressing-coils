#include "BCylinder.h"

#include <math.h>

BCylinder::BCylinder(float radius) {
  this->radius = radius;
  this->max_phi_step = .2;
}

int BCylinder::AddNextPoint(float phi, float z) {
  int points = 0;
  float temp = -1.;
  if (p2 || p1) {
    temp = phi - last_phi;
    if (temp < 0) temp = -temp;
    while (temp > 3.14159) temp -= 3.14159;
  }
  if (temp > max_phi_step) {
    points = AddNextPoint((last_phi + phi)/2.0, (last_z + z)/2.0);
    points += AddNextPoint(phi, z);
    return points;
  }
  points = BChain::AddNextPoint(radius * cos(phi), radius * sin(phi), z);
  last_phi = phi;
  last_z = z;
  return points;
}

int BCylinder::AddNextPoint(float *coords) {
  if (coords) {
    return AddNextPoint(coords[0], coords[1]);
  }
  return -1;
}

float *BCylinder::field_polar(float radius, float phi, float z) {
  return BChain::field(radius * cos(phi), radius * sin(phi), z);
}
