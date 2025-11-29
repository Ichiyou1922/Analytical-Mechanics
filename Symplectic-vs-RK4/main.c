#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define G 9.8
#define L 1.0
#define M 1.0

typedef struct {
  double theta;
  double p;
}State;

State func(double t, State s) {
  State dot_s;
  dot_s.theta = s.p / (M * pow(L, 2));
  dot_s.p = - M * G * L * sin(s.theta);
  return dot_s;
}

State rk4_step(double t, State current, double dt) {
  State k1, k2, k3, k4;
  State temp; //計算用の仮設構造体
  State next_state;

  k1 = func(t, current);

  temp.theta = current.theta + k1.theta * dt * 0.5;
  temp.p = current.p + k1.p * dt * 0.5;
  k2 = func(t + dt * 0.5, temp);

  temp.theta = current.theta + k2.theta * dt * 0.5;
  temp.p = current.p + k2.p * dt * 0.5;
  k3 = func(t + dt * 0.5, temp);

  temp.theta = current.theta + k3.theta * dt;
  temp.p = current.p + k3.p * dt;
  k4 = func(t + dt, temp);

  next_state.theta = current.theta + dt * (k1.theta + 2 * k2.theta + 2 * k3.theta + k4.theta) / 6.0;
  next_state.p = current.p + dt * (k1.p + 2 * k2.p + 2 * k3.p + k4.p) / 6.0;

  return next_state;
}

State symplectic_step(double t, State current, double dt) {
  State next_state;
  next_state.p = current.p - M * G * L * sin(current.theta) * dt;
  next_state.theta = current.theta + next_state.p * dt / (M * pow(L, 2));
  
  return next_state;
}

int main(void) {
  double t = 0.0;
  double dt = 0.05;
  double t_max = 500.0;
  int steps = (int)(t_max / dt);
  
  State s_rk4;
  s_rk4.theta = 1.0;
  s_rk4.p = 0.0;

  State s_sym;
  s_sym.theta = 1.0;
  s_sym.p = 0.0;
  
  printf("time,E_rk4,E_sym\n");
  //main loop
  for(int i = 0; i < steps; i++) {
    // エネルギーH
    double H_rk4 = 0.5 * pow(s_rk4.p, 2) / (M * pow(L, 2)) + M * G* L * (1 - cos(s_rk4.theta));
    double H_sym = 0.5 * pow(s_sym.p, 2) / (M * pow(L, 2)) + M * G* L * (1 - cos(s_sym.theta));
    
    printf("%f,%f,%f\n", t, H_rk4, H_sym);

    s_rk4 = rk4_step(t, s_rk4, dt);
    s_sym = symplectic_step(t, s_sym, dt);
    t += dt;
  }
return 0;
}
