#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
  int n = 0, len = strlen(pattern);

  clock_t t1 = clock();
  for (int i = 0; i < filesize; i++) {
    if (strncmp(text + i, pattern, len) == 0) n++;
  }
  clock_t t2 = clock();

  printf("\"%s\" found %d times!\n", pattern, n);
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
  Naive(fsize, text, pattern);

  free(text);

  return 0;
}
