#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define m1 1.0
#define m2 1.0
#define l1 1.0
#define l2 1.0
#define G 9.8

typedef struct {
  double theta1;
  double theta2;
  double omega1;
  double omega2;
} State;

State func(double t, State s) {
  State dot_s;

  double delta = s.theta1 - s.theta2;
  double M = 2 * m1 + m2;

  double Num1 = - G * M * sin(s.theta1) - m2 * G * sin(s.theta1 - 2 * s.theta2) - 2 * sin(delta) * m2 * (pow(s.omega2, 2) * l2 + pow(s.omega1, 2) * l1 * cos(delta));
  double Den1 = l1 * (M - m2 * cos(2 * delta));
  if (Den1 == 0) {
    printf("Value Error\n");
    exit(1);
  }

  double Num2 = 2 * sin(delta) * (pow(s.omega1, 2) * l1 * (m1 + m2) + G * (m1 + m2) * cos(s.theta1) + pow(s.omega2, 2) * l2 * m2 * cos(delta));
  double Den2 = l2 * (M - m2 * cos(2 * delta));
  if (Den2 == 0) {
    printf("Value Error\n");
    exit(1);
  }

  dot_s.theta1 = s.omega1;
  dot_s.theta2 = s.omega2;
  dot_s.omega1 = Num1 / Den1;
  dot_s.omega2 = Num2 / Den2;

  return dot_s;
}

State rk4_step(double t, State current, double dt) {
  State k1, k2, k3, k4;
  State temp;
  State next_state;

  k1 = func(t, current);

  temp.theta1 = current.theta1 + k1.theta1 * dt * 0.5;
  temp.theta2 = current.theta2 + k1.theta2 * dt * 0.5;
  temp.omega1 = current.omega1 + k1.omega1 * dt * 0.5;
  temp.omega2 = current.omega2 + k1.omega2 * dt * 0.5;
  k2 = func(t + dt * 0.5, temp);
  
  temp.theta1 = current.theta1 + k2.theta1 * dt * 0.5;
  temp.theta2 = current.theta2 + k2.theta2 * dt * 0.5;
  temp.omega1 = current.omega1 + k2.omega1 * dt * 0.5;
  temp.omega2 = current.omega2 + k2.omega2 * dt * 0.5;
  k3 = func(t + dt * 0.5, temp);
  
  temp.theta1 = current.theta1 + k3.theta1 * dt * 1.0;
  temp.theta2 = current.theta2 + k3.theta2 * dt * 1.0;
  temp.omega1 = current.omega1 + k3.omega1 * dt * 1.0;
  temp.omega2 = current.omega2 + k3.omega2 * dt * 1.0;
  k4 = func(t + dt * 1.0, temp);

  next_state.theta1 = current.theta1 + dt * (k1.theta1 + 2 * k3.theta1 + k4.theta1) / 6.0;
  next_state.theta2 = current.theta2 + dt * (k1.theta2 + 2 * k3.theta2 + k4.theta2) / 6.0;
  next_state.omega1 = current.omega1 + dt * (k1.omega1 + 2 * k3.omega1 + k4.omega1) / 6.0;
  next_state.omega2 = current.omega2 + dt * (k1.omega2 + 2 * k3.omega2 + k4.omega2) / 6.0;

  return next_state;
}

double calc_distance(State A, State B) {
  double x2_A = l1 * sin(A.theta1) + l2 * sin(A.theta2);
  double y2_A = - l1 * cos(A.theta1) - l2 * cos(A.theta2);
  double x2_B = l1 * sin(B.theta1) + l2 * sin(B.theta2);
  double y2_B = - l1 * cos(B.theta1) - l2 * cos(B.theta2);

  double dist = sqrt(pow((x2_A - x2_B), 2) + pow((y2_A - y2_B), 2));
  return dist;
}

int main(void) {
  double t = 0.0;
  double dt = 0.005;
  double t_max = 30;
  int steps = (int)(t_max / dt);
  
  State s1;
  s1.theta1 = M_PI / 2;
  s1.theta2 = M_PI / 2;
  s1.omega1 = 0.0;
  s1.omega2 = 0.0;

  State s2;
  s2.theta1 = M_PI / 2 + 0.001;
  s2.theta2 = M_PI / 2;
  s2.omega1 = 0.0;
  s2.omega2 = 0.0;
  
  printf("time,distance,x_A,y_A,x_B,y_B\n");
  for(int i = 0; i < steps; i++){
    double x2_A = l1 * sin(s1.theta1) + l2 * sin(s1.theta2);
    double y2_A = - l1 * cos(s1.theta1) - l2 * cos(s1.theta2);
    double x2_B = l1 * sin(s2.theta1) + l2 * sin(s2.theta2);
    double y2_B = - l1 * cos(s2.theta1) - l2 * cos(s2.theta2);
    
    double dist = calc_distance(s1, s2); 
    printf("%f,%f,%f,%f,%f,%f\n", t, dist, x2_A, y2_A, x2_B, y2_B);

    s1 = rk4_step(t, s1, dt);
    s2 = rk4_step(t, s2, dt);

    t += dt;
  }
  return 0;
}







