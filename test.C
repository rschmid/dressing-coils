#include "BChain.h"

//#include <stdlib.h>
#include <iostream>
using namespace std;

int main (int argc, char **argv) {
  char input[1000];
  float temp_coords[3];
  BChain *chain = new BChain();
  while (cin >> temp_coords[0] >> temp_coords[1] >> temp_coords[2]) {
    chain->AddNextPoint(temp_coords);
  }
  cout << "ok: " << input << endl;
  float *field;
  /*
  seg->AddNextPoint(0, 0, 0);
  seg->AddNextPoint(1, 0, 0);
  seg->AddNextPoint(1, 1, 0);
  seg->AddNextPoint(0, 1, 0);
  seg->AddNextPoint(0, 0, 0);
  */

  field = (float *)chain->field(-1,-1,-1);
  if (field) {
    cout << "field @ (0,0,0) = {" << field[0]
	 << ", " << field[1] << ", " << field[2] << "}\n";
  }
  else {
    cout << "valid = " << chain->is_valid() << endl;
  }
  return 0;
}
