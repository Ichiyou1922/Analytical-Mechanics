#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define M 1.0
#define G 9.8
#define H 10.0
#define T_END 1.42857
#define N 100

double calc_action(double y[], double dt) {
  double sum = 0.0;
  int i = 0;
  while (i < N) {
    double T = 0.5 * M * pow((y[i+1]-y[i]) / dt, 2);
    double V = M * G * ((y[i+1]+y[i]) / 2);
    double term = (T - V) * dt;
    sum += term;
    i++;
  }
  return sum;
}

int main(void) {
  
/*
  FILE *fp = fopen("output.csv", "w");
  if (fp == NULL) {
    perror("Can`t open the file");
    return 1;
  }
*/

  srand((unsigned)time(NULL));
  int max_iter = 100000;
  double step_size = 0.1;
  double y[N+1];
  // y[]を直線で初期化
  double dt = T_END / N;
  for (int i = 0; i < N+1; i++) {
    double t = i * dt;
    y[i] = H - H * t / T_END;
  }

  

  //main loop
  int iter = 0;
  while (iter <= max_iter) {
    double t = iter * dt;
    int k = rand() % ((N-1) - 1 + 1) + 1;
    double y_old = y[k]; //判定処理のためにコピーしておく
    double S_old = calc_action(y, dt); //判定条件のため
    y[k] += ((double)rand()/RAND_MAX - 0.5) * 2 * step_size;
    // 1. (double)rand()/RAND_MAXで0~1までの乱数(正規化)
    // 2. ((double)rand()/RAND_MAX - 0.5)で-0.5~0.5
    // 3. ((double)rand()/RAND_MAX - 0.5) * 2で-1~1
    // 4. 要望の物を掛けて，期待した範囲の乱数が生成される．
    double S_new = calc_action(y, dt);
    if (S_new < S_old) {
      continue;
    }
    else {
      y[k] = y_old;
    }

    iter++;
  }

  // 結果を表示
  int i = 0;
  while (i < N + 1) {
    double t = i * dt;
    double y_exact = H - 0.5 * G * pow(t, 2);//比較用解析解
    printf("%f, %f, %f\n", t, y[i], y_exact);
    i++;
  }
  
  return 0;
}



