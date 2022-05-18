#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Triangle {
  double x1, y1, x2, y2, x3, y3, R, G, B;
} TRG, *TRGP;

// min〜maxのdoubleの乱数を生成する
double generadeRand(double min, double max) {
  return min + (double)(rand()) / ((double)(RAND_MAX / (max - min)));
}

// 構造体Triangleに値をセット(posmin: 座標の最小値， posmax: 座標の最大値, cmin: 色の最小値, cmax: 色の最大値)
TRGP setTRG(double posmin, double posmax, double cmin, double cmax) {
  TRGP p;

  // メモリ確保
  if ((p = (TRGP)malloc(sizeof(TRG))) == NULL) {
    perror("Memory Allocation Error");
    exit(EXIT_FAILURE);
  }

  // 値をセット
  p->x1 = generadeRand(posmin, posmax);
  p->x2 = generadeRand(posmin, posmax);
  p->y1 = generadeRand(posmin, posmax);
  p->y2 = generadeRand(posmin, posmax);
  p->x3 = generadeRand(posmin, posmax);
  p->y3 = generadeRand(posmin, posmax);
  p->R  = generadeRand(cmin, cmax);
  p->G  = generadeRand(cmin, cmax);
  p->B  = generadeRand(cmin, cmax);

  return p;
}

int main() {
  int N = 100;

  srand((unsigned int)time(NULL));

  for(int i = 0; i < N; i++) {
    TRGP trg = setTRG(50, 550, 0, 1);

    // デバッグ用
    // printf("v1=(%.5lf, %.5lf), v2=(%.5lf, %.5lf), v3=(%.5lf, %.5lf) color(%.5lf, %.5lf, %.5lf)\n", trg->x1, trg->y1, trg->x2, trg->y2, trg->x3, trg->y3, trg->R, trg->G, trg->B);
  }

  return 0;
}
