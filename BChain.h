#ifndef __BCHAIN_H
#define __BCHAIN_H

#include "BSegment.h"

struct _BChain {
  BSegment *link;
  _BChain *next;
};

class BChain : public BSegment {
public:
  BChain();
  ~BChain();
  // overloaded methods
  virtual int is_valid();
  float *field(float *r);
  float *field(float x, float y, float z);

  int is_closed();
  // Members
  _BChain *first;
  _BChain *last;

  int AddNextPoint(float *p);
  int AddNextPoint(float x, float y, float z);

};

#endif
