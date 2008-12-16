#ifndef __VECTOR_H
#define __VECTOR_H

#include "TROOT.h"

#define PI 3.141592653589793238462643383

#include <iostream.h>
#include <math.h>

class Vector {

 public:
  Vector() {};


static Double_t *Add(Double_t *A, Double_t *B, Double_t *C) {

  C[0] = A[0] + B[0];
  C[1] = A[1] + B[1];
  C[2] = A[2] + B[2];

  return C;

}
 
static Double_t DotProduct(Double_t *A, Double_t *B) {

  if (A && B) {
    return A[0]*B[0] + A[1]*B[1] + A[2]*B[2];
  }
  else
    return 0.0;

}

static Double_t *CrossProduct(Double_t *A, Double_t *B, Double_t *C) {
 
  Double_t temp[3];
  

  if (A && B && C) {

    temp[0] = A[1]*B[2] - A[2]*B[1];
    temp[1] = A[2]*B[0] - A[0]*B[2];
    temp[2] = A[0]*B[1] - A[1]*B[0];

  }

  C[0] = temp[0];
  C[1] = temp[1];
  C[2] = temp[2];

  return C;

}

static Double_t *CrossProduct(Double_t *A, Double_t *B) {

  Double_t *C = 0;

  if (A && B) 
    C = new Double_t[3];
  
  return CrossProduct(A,B,C);

}

 static Double_t Norm(Double_t *A) {

   return sqrt(A[0]*A[0] + A[1]*A[1] + A[2]*A[2]);

 } 

 static Double_t Norm2(Double_t *A) {

   return A[0]*A[0] + A[1]*A[1] + A[2]*A[2];

 } 


 static Double_t Normalize(Double_t *A, Double_t *out) {

   Double_t temp;

   if (!A)
     return -1.0;

   temp = sqrt(A[0]*A[0] + A[1]*A[1] + A[2]*A[2]);

   out[0] = A[0] / temp;
   out[1] = A[1] / temp;
   out[2] = A[2] / temp;
   
   return temp;
 }  

 static Double_t Normalize(Double_t *A) {
   
   return Normalize(A, A);

 }

 static Double_t Normalize(Double_t *A, Double_t mag) {
   
   Double_t temp;

   temp = Normalize(A, A);
   
   A[0] *= mag;
   A[1] *= mag;
   A[2] *= mag;

   return temp;

 }

 static Double_t Theta(Double_t *A, Double_t *B) {

   Double_t c;
   
   Double_t temp[3];

   c = DotProduct(A, B);
   c /= Norm(A);
   c /= Norm(B);
   
   CrossProduct(A, B, temp);
   CrossProduct(temp, A, temp);
   
   if (DotProduct(B, temp) >= 0)
     return acos(c);
   else
     return 2. * PI - acos(c);

 }

 static void Print(Double_t *v) {

   cout << "{" << v[0]
	<< ", " << v[1]
	<< ", " << v[2]
	<< "}";

 }
 
 

};

#endif
