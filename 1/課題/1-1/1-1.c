#include <stdio.h>
#include <ctype.h>

int main() {
  int count[128] = {0};

  char c;
  while((c = getchar()) != EOF) {
    if (isprint(c)) {
      int cn = (unsigned char)c;
      count[cn]++;
    }
  }

  for (int i = 0; i <= 128; i++) {
    if (isprint(i)) printf("\'%c\' : %d\n", i, count[i]);
  }
}
