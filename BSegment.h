#ifndef __BSEGMENT_H
#define __BSEGMENT_H

class BSegment {

 public:

  BSegment();
  BSegment(BSegment *clone);
  int SetPoints(const double *p1, const double *p2);
  double *GetPoint1() {return _p1;}
  double *GetPoint2() {return _p2;}
  BSegment *prev() {return _prev;}
  BSegment *next() {return _next;}
  BSegment *Clone();
  int is_valid();

 private:
  void _default_constructor();
  BSegment *_prev;
  BSegment *_next;
  double *_p1;
  double *_p2;
}


#endif
