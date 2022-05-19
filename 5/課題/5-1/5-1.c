// 三角形のデータをN個ランダムに作成して線形リストに保持し，それらのデータをPostscript形式に変換する
// % gcc -o 5-1 5-1.c
// ./5-1 [出力ファイル名] [N]

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 三角形の構造体
typedef struct Triangle {
  double x1, y1, x2, y2, x3, y3, R, G, B;
} TRG, *TRGP;

// 線形リストの構造体
typedef struct list {
  TRG trg;           // 三角形のデータ
  struct list *next; // 次のノード
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

  // 末尾の要素の次の位置に追加
  while (p != NULL) {
    prev = p;
    p = p->next;
  }
  prev->next = new;
}

// リストの要素を順に表示
void outputPS(LISTP p, FILE* fp) {
  while (p != NULL) {
    fprintf(fp, "newpath\n");
    fprintf(fp, "%lf %lf %lf setrgbcolor\n", p->trg.R, p->trg.G, p->trg.B);
    fprintf(fp, "%lf %lf moveto\n", p->trg.x1, p->trg.y1);
    fprintf(fp, "%lf %lf lineto\n", p->trg.x2, p->trg.y2);
    fprintf(fp, "%lf %lf lineto\n", p->trg.x3, p->trg.y3);
    fprintf(fp, "closepath\n");
    fprintf(fp, "stroke\n\n");

    p = p->next;
  }
}

// リストのメモリ解放
void freeList(LISTP p) {
  if (p == NULL) return;

  freeList(p->next);
  free(p);
}


int main(int argc, char *argv[]) {
  FILE *file;
  if ((file = fopen(argv[1], "w")) == NULL) {
    perror("File Open Error");
    exit(EXIT_FAILURE);
  }

  // Nはコマンドライン引数で指定
  int N = atoi(argv[2]);

  srand((unsigned int)time(NULL));

  // N個の三角形を生成して線形リストに格納
  LISTP trgList = NULL;
  for(int i = 0; i < N; i++) appendList(&trgList);

  // psファイルへ出力
  fprintf(file, "%%!PS\n");
  outputPS(trgList, file);
  fprintf(file, "showpage\n");

  // 線形リストのメモリ解放
  freeList(trgList);

  fclose(file);

  return 0;
}
