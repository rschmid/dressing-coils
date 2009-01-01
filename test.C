#include "BCylinder.h"
#include "BChain.h"
#include "Vector.h"

//#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

int apply_x_symmetry(BCylinder *coil) {
  if (coil->p2[1] != 0.) {
    cout << "Could not add x symmetry, p2_y != 0." << endl;
    return -1;
  } 
  else {
    cout << "great! adding x symmetry...";
  }
  int count = 0;
  float temp_point[3];
  _BChain *current;
  current = coil->last;
  do {
    temp_point[0] = -current->link->p1[0];
    temp_point[1] = current->link->p1[1];
    temp_point[2] = current->link->p1[2];
    coil->BChain::AddNextPoint(temp_point);
    count++;
  } while ((current = current->prev));
  cout << " added " << count << " segments" << endl;
  return count;
}

int apply_z_symmetry(BCylinder *coil) {
  if (coil->p2[2] != 0.) {
    cout << "Could not add z symmetry, p2_z != 0." << endl;
    return -1;
  } 
  else {
    cout << "great! adding z symmetry...";
  }
  int count = 0;
  float temp_point[3];
  _BChain *current;
  current = coil->last;
  do {
    temp_point[0] = current->link->p1[0];
    temp_point[1] = current->link->p1[1];
    temp_point[2] = -current->link->p1[2];
    coil->BChain::AddNextPoint(temp_point);
    count++;
  } while ((current = current->prev));
  cout << " added " << count << " segments" << endl;
  return count;
}

BCylinder *copy_to_bottom_y(BCylinder *coil) {
  if (!coil) {
    cout << "Empty coil" << endl;
    return 0;
  }
  BCylinder *copy = new BCylinder(coil->radius);
  _BChain *current;
  float temp_point[3];
  current = coil->first;
  do {
    temp_point[0] = current->link->p1[0];
    temp_point[1] = -current->link->p1[1];
    temp_point[2] = current->link->p1[2];
    copy->BChain::AddNextPoint(temp_point);
  } while ((current = current->next));
  cout << "Copied coil to bottom y" << endl;
  return copy;
}

int main (int argc, char **argv) {
  float phi_rotation = 0.;
  if (argc == 1 && strcmp(argv[1], "-r")) {
    phi_rotation = PI/2.0;
  }
  char input[1000];
  float field[3], temp_coords[3];
  BCylinder *temp_coil, *coil_array[100];
  int i, n_coils = 0, n_split;
  do {
    temp_coil = new BCylinder(0.25);
    while (cin >> temp_coords[0] >> temp_coords[1]) {
      temp_coords[0] += phi_rotation;
      n_split = temp_coil->AddNextPoint(temp_coords);
      if (n_split > 1) {
	cout << "Broken into " << n_split << " segments" << endl;
      }
    }
    apply_x_symmetry(temp_coil);
    apply_z_symmetry(temp_coil);
    if (temp_coil->is_closed()) cout << "Closed circuit" << endl;
    else cout << "Circuit not closed" << endl;
    coil_array[n_coils] = temp_coil;
    n_coils++;
    cin.clear();
    cin >> input;
  } while (strcmp(input, "next") == 0);

  for (i=0; i<n_coils; i++) {
    coil_array[n_coils + i] = copy_to_bottom_y(coil_array[i]);
  }
  n_coils *= 2;

  cout << "Read " << n_coils << " coils" << endl;

  cout << "ok. Now enter points where you want the field" << endl;
  while (cin >> temp_coords[0] >> temp_coords[1] >> temp_coords[2]) {
    field[0] = field[1] = field[2] = 0.;
    for (i=0; i<n_coils; i++) {
      Vector::Add(field, coil_array[i]->field(temp_coords[0],temp_coords[1],temp_coords[2]), field);
    }
    cout << "field @ (" << temp_coords[0] << ", "
	 << temp_coords[1] << ", " << temp_coords[2]
	 << ") = {" << field[0]
	 << ", " << field[1] << ", " << field[2] << "}\n";
  }
  return 0;
}

