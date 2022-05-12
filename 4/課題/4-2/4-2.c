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

  // メモリ確保
  if ((new = (LISTP)malloc(sizeof(LIST))) == NULL) {
    printf("Memory Allocation Error\n");
    exit(EXIT_FAILURE);
  }

  // 値の代入
  strcpy(new->word, word);
  new->count = 1;
  new->next = NULL;

  // まだ要素が1つもないなら先頭に追加
  if (p == NULL) {
    *head = new;
    return;
  }

  // 末尾までポインタを移動
  while (p != NULL) {
    // すでに登録されているならカウントアップ
    if (strcmp(p->word, word) == 0) {
      p->count++;
      return;
    }

    prev = p;
    p = p->next;
  }

  // 末尾の要素の次の位置に追加
  prev->next = new;

  return;
}

// リストの要素を順に表示
void printList(LIST **head, int *n) {
  LISTP p = *head;

  while (p != NULL) {
    printf("%d: WORD: %s, COUNT: %d\n", *n, p->word, p->count);

    p = p->next;
    (*n)++;
  }

  return;
}

// リストのメモリ解放
void freeList(LIST **head) {
  LISTP p = *head;

  if (p == NULL) return;

  freeList(&(p->next));
  free(p);

  return;
}


// ハッシュ関数
int hash(char *str) {
  int h = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    h = (h * 137 + str[i]) % HASHSIZE;
  }

  return h;
}

// ハッシュテーブルに値を追加
void insertHash(LIST **hash_table, char *word) {
  int h = hash(word);

  if (h >= HASHSIZE) {
    printf("Hash Value Error\n");
    exit(EXIT_FAILURE);
  }

  // ハッシュ値の位置のリストに追加
  appendList(&hash_table[h], word);

  return;
}

// ハッシュ表の先頭から要素を表示
void printHash(LIST **hash_table) {
  int n = 1;

  for (int i = 0; i < HASHSIZE; i++) {
    printList(&hash_table[i], &n);
  }

  return;
}

// ハッシュ表のメモリ解放
void freeHash(LIST **hash_table) {
  for (int i = 0; i < HASHSIZE; i++) {
    freeList(&hash_table[i]);
  }

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

  // ハッシュテーブルを初期化
  LISTP hash_table[HASHSIZE];
  for (int i = 0; i < HASHSIZE; i++) hash_table[i] = NULL;

  char str[STRLEN];
  while(fgets(str,sizeof(str), file) != NULL) {
    // 文字列を分割
    char *result[STRLEN];
    int count = split(str, " \n", result); // 空白と改行コードでsplit

    // 線形リストに追加
    for (int i = 0; i < count; i++) insertHash(hash_table, result[i]);
  }

  // 線形リストを順に出力
  printHash(hash_table);

  // メモリ解放
  freeHash(hash_table);

  fclose(file);
}
