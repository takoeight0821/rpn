#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 入力されたソースコードをトークンに分割する

// トークンの定義

// トークンは整数か演算子かカッコかアルファベットの列
enum TokenTag
{
  TINT,   // 整数リテラル
  TIDENT, // 演算子かアルファベットの列
};

// トークン列を連結リストとして定義する
struct Token
{
  enum TokenTag tag;
  int integer;
  char *ident;
  struct Token *next;
};

// 文字列をreallocして連結する関数
char *realloc_concat(char *s1, char *s2)
{
  s1 = realloc(s1, (strlen(s1) + strlen(s2) + 1) * sizeof(char));
  return strcat(s1, s2);
}

// 文字列s2が文字列s1から始まるか否か
bool start_with(char* s1, char *s2) {
  while (*s1 != '\0' && *s2 != '\0') {
    if (*s1 == *s2) {
      s1++;
      s2++;
    } else {
      return false;
    }
  }
  return true;
}

struct Token* lex(char* input) {
  static char* src;
  if (input != NULL) {
    src = input;
  }

  if (src == NULL) {
    return NULL;
  }

  // 空白文字は読み飛ばす
  // strchrは、文字列にある文字が含まれるかどうかを判定する
  while (strchr(" \t\n\r", *src)) {
    src++;
  }

  if (strchr("+", *src)) {
    src++; // 一文字読み進める
    struct Token* token = malloc(sizeof(struct Token));
    token->tag = TIDENT;
    token->ident = "+";
    token->next = lex(NULL);
    return token;
  }

  if (strchr("-", *src)) {
    src++;
    struct Token* token = malloc(sizeof(struct Token));
    token->tag = TIDENT;
    token->ident = "-";
    token->next = lex(NULL);
    return token;
  }

  if (strchr("*", *src)) {
    src++;
    struct Token* token = malloc(sizeof(struct Token));
    token->tag = TIDENT;
    token->ident = "-";
    token->next = lex(NULL);
    return token;
  }

  if (strchr("/", *src)) {
    src++;
    struct Token* token = malloc(sizeof(struct Token));
    token->tag = TIDENT;
    token->ident = "-";
    token->next = lex(NULL);
    return token;
  }

  // TODO: isdigitを使うべき？
  if (strchr("0123456789", *src)) {
    struct Token* token = malloc(sizeof(struct Token));
    token->tag = TINT;
    token->integer = 0;
    while (strchr("0123456789", *src)) {
      token->integer = token->integer * 10 + (*src - '0');
      src++;
    }
    token->next = lex(NULL);
    return token;
  }

  return NULL;
}

int main(void)
{
  const size_t buf_max_len = 256;
  char buf[buf_max_len];

  // ヒープ領域にソースコード用の領域を確保する
  // calloc関数で確保したメモリは0クリアされている（つまり空文字列）
  char *source = calloc(buf_max_len, sizeof(char));

  // 標準入力を最大255文字ずつ読み込む
  while (fgets(buf, buf_max_len, stdin) != NULL)
  {
    realloc_concat(source, buf);
  }

  printf("source: %s\n", source);
  printf("length: %lu\n", strlen(source));

  // 字句解析
  struct Token* tokens = lex(source);

  for (struct Token *token = tokens; token != NULL; token = token->next) {
    switch (token->tag)
    {
    case TINT:
      printf("TINT %d\n", token->integer);
      break;
    case TIDENT:
      printf("TIDENT %s\n", token->ident);
      break;
    }
  }
}
