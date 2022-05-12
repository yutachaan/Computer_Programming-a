#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 256
#define HASHSIZE 8191


// ノードの定義
typedef struct list {
  char word[STRLEN];  // 単語(key)
  int count;          // 単語の出現回数
  struct list *next;  // 次の要素へのポインタ
} LIST, *LISTP;

// リストの末尾にノードを追加
void appendList(LIST **head, char *word) {
  LISTP new, p = *head, prev;

  // 追加する要素のメモリ確保
  if ((new = (LISTP)malloc(sizeof(LIST))) == NULL) {
    printf("Memory Allocation Error\n");
    exit(EXIT_FAILURE);
  }

  // 値を代入
  strcpy(new->word, word);
  new->count = 1;
  new->next = NULL;

  // 末尾までポインタを移動
  while (p != NULL) {
    prev = p;
    p = p->next;
  }

  if (p == *head) *head = new; // 追加する位置が先頭の場合，そのまま先頭に設定
  else prev->next = new;     // それ以外の場合は今の末尾の要素の次に追加

  return;
}

// リストの要素を順に表示
void printList(LIST **head) {
  LISTP p = *head;

  int n = 1;
  while (p != NULL) {
    printf("%d: WORD: %s, COUNT: %d\n", n, p->word, p->count);

    p = p->next;
    n++;
  }

  return;
}

// リストのメモリ解放
void freeList(LIST **head) {
  LISTP p = *head;

  if (p == NULL) return;

  freeList(&p->next);
  free(p);

  return;
}


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
  LISTP list = NULL;
  while(fgets(str,sizeof(str), file) != NULL) {
    // 文字列を分割
    char *result[STRLEN];
    int count = split(str, " \n", result); // 空白と改行コードでsplit

    // 線形リストに追加
    for (int i = 0; i < count; i++) appendList(&list, result[i]);
  }

  // 線形リストを順に出力
  printList(&list);

  // メモリ解放
  freeList(&list);

  fclose(file);
}
