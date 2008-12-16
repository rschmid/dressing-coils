#ifndef __BCYLINDER_H
#define __BCYLINDER_H

#include "BCoil.h"

class BCylinder {
 public:
  BCylinder(float radius);
  int AddNextPoint(float phi, float z);
  float *field(float x, float y, float z);
  float *field_radius(float radius, float phi, float z);

  // Members:
  BCoil *coil;
 private:
  float radius;
  int closed;
};

#endif
