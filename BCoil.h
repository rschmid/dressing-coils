#ifndef __BCOIL_H
#define __BCOIL_H

#include "BSegment.h"

class BCoil : public BSegment{

 public:
  BCoil();
  int AddNextPoint(const float *p);
  int AddNextPoint(float x, float y, float z);
  float *field(float *r);
  float *field(float x, float y, float z);
  int is_closed();

  BCoil *prev;
  BCoil *next;
};

#endif
