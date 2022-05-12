#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 256


// ノードの定義
typedef struct node {
  char word[STRLEN];  // 単語(key)
  int count;          // 単語の出現回数
  struct node *left;  // 左部分木
  struct node *right; // 右部分木
} NODE, *BTREE;

// ノードのメモリを確保し，値を代入
BTREE mallocNode(char *word) {
  BTREE p;

  // メモリ確保
  if ((p = (BTREE)malloc(sizeof(NODE))) == NULL) {
    printf("Memory Allocation Error\n");
    exit(EXIT_FAILURE);
  }

  // 値の代入
  strcpy(p->word, word);
  p->count = 1;
  p->left = p->right = NULL;

  return p;
}

// 2分木にノードを挿入
BTREE insertNode(BTREE p, char *word) {
  // pが空なら， rootを挿入
  if (p == NULL) {
    p = mallocNode(word);
    return p;
  }

  int cmp = strcmp(word, p->word);
  if (cmp <= -1) p->left = insertNode(p->left, word);       // 追加したいwordのほうが辞書順で小さい場合は左部分木に追加
  else if (cmp >= 1) p->right = insertNode(p->right, word); // 大きい場合は右部分木に追加
  else p->count++;                                          // 等しい場合はカウントアップ

  return p;
}

// 2分木を表示
int n; // 通し番号
void printBtree(BTREE p) {
  if (p == NULL) return;

  printBtree(p->left);
  printf("%d: WORD: %s, COUNT: %d\n", ++n, p->word, p->count);
  printBtree(p->right);
}

// 2分木のメモリ解放
void freeBtree(BTREE p) {
  if (p == NULL) return;

  freeBtree(p->left);
  freeBtree(p->right);
  free(p);
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
  BTREE btree = NULL;
  while(fgets(str,sizeof(str), file) != NULL) {
    // 文字列を分割
    char *result[STRLEN];
    int count = split(str, " \n", result); // 空白と改行コードでsplit

    // 2分木に挿入
    for (int i = 0; i < count; i++) btree = insertNode(btree, result[i]);
  }

  // 2分木を出力
  printBtree(btree);

  // メモリ解放
  freeBtree(btree);

  fclose(file);
}
