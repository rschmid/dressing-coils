#include "BSegment.h"
#include "Vector.h"

float BSegment::_temp_field[3];

BSegment::BSegment() {
  _default_constructor();
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

/*
 * Initialize the values
 * set length of segment and current direction
 */
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
  else {
    cout << "!p1 || !p2" << endl;
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

/**
 * Calculates the B field due to this segment at point r (x,y,z)
 * @param float *r : position vector float[3];
 * @return float * : Field vector float[3] (static variable)
 */
float *BSegment::field(float *r) {
  if (!is_valid() || !r) {
    return 0;
  }
  // distances from the point
  float d1[3]; float d2[3];
  Vector::Sub(p1, r, d1); // d1 = p1 - r
  Vector::Sub(p2, r, d2); // d2 = p2 - r
  // segment distance
  float k = -Vector::DotProduct(current_direction, d1); // k = - Idir.d1
  float v[3];
  Vector::Scale(current_direction, k, v); // v = k * Idir
  float s[3];
  Vector::Add(v, d1, s); // s = v + d1
  // sines:
  float temp[3];
  Vector::Sub(d1, s, temp); // temp = d1 - s; sin1 = temp.Idir / |d1|
  float sin1 = Vector::DotProduct(temp, current_direction) / Vector::Norm(d1);
  Vector::Sub(d2, s, temp); // temp = d2 - s; sin2 = temp.Idir / |d2|
  float sin2 = Vector::DotProduct(temp, current_direction) / Vector::Norm(d2);
  // the field: B = (sin2-sin1) / s.s * (s x Idir)
  Vector::CrossProduct(s, current_direction, _temp_field); 
  Vector::Scale(_temp_field, (sin2-sin1) / Vector::Norm2(s));
  return _temp_field;
}

float *BSegment::field(float x, float y, float z) {
  // the point
  float r[3];
  r[0] = x;
  r[1] = y;
  r[2] = z;
  return field(r);
}

float BSegment::get_length() {
  if (!initialized && !init()) {
    return -1.0;
  }
  return length;
}
