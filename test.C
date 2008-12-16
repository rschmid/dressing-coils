#include "BSegment.h"

//#include <stdlib.h>
#include <iostream.h>

int main (int argc, char **argv) {
  cout << "ok\n";
  BSegment *seg = new BSegment();
  float *temp = seg->field(1,2,3);
  cout << temp[0] << "\t"
       << temp[1] << "\t"
       << temp[2] << "\n";
  if (seg->is_valid()) {
    cout << "valid\n";
  }
  else {
    cout << "not valid\n";
  }
  return 0;
}
