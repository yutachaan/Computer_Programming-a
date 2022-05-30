#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

// エラー処理を含めたmalloc()関数
void *MyMalloc(size_t size) {
  void *p;

  if ((p = malloc(size)) == NULL) {
    perror("Memory Allocation Error");
    exit(EXIT_FAILURE);
  }

  return p;
}

// 力まかせ法
void Naive(int filesize, char *text, char *pattern) {
  int count = 0, pattern_len = strlen(pattern);

  clock_t t1 = clock();
  for (int i = 0; i < filesize; i++) {
    if (strncmp(text + i, pattern, pattern_len) == 0) count++;
  }
  clock_t t2 = clock();

  printf("\"%s\" found %d times!\n", pattern, count);
  printf("Used CPU time: %.10f\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
}

// BM法
void BM(int filesize, char *text, char *pattern) {
  int count = 0, pattern_len = strlen(pattern);
  int skip[UCHAR_MAX]; // スキップテーブル

  clock_t t1 = clock();

  // スキップテーブルの作成
  for (int c = 0; c < UCHAR_MAX; c++) skip[c] = pattern_len;
  for (int i = 0; i < pattern_len; i++) skip[pattern[i]] = pattern_len - i - 1;

  int text_pos = pattern_len - 1, pattern_pos = pattern_len - 1;
  while (text_pos < filesize) {
    while (text[text_pos] == pattern[pattern_pos]) {
      if (pattern_pos == 0) count++;
      text_pos--;
      pattern_pos--;
    }

    if (skip[text[text_pos]] > pattern_len - 1 - pattern_pos) text_pos += skip[text[text_pos]];
    else text_pos += pattern_len - pattern_pos;

    pattern_pos = pattern_len - 1;
  }

  clock_t t2 = clock();

  printf("\"%s\" found %d times!\n", pattern, count);
  printf("Used CPU time: %.10f\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
}


int main(int argc, char *argv[]) {
  FILE *fp;
  if ((fp = fopen(argv[1], "r")) == NULL) {
    perror("File Open Error");
    exit(EXIT_FAILURE);
  }

  // ファイルサイズを測る
  fpos_t fsize;
  fseek(fp, 0, SEEK_END);
  fgetpos(fp, &fsize);
  fseek(fp, 0L, SEEK_SET);

  // ファイル全文を読みこむ
  char *text = (char *)MyMalloc(fsize * sizeof(char));
  fsize = fread(text, sizeof(char), fsize, fp);
  fclose(fp);

  char *pattern = argv[2];

  // 力まかせ法
  printf("Naive:\n");
  Naive(fsize, text, pattern);

  // BM法
  printf("BM:\n");
  BM(fsize, text, pattern);

  free(text);

  return 0;
}
