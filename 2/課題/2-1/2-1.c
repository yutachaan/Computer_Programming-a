#include <stdio.h>
#include <stdlib.h>

#define BUFFER 512

// 文字列sの長さを返す
int size_s(char *s) {
  int ret = 0;

  // 文字列の最後には\0(ヌル文字)が入っているため，それが見つかるまでカウントアップ
  while (*s++ != '\0')ret++;

  return ret - 1;
}

// 文字列sをreverse
void reverse(char *s) {
  int size = size_s(s);

  // i文字目とsize-i-1文字目をswap (0-indexed)
  for (int i = 0; i < size / 2; i++) {
    char temp = s[i];
    s[i] = s[size - 1 - i];
    s[size - 1 - i] = temp;
  }

  return;
}


int main(int argc, char *argv[]) {
  FILE *file;
  char buf[BUFFER];

  if ((file = fopen(argv[1], "r")) == NULL) exit(1);

  // 1行ずつ読み込み，reverseして出力
  while(fgets(buf,sizeof(buf), file) != NULL) {
    reverse(buf);

    printf("%s", buf);
  }

  fclose(file);
}
