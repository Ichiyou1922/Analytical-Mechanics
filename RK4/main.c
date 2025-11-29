#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define G 9.8
#define L 1.0
#define M 1.0

typedef struct {
  double theta;
  double omega;
}State;

State func(double t, State s) {
  State dot_s;
  dot_s.theta = s.omega;
  dot_s.omega = -(G/L)*sin(s.theta);
  return dot_s;
}

State rk4_step(double t, State current, double dt) {
  State k1, k2, k3, k4;
  State temp; //計算用の仮設構造体
  State next_state;

  k1 = func(t, current);

  temp.theta = current.theta + k1.theta * dt * 0.5;
  temp.omega = current.omega + k1.omega * dt * 0.5;
  k2 = func(t + dt * 0.5, temp);

  temp.theta = current.theta + k2.theta * dt * 0.5;
  temp.omega = current.omega + k2.omega * dt * 0.5;
  k3 = func(t + dt * 0.5, temp);

  temp.theta = current.theta + k3.theta * dt;
  temp.omega = current.omega + k3.omega * dt;
  k4 = func(t + dt, temp);

  next_state.theta = current.theta + dt * (k1.theta + 2 * k2.theta + 2 * k3.theta + k4.theta) / 6.0;
  next_state.omega = current.omega + dt * (k1.omega + 2 * k2.omega + 2 * k3.omega + k4.omega) / 6.0;

  return next_state;
}

int main(void) {
  double t = 0.0;
  double dt = 0.05;
  double t_max = 10.0;
  int steps = (int)(t_max / dt);
  
  State s;
  s.theta = 1.0;
  s.omega = 0.0;
  
  printf("time,theta,omega,energy\n");
  //main loop
  for(int i = 0; i < steps; i++) {
    // エネルギーE
    double E = 0.5 * M * pow(L, 2) * pow(s.omega, 2) + M * G * L * (1 - cos(s.theta));
    // 張力S
    double S = M * G * cos(s.theta) + M * L * pow(s.omega, 2);

    printf("%f,%f,%f,%f,%f\n", t, s.theta, s.omega, E, S);

    s = rk4_step(t, s, dt);
    t += dt;
  }
return 0;
}
