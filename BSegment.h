#ifndef __BSEGMENT_H
#define __BSEGMENT_H

class BSegment {
public:
  BSegment();
  virtual ~BSegment();
  virtual int init(); // use when changed
  virtual int is_valid();
  virtual float *field(float *r);
  virtual float *field(float x, float y, float z);

  virtual float get_length();
  // Members
  float *p1;
  float *p2;
  
protected:
  static float _temp_field[3]; // store latest field

  int initialized;
  float current_direction[3];
  float length;

  void _default_constructor();
};


#endif
