#include "BCoil.h"

#include "Vector.h"

BCoil::BCoil() {
  prev = next = 0;
}

int BCoil::AddNextPoint(const float *p) {
  return AddNextPoint(p[0], p[1], p[2]);
}

int BCoil::AddNextPoint(float x, float y, float z) {
  if (!p1) {
    p1 = new float(3);
    p1[0] = x; p1[1] = y; p1[2] = z;
    return 1;
  }
  if (!p2) {
    p2 = new float(3);
    p2[0] = x; p2[1] = y; p2[2] = z;
    return 1;
  }
  if (!next) {
    next = new BCoil();
    next->prev = this;
    next->p1 = p2;
    next->p2 = new float(3);
    next->p2[0] = x;
    next->p2[1] = y;
    next->p2[2] = z;
    return 1;
  }
  BCoil *next_most = this;
  while (next_most->next) {
    next_most = next_most->next;
    if (next_most == this) return 0; // Loop is closed
  }
  return next_most->AddNextPoint(x,y,z);
}


float *BCoil::field(float x, float y, float z) {
  float r[3];
  r[0] = x;
  r[1] = y;
  r[2] = z;
  return field(r);
}

float *BCoil::field(float *r) {
  float temp[] = {0., 0., 0.};
  BCoil *prev_most = this, *next_most = this;
  this->BSegment::field(r);
  Vector::Add(temp, _temp_field, temp);
  while (next_most->next && next_most->next != prev_most) {
    next_most = next_most->next;
    next_most->BSegment::field(r);
    Vector::Add(temp, _temp_field, temp);
  }
  while (prev_most->prev && prev_most->prev != next_most) {
    prev_most = prev_most->prev;
    prev_most->BSegment::field(r);
    Vector::Add(temp, _temp_field, temp);
  }
  _temp_field[0] = temp[0];
  _temp_field[1] = temp[1];
  _temp_field[2] = temp[2];
  return _temp_field;
}

int BCoil::is_closed() {
  BCoil *next_most = this;
  while (next_most = next_most->next) {
    if (next_most == this) return 1;
  }
  return 0;
}

BCoil *BCoil::get_first() {
  BCoil *prev_most = this;
  while (prev_most->prev) {
    prev_most = prev_most->prev;
    if (prev_most == this) return this;
  }
  return prev_most;
}