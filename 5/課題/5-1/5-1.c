#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Triangle {
  double x1, y1, x2, y2, x3, y3, R, G, B;
} TRG, *TRGP;

typedef struct list {
  TRG trg;
  struct list *next;
} LIST, *LISTP;

// min〜maxのdoubleの乱数を生成する
double generadeRand(double min, double max) {
  return min + (double)(rand()) / ((double)(RAND_MAX / (max - min)));
}

// 構造体Triangleに値をセット(posmin: 座標の最小値， posmax: 座標の最大値, cmin: 色の最小値, cmax: 色の最大値)
TRG setTRG(double posmin, double posmax, double cmin, double cmax) {
  TRG trg;

  // 値をセット
  trg.x1 = generadeRand(posmin, posmax);
  trg.x2 = generadeRand(posmin, posmax);
  trg.y1 = generadeRand(posmin, posmax);
  trg.y2 = generadeRand(posmin, posmax);
  trg.x3 = generadeRand(posmin, posmax);
  trg.y3 = generadeRand(posmin, posmax);
  trg.R  = generadeRand(cmin, cmax);
  trg.G  = generadeRand(cmin, cmax);
  trg.B  = generadeRand(cmin, cmax);

  return trg;
}

// リストの末尾にノードを追加
void appendList(LIST **head) {
  LISTP new, p = *head, prev;

  // メモリ確保
  if ((new = (LISTP)malloc(sizeof(LIST))) == NULL) {
    perror("Memory Allocation Error");
    exit(EXIT_FAILURE);
  }

  // 値の代入
  new->trg = setTRG(50, 550, 0, 1);
  new->next = NULL;

  // まだ要素が1つもないなら先頭に追加して終了
  if (p == NULL) {
    *head = new;
    return;
  }

  // 末尾までポインタを移動
  while (p != NULL) {
    prev = p;
    p = p->next;
  }

  // 末尾の要素の次の位置に追加
  prev->next = new;
}

// リストの要素を順に表示
void printList(LISTP p) {
  while (p != NULL) {
    printf("v1=(%.5lf, %.5lf), v2=(%.5lf, %.5lf), v3=(%.5lf, %.5lf) color(%.5lf, %.5lf, %.5lf)\n", p->trg.x1, p->trg.y1, p->trg.x2, p->trg.y2, p->trg.x3, p->trg.y3, p->trg.R, p->trg.G, p->trg.B);

    p = p->next;
  }
}

// リストのメモリ解放
void freeList(LISTP p) {
  if (p == NULL) return;

  freeList(p->next);
  free(p);
}


int main() {
  int N = 100;

  srand((unsigned int)time(NULL));

  LISTP trgList = NULL;
  for(int i = 0; i < N; i++) appendList(&trgList);

  printList(trgList);

  freeList(trgList);

  return 0;
}
