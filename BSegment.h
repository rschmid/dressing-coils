#ifndef __BSEGMENT_H
#define __BSEGMENT_H

class BSegment {
 public:
  BSegment();
  BSegment(BSegment *clone);
  ~BSegment();
  BSegment *Clone();
  int init();
  int is_valid();
  float *field(float x, float y, float z);

  // Members
  float *p1;
  float *p2;
 private:
  int initialized;
  static float _temp_field[3];
  float current_direction[3];
  void _default_constructor();
};


#endif
