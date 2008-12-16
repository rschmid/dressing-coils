#include "BSegment.h"
#include "Vector.h"

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
  initialized = 0;
  p1 = 0;
  p2 = 0;
}

BSegment *BSegment::Clone() {
  BSegment *clone = new BSegment();
  return clone;
}

int BSegment::init() {
  initialized = 0;
  if (p1 && p2) {
    current_direction[0] = p2[0] - p1[0];
    current_direction[1] = p2[1] - p1[1];
    current_direction[2] = p2[2] - p1[2];
    length = Vector::Norm(current_direction);
    Vector::Normalize(current_direction);
    initialized = 1;
  }
  return initialized;
}

int BSegment::is_valid() {
  if (!initialized) {
    init();
  }
  if (!p1 || !p2) {
    initialized = 0;
  }
  return initialized;
}

float *BSegment::field(float x, float y, float z) {
  if (!is_valid()) {
    return 0;
  }
  // the point
  float r[3];
  r[0] = x;
  r[1] = y;
  r[2] = z;
  // distances from the point
  float d1[3]; float d2[3];
  Vector::Sub(p1, r, d1);
  Vector::Sub(p2, r, d2);
  // segment distance
  float k = -Vector::DotProduct(current_direction, d1);
  float v[3];
  Vector::Scale(current_direction, k, v);
  float s[3];
  Vector::Add(v, d1, s);
  // sines:
  float temp[3];
  Vector::Sub(d1, s, temp);
  float sin1 = Vector::DotProduct(temp, current_direction) / Vector::Norm(d1);
  Vector::Sub(d2, s, temp);
  float sin2 = Vector::DotProduct(temp, current_direction) / Vector::Norm(d2);
  // the field;
  Vector::CrossProduct(s, current_direction, _temp_field);
  Vector::Scale(_temp_field, (sin2-sin1) / Vector::Norm2(s));
  return _temp_field;
}
