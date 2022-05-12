#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 256


// 文字列を分割してresultに格納し， 分割後の文字列の個数を返す(s: 対象文字列， separator: 区切り文字の配列， result: 結果を格納する文字列配列，)
int split(char *s, const char *separator, char **result) {
    if (s == NULL) return 0;

    int count = 0;

    // 文字列を分割してカウント
    char *p = strtok(s, separator);
    while (p != NULL) {
      result[count] = p;
      count++;

      p = strtok(NULL, separator);
    }

    return count;
}


int main(int argc, char *argv[]) {
  FILE *file;
  if ((file = fopen(argv[1], "r")) == NULL) {
    printf("File Open Error: %s\n", file);
    exit(EXIT_FAILURE);
  }

  char str[STRLEN];
  while(fgets(str,sizeof(str), file) != NULL) {
    // 文字列を分割
    char *result[STRLEN];
    int count = split(str, " \n", result); // 空白と改行コードでsplit
  }

  fclose(file);
}
