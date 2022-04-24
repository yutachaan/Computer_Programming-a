#include <stdio.h>
#include <ctype.h>

int main() {
  int count[128] = {0};

  char c;
  while((c = getchar()) != EOF) {
    if (!isprint(c)) continue;

    int n = (unsigned char)c;
    count[n]++;
  }

  for (int i = 0; i <= 128; i++) {
    if (!isprint(i)) continue;

    printf("\'%c\' : %d\n", i, count[i]);
  }
}
