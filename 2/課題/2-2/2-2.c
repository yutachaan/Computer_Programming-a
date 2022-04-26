#include <stdio.h>
#include <stdlib.h>

// 文字列sの中に文字列tがいくつ含まれるのかをカウント
int count_string(char *s, char *t) {
  int ret = 0;

  // sを1文字ずつ見る
  for (int i = 0; s[i] != '\0'; i++) {
    int flag = 1; // s[i] + s[i + 1] + ... + s[i + size(t)]が文字列tと等しいか
    for (int j = 0; t[j] != '\0'; j++) {
      if (s[i + j] != t[j]) flag = 0;
    }

    // 等しかったらカウントアップ
    if (flag) ret++;
  }

  return ret;
}


int main(int argc, char *argv[]) {
  FILE *file;
  char buf[512];

  if ((file = fopen(argv[1], "r")) == NULL) exit(1);

  // 1行ずつ読み込んでそれぞれの出現回数をカウント
  int count_Alice = 0, count_wonder = 0, count_self = 0;
  while(fgets(buf,sizeof(buf), file) != NULL) {
    count_Alice += count_string(buf, "Alice");
    count_wonder += count_string(buf, "wonder");
    count_self += count_string(buf, "self");
  }

  fclose(file);

  printf("Alice: %d\n", count_Alice);
  printf("wonder: %d\n", count_wonder);
  printf("self: %d\n", count_self);
}
