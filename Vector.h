#ifndef __VECTOR_H
#define __VECTOR_H

#define PI 3.141592653589793238462643383

#include <iostream.h>
#include <math.h>

class Vector {

 public:
  Vector() {};


static float *Add(float *A, float *B, float *C) {
  C[0] = A[0] + B[0];
  C[1] = A[1] + B[1];
  C[2] = A[2] + B[2];
  return C;
}

static float *Sub(float *A, float *B, float *C) {
  C[0] = A[0] - B[0];
  C[1] = A[1] - B[1];
  C[2] = A[2] - B[2];
  return C;
}
 
static void Scale(float *A, float mult, float *out = 0) {
  if (!out) out = A;
  out[0] = A[0] * mult;
  out[1] = A[1] * mult;
  out[2] = A[2] * mult;  
}

static float DotProduct(float *A, float *B) {

  if (A && B) {
    return A[0]*B[0] + A[1]*B[1] + A[2]*B[2];
  }
  else
    return 0.0;

}

static float *CrossProduct(float *A, float *B, float *C) {
 
  float temp[3];
  

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

static float *CrossProduct(float *A, float *B) {

  float *C = 0;

  if (A && B) 
    C = new float[3];
  
  return CrossProduct(A,B,C);

}

 static float Norm(float *A) {

   return sqrt(A[0]*A[0] + A[1]*A[1] + A[2]*A[2]);

 } 

 static float Norm2(float *A) {

   return A[0]*A[0] + A[1]*A[1] + A[2]*A[2];

 } 


 static float Normalize(float *A, float *out) {
   float temp;
   if (!A)
     return -1.0;
   temp = sqrt(A[0]*A[0] + A[1]*A[1] + A[2]*A[2]);
   out[0] = A[0] / temp;
   out[1] = A[1] / temp;
   out[2] = A[2] / temp;
   return temp;
 }  

 static float Normalize(float *A) {
   return Normalize(A, A);
 }

 static float Normalize(float *A, float mag) {
   float temp;
   temp = Normalize(A, A);
   A[0] *= mag;
   A[1] *= mag;
   A[2] *= mag;
   return temp;
 }

 static float Normalize(float *A, float *out, float mag) {
   float temp;
   temp = Normalize(A, out);
   out[0] *= mag;
   out[1] *= mag;
   out[2] *= mag;
   return temp;
 }

 static float Theta(float *A, float *B) {

   float c;
   
   float temp[3];

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

 static void Print(float *v) {

   cout << "{" << v[0]
	<< ", " << v[1]
	<< ", " << v[2]
	<< "}";

 }
 
 

};

#endif
