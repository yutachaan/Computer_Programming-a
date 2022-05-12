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

// ノードのメモリを確保し，値を代入
LISTP mallocNode(char *word) {
  LISTP p;

  // メモリ確保
  if ((p = (LISTP)malloc(sizeof(LIST))) == NULL) {
    printf("Memory Allocation Error\n");
    exit(EXIT_FAILURE);
  }

  // 値の代入
  strcpy(p->word, word);
  p->count = 1;
  p->next = NULL;

  return p;
}

// リストの末尾にノードを追加
LISTP appendList(LISTP head, char *word) {
  LISTP new, p = head;

  if (p == NULL) {
    p = mallocNode(word);
    return p;
  }

  if (strcmp(word, p->word) == 0) p->count++; // 等しい場合はカウントアップ
  else p->next = appendList(p->next, word);   // それ以外の場合は次の要素へ

  return p;
}

// リストの要素を順に表示
void printList(LISTP p) {
  int n = 1;
  while (p != NULL) {
    printf("%d: WORD: %s, COUNT: %d\n", n, p->word, p->count);

    p = p->next;
    n++;
  }

  return;
}

// リストのメモリ解放
void freeList(LISTP p) {
  if (p == NULL) return;

  freeList(p->next);
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
    for (int i = 0; i < count; i++) list = appendList(list, result[i]);
  }

  // 線形リストを順に出力
  printList(list);

  // メモリ解放
  freeList(list);

  fclose(file);
}
