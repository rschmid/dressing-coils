#include "BCoil.h"

//#include <stdlib.h>
#include <iostream.h>

int main (int argc, char **argv) {
  cout << "ok\n";
  BCoil *seg = new BCoil();
  float *field;
  seg->AddNextPoint(0, 0, 0);
  seg->AddNextPoint(1, 0, 0);
  seg->AddNextPoint(1, 1, 0);
  seg->AddNextPoint(0, 1, 0);
  seg->AddNextPoint(0, 0, 0);

  field = seg->field(-1,-1,-1);
  if (field) {
    cout << "field @ (0,0,0) = {" << field[0]
	 << ", " << field[1] << ", " << field[2] << "}\n";
  }
  else {
    cout << "valid = " << seg->is_valid() << endl;
  }
  return 0;
}
