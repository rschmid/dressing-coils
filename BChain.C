#include "BChain.h"

#include "Vector.h"

BChain::BChain() {
  first = last = 0;
}

BChain::~BChain() {
  first = last = 0;
}

int BChain::init() {
  if (p1 && p2) {
    if (!first || !last) {
      first = new _BChain;
      BSegment *temp = new BSegment;
      temp->p1 = p1;
      temp->p2 = p2;
      temp->init();
      first->link = temp;
      first->next = 0;
      last = first;
    }
    return 1;
  }
  return 0;
}

int BChain::is_valid() {
  if (!first || !last || !p1 || !p2 ||
      first->link->p1 != p1 || last->link->p2 != p2) {
    return 0;
  }
  return 1;
}

int BChain::AddNextPoint(float *p) {
  return AddNextPoint(p[0], p[1], p[2]);
}

int BChain::AddNextPoint(float x, float y, float z) {
  if (!p1) {
    p1 = new float(3);
    p1[0] = x; p1[1] = y; p1[2] = z;
    return 1;
  }
  if (!p2) {
    p2 = new float(3);
    p2[0] = x; p2[1] = y; p2[2] = z;
    return init();
  }
  if ((!first || !last) && !init()) {
    return 0;
  }
  // create a new segment
  BSegment *temp = new BSegment();
  temp->p1 = last->link->p2;
  temp->p2 = new float(3);
  temp->p2[0] = x;
  temp->p2[1] = y;
  temp->p2[2] = z;
  temp->init();
  // add it to the chain as the last link
  _BChain *current = new _BChain;
  current->next = 0;
  current->link = temp;
  last->next = current;
  last = current;
  p2 = temp->p2;
  return 1;
}


float *BChain::field(float x, float y, float z) {
  float r[3];
  r[0] = x;
  r[1] = y;
  r[2] = z;
  return field(r);
}

float *BChain::field(float *r) {
  float temp[] = {0., 0., 0.};
  _BChain *current = first;
  current->link->field(r);
  Vector::Add(temp, _temp_field, temp);
  while (current->next) {
    current = current->next;
    if (current == first) break;
    current->link->field(r);
    Vector::Add(temp, _temp_field, temp);
  }
  _temp_field[0] = temp[0];
  _temp_field[1] = temp[1];
  _temp_field[2] = temp[2];
  return _temp_field;
}

int BChain::is_closed() {
  _BChain *current = first;
  while (current->next) {
    current = current->next;
    if (current == first) return 1;
  }
  return 0;
}

