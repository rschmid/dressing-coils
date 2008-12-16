#include "BSegment.h"

BSegment::BSegment() {
  this->_default_constructor();
}

BSegment::BSegment(BSegment *clone) {
  this->_default_constructor();
}

BSegment::~BSegment() {
  if (!_prev) {
    delete _p1;
  }
  else {
    _prev->_next = 0;
  }
  if (!_next) {
    delete _p2;
  }
  else {
    _next->prev = 0;
  }
}

void BSegment::_default_constructor() {
  this->_prev = 0;
  this->_next = 0;
  this->_p1 = 0;
  this->_p2 = 0;
}

/*
 * Returns 1 if completed successfully
 */
void SetPoints(const double *p1, const double *p2) {
  if (p1) {
    if (!_p1) _p1 = double(3);
    _p1[0] = p1[0];
    _p1[1] = p1[1];
    _p1[2] = p1[2];
  }
  if (p2) {
    if (!_p2) _p2 = double(3);
    _p2[0] = p2[0];
    _p2[1] = p2[1];
    _p2[2] = p2[2];
  }
}

BSegment *BSegment::Clone() {
  BSegment *clone = new BSegment();
  return clone;
}

int is_valid() {
  return (_p1 && _p2);
}
