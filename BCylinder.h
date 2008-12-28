#ifndef __BCYLINDER_H
#define __BCYLINDER_H

#include "BChain.h"

class BCylinder : public BChain {
 public:
  BCylinder(float radius);
  int AddNextPoint(float phi, float z);
  float *field_polar(float radius, float phi, float z);

  // Members:
  float last_phi;
  float last_z;
  float radius;
  float max_phi_step;
};

#endif
