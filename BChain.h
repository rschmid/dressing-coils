#ifndef __BCHAIN_H
#define __BCHAIN_H

#include "BSegment.h"

struct _BChain {
  BSegment *link;
  _BChain *next;
};

class BChain : public BSegment{
  public:
  BChain();
  int AddNextPoint(const float *p);
  int AddNextPoint(float x, float y, float z);
  float *field(float *r);
  float *field(float x, float y, float z);
  int is_valid();
  int is_closed();
  BChain *get_first();
  // Members
  BChain *first;
  BChain *last;

};

#endif
