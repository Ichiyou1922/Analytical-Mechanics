#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define M 1.0
#define G 9.8
#define H 10.0
#define T_END 1.428
#define N 100


int main(void) {
  double y[N+1];
  double dt = T_END / N;
  for (int i = 0; i < N+1; i++) {
    double t = i * dt;
    y[i] = H - H * t / T_END;
  }
  printf("y[0]: %f\ny[50]: %f\ny[100]: %f\n", y[0], y[50], y[100]);
  
  return 0;
}
