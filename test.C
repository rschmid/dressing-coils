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
  float *field = 0;
  cin >> input;
  cin.clear();
  cout << "ok. Now enter points where you want the field" << endl;
  while (cin >> temp_coords[0] >> temp_coords[1] >> temp_coords[2]) {
    field = chain->field(temp_coords[0],temp_coords[1],temp_coords[2]);
    cout << "field @ (" << temp_coords[0] << ", "
	 << temp_coords[1] << ", " << temp_coords[2]
	 << ") = {" << field[0]
	 << ", " << field[1] << ", " << field[2] << "}\n";
  }
  return 0;
}
