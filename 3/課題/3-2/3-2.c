#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef double (*P_FUNC)(double);


// target function 1
double f1(double x) {
  return x * x;
}

// target function 2
double f2(double x) {
  return x * x * x + x * x;
}

// target function 3
double f3(double x) {
  return sin(x) + cos(x);
}

// 微小台形の面積を求める
double trapezoid(double w1, double w2, double h) {
  return (w1 + w2) * h / 2.0;
}

// 台形法により一変数関数の積分値を計算
double integral(double x1, double x2, int n, P_FUNC funcptr) {
  double ret;

  return ret;
}


int main() {
  P_FUNC funcptr[3] = {f1, f2, f3};                                  // 積分値を求める関数の関数ポインタの配列
  double val[3][2] = {{1.0, 10.0}, {1.0, 10.0}, {M_PI / 3.0, M_PI}}; // 積分範囲

  for (int i = 0; i < 3; i++) {
    printf("f%d: %10f\n", i, integral(val[i][0], val[i][1], 10000, funcptr[i]));
  }
}
