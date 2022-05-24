/*
  三角形のデータをN個ランダムに作成して線形リストに保持し，それらのデータをPostscript形式のファイルへ出力する

  @author: Yuta Sato

  @version: gcc (Homebrew GCC 11.3.0_1) 11.3.0

  % gcc -o 5-1 5-1.c
  % ./5-1 [出力ファイル名] [作成する三角形の数]
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 三角形の3点の座標v1=(x1, y1), v2=(x2, y2), v3=(x3, y3)と色(R, G, B)のデータを持つ構造体
typedef struct Triangle {
  double x1, y1, x2, y2, x3, y3, R, G, B;
} TRG, *TRGP;

// 三角形のデータを格納する線形リストの構造体
typedef struct node {
  TRG trg;
  struct node *next;
} NODE, *NODEP;


// 閉区間[min_rand, max_rand]から実数の乱数を生成して返す
double GenerateRand(double min_rand, double max_rand) {
  return min_rand + (double)(rand()) / ((double)(RAND_MAX / (max_rand - min_rand)));
}

// 3点のx座標とy座標の値が閉区間[coord_min, coord_max]内の乱数値であるようなTriangleの実体を生成して返す
TRG GenerateTRG(double coord_min, double coord_max) {
  TRG trg;

  trg.x1 = GenerateRand(coord_min, coord_max);
  trg.x2 = GenerateRand(coord_min, coord_max);
  trg.y1 = GenerateRand(coord_min, coord_max);
  trg.y2 = GenerateRand(coord_min, coord_max);
  trg.x3 = GenerateRand(coord_min, coord_max);
  trg.y3 = GenerateRand(coord_min, coord_max);
  trg.R  = GenerateRand(0, 1);
  trg.G  = GenerateRand(0, 1);
  trg.B  = GenerateRand(0, 1);

  return trg;
}


// エラー処理を含めたmalloc()関数
void *MyMalloc(size_t size) {
  void *p;

  if ((p = malloc(size)) == NULL) {
    perror("Memory Allocation Error");
    exit(EXIT_FAILURE);
  }

  return p;
}

// 追加するノードのメモリ領域を確保して値を代入
NODEP MallocNode(TRG trg) {
  NODEP p = (NODEP)MyMalloc(sizeof(NODE));

  p->trg = trg;
  p->next = NULL;

  return p;
}

// 三角形のデータtrgを持つノードをリストの末尾に追加
NODEP AppendNodeToList(NODEP p, TRG trg) {
  // 末尾まできたらノードを追加
  if (p == NULL) {
    p = MallocNode(trg);
    return p;
  }

  // AppendNodeToList()を再帰的に呼び出して末尾まで移動
  p->next = AppendNodeToList(p->next, trg);

  return p;
}

// リストのもつ三角形のデータを順にPostScript形式に変換しファイルに出力
void OutputToPS(NODEP p, FILE *fp) {
  while (p != NULL) {
    // 描画セットの開始
    fprintf(fp, "newpath\n");

    // 描画に用いる色の設定
    fprintf(fp, "%lf %lf %lf setrgbcolor\n", p->trg.R, p->trg.G, p->trg.B);

    // 3点を結ぶように線を引く
    fprintf(fp, "%lf %lf moveto\n", p->trg.x1, p->trg.y1);
    fprintf(fp, "%lf %lf lineto\n", p->trg.x2, p->trg.y2);
    fprintf(fp, "%lf %lf lineto\n", p->trg.x3, p->trg.y3);
    fprintf(fp, "closepath\n");

    // 描画セットの実行
    fprintf(fp, "stroke\n\n");

    p = p->next;
  }
}

// リストのメモリを解放
void FreeList(NODEP p) {
  if (p == NULL) return;

  FreeList(p->next);
  free(p);
}


int main(int argc, char *argv[]) {
  FILE *fp;
  if ((fp = fopen(argv[1], "w")) == NULL) {
    perror("File Open Error");
    exit(EXIT_FAILURE);
  }

  int N = atoi(argv[2]); // 作成する三角形の数

  srand((unsigned int)time(NULL));

  // N個の三角形を生成して順に線形リストに格納
  NODEP trgList = NULL;
  for(int i = 0; i < N; i++) trgList = AppendNodeToList(trgList, GenerateTRG(50, 550));

  // PostScript形式のファイルへ出力
  fprintf(fp, "%%!PS\n");    // PostScriptファイルの識別子
  OutputToPS(trgList, fp);   // 各三角形を描画
  fprintf(fp, "showpage\n"); // ページ全体の描画

  FreeList(trgList);

  fclose(fp);

  return 0;
}
