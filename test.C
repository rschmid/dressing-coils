#include "BCylinder.h"
#include "BChain.h"
#include "Vector.h"

//#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
using namespace std;

float coil_rotation(float phi = 0.) {
  static float rotation = 0.;
  if (phi != 0.) {
    rotation = phi;
  }
  return rotation;
}

float coil_radius(float radius = 0.) {
  static float saved_radius = 0.;
  if (radius != 0.) {
    saved_radius = radius;
  }
  return saved_radius;
}

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
  temp_point[0] = current->link->p1[0];
  temp_point[1] = -current->link->p1[1];
  temp_point[2] = current->link->p1[2];
  copy->BChain::AddNextPoint(temp_point);
  do {
    temp_point[0] = current->link->p2[0];
    temp_point[1] = -current->link->p2[1];
    temp_point[2] = current->link->p2[2];
    copy->BChain::AddNextPoint(temp_point);
  } while ((current = current->next));
  cout << "Copied coil to bottom y" << endl;
  return copy;
}

BCylinder *rectangular_coil(float phi, float length, float radius) {
  BCylinder *temp_coil = new BCylinder(radius);
  float temp_coords[2];
  float rotation = coil_rotation();
  temp_coords[0] = rotation + phi; temp_coords[1] = rotation;
  temp_coil->AddNextPoint(temp_coords);
  temp_coords[1] = length;
  temp_coil->AddNextPoint(temp_coords);
  temp_coords[0] = rotation;
  temp_coil->AddNextPoint(temp_coords);
  apply_x_symmetry(temp_coil);
  apply_z_symmetry(temp_coil);
  return temp_coil;
}

int cos_theta_coil_pairs(int n, float length, BCylinder **coil_array) {
  float angle, radius = coil_radius();
  for (int i=0; i<n; i++) {
    angle = acos(0.5 - ((float)i)/((float)n));
    coil_array[i] = rectangular_coil(angle, length, radius);
    coil_array[i + n] = copy_to_bottom_y(coil_array[i]);
  }
  return 2*n;
}

int parse_segmented_arc(BCylinder **coil_array) {
  float temp_coords[2];
  float radius = coil_radius(),
    rotation = coil_rotation();
  BCylinder *temp_coil = new BCylinder(radius);
  while (cin >> temp_coords[0] >> temp_coords[1]) {
    temp_coords[0] += rotation;
    temp_coil->AddNextPoint(temp_coords);
  }
  apply_x_symmetry(temp_coil);
  apply_z_symmetry(temp_coil);
  if (temp_coil->is_closed()) cout << "Closed circuit" << endl;
  else cout << "Circuit not closed" << endl;
  coil_array[0] = temp_coil;
  coil_array[1] = copy_to_bottom_y(temp_coil);
  return 2;
}

int cell_calculations(int set = 0) {

}

int main (int argc, char **argv) {
  if (argc == 1 && strcmp(argv[1], "-r")) {
    coil_rotation(PI/2.0);
  }
  coil_radius(.25);
  char input[1000];
  float radius, field[3], temp_coords[3];
  BCylinder *coil_array[100], **array_pointer;
  int i, n_coils = 0;
  sprintf(input, "start");
  while (strcmp(input, "end") != 0) {
    array_pointer = coil_array + n_coils;
    if (strcmp(input, "coil") == 0 ||
	strcmp(input, "next") == 0) {
      // Segmented arcs coil
      n_coils += parse_segmented_arc(array_pointer);
    }
    else if (strcmp(input, "cos") == 0) {
      // Cosine theta coil
      if (!(cin >> temp_coords[0] >> temp_coords[1])) {
	cout << "error parsing: n length" << endl;
	break;
      }
      n_coils += cos_theta_coil_pairs((int)temp_coords[0], temp_coords[1],
			   array_pointer);
    }
    else if (strcmp(input, "radius") == 0) {
      // Set the radius
      if (cin >> radius) {
	coil_radius(radius);
	cout << "Radius set to " << radius << endl;
      } 
      else 
	cout << "Radius not understood" << endl;
    }
    else if (strcmp(input, "cell") == 0) {
      cell_calculation(1);
    }
    else if (strcmp(input, "start") == 0) {
      cout << "Ok: start" << endl;
      sprintf(input, "coil");
    }
    else {
      cout << "not understood" << endl;
    }
    // get next command
    cin.clear();
    cin >> input;
  };

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

