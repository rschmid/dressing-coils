#include "BSegment.h"

float BSegment::_temp_field[3];

BSegment::BSegment() {
  _default_constructor();
}

BSegment::BSegment(BSegment *clone) {
  _default_constructor();
  if (clone->p1) {
    p1 = new float(3);
    p1[0] = clone->p1[0];
    p1[1] = clone->p1[1];
    p1[2] = clone->p1[2];
  }
  if (clone->p2) {
    p2 = new float(3);
    p2[0] = clone->p2[0];
    p2[1] = clone->p2[1];
    p2[2] = clone->p2[2];
  }
}

BSegment::~BSegment() {
  delete p1;
  delete p2;
}

void BSegment::_default_constructor() {
  p1 = 0;
  p2 = 0;
}

BSegment *BSegment::Clone() {
  BSegment *clone = new BSegment();
  return clone;
}

int BSegment::is_valid() {
  return (p1 && p2);
}

float *BSegment::field(float x, float y, float z) {
  float *temp = _temp_field;
  temp[0] = x;
  temp[1] = y;
  temp[2] = z;
  return temp ;
}
