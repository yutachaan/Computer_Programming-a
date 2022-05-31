/*
  力まかせ法とBM法による文字列検索の速度比較

  @author: Yuta Sato

  @version: gcc (Homebrew GCC 11.3.0_1) 11.3.0

  % gcc -o 6-1 6-1.c
  % ./6-1 [入力ファイル名] [検索文字列]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

// エラー処理を含めたfopen()関数
FILE *MyFopen(char *filename, char *mode) {
  FILE *fp;

  if ((fp = fopen(filename, mode)) == NULL) {
    perror("File Open Error");
    exit(EXIT_FAILURE);
  }

  return fp;
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


// 力まかせ法による文字列検索をおこない， textに含まれるpatternの個数を調べる．また，文字列検索にかかった時間を出力する．
void BruteForce(int filesize, char *text, char *pattern) {
  int count = 0, len_pattern = strlen(pattern);

  clock_t t1 = clock(); // 計測開始

  // 先頭から探索し， text[i, ..., i+len_pattern]とpatternが一致したらカウントアップ
  for (int i = 0; i < filesize; i++) {
    if (strncmp(text + i, pattern, len_pattern) == 0) count++;
  }

  clock_t t2 = clock(); // 計測終了

  printf("\"%s\" found %d times!\n", pattern, count);
  printf("Used CPU time: %.10f\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
}

// BM法による文字列検索をおこない， textに含まれるpatternの個数を調べる．また，文字列検索にかかった時間を出力する．
void BM(int filesize, char *text, char *pattern) {
  int count = 0, len_pattern = strlen(pattern);
  int skip[UCHAR_MAX]; // スキップテーブル

  clock_t t1 = clock(); // 計測開始

  // スキップテーブルの作成
  for (int c = 0; c < UCHAR_MAX;   c++) skip[c]          = len_pattern;         // パターン内に存在しない場合
  for (int i = 0; i < len_pattern; i++) skip[pattern[i]] = len_pattern - i - 1; // パターン内に存在する場合(pattern内に同じ文字が複数存在する場合は後ろ側の位置に合わせる)

  int tpos = len_pattern - 1, ppos = len_pattern - 1; // tpos: テキストの比較位置， ppos: パターンの比較位置． それぞれパターンの末尾のインデックスにする
  while (tpos < filesize) {
    while (text[tpos] == pattern[ppos]) {
      // パターンの先頭の文字までテキストの文字が一致した場合
      if (ppos == 0) {
        count++;
        break;
      }

      // 比較位置を１文字前に移動
      tpos--;
      ppos--;
    }

    if (skip[text[tpos]] > len_pattern - 1 - ppos) tpos += skip[text[tpos]]; // 次回の比較位置が前回の比較開始位置よりも後ろに移動する場合はスキップテーブルに従い移動
    else tpos += len_pattern - ppos;                                         // 前に移動してしまう場合は前回の比較開始位置から1文字だけスキップ

    ppos = len_pattern - 1;
  }

  clock_t t2 = clock(); // 計測終了

  printf("\"%s\" found %d times!\n", pattern, count);
  printf("Used CPU time: %.10f\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
}


int main(int argc, char *argv[]) {
  FILE *fp = MyFopen(argv[1], "r");

  // ファイルサイズを計測する
  fpos_t filesize;
  fseek(fp, 0, SEEK_END);
  fgetpos(fp, &filesize);
  fseek(fp, 0L, SEEK_SET);

  // ファイル全文を読みこむ
  char *text = (char *)MyMalloc(filesize * sizeof(char));
  filesize = fread(text, sizeof(char), filesize, fp);
  fclose(fp);

  char *pattern = argv[2];

  // 力まかせ法による文字列検索
  printf("Brute Force Method:\n");
  BruteForce(filesize, text, pattern);
  printf("\n");

  // BM法による文字列検索
  printf("BM Method:\n");
  BM(filesize, text, pattern);

  free(text);

  return 0;
}
