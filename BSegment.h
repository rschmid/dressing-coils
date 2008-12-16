#ifndef __BSEGMENT_H
#define __BSEGMENT_H

class BSegment {
 public:
  BSegment();
  BSegment(BSegment *clone);
  virtual ~BSegment();
  BSegment *Clone();
  int init();
  int is_valid();
  virtual float *field(float x, float y, float z);
  virtual float *field(float *r);

  // Members
  float *p1;
  float *p2;
 protected:
  int initialized;
  static float _temp_field[3];
  float current_direction[3];
  float length;
  void _default_constructor();
};


#endif
