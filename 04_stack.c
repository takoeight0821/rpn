#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ソースコードを空白区切りに分割し、スタックに入れていく

// スタックは単方向連結リストで実装できる

struct Stack
{
  char *value;        // スタックに積まれた値
  struct Stack *next; // 次の要素へのポインタ
};

// スタックを操作するための関数を定義する

// プッシュ
// 引数のstackを書き換えるのではなく、プッシュした新しいスタックを返す
// プッシュした要素以外は共通なので、メモリ効率は悪くない
struct Stack *push(char *value, struct Stack *stack)
{
  struct Stack *new_stack = malloc(sizeof(struct Stack));
  new_stack->value = value;
  new_stack->next = stack;
  return new_stack;
}

// ポップ
// 先頭の要素を除去したスタックを返す
struct Stack *pop(struct Stack *stack)
{
  return stack->next;
}

// 先頭の要素を取得
// 「ちらっと覗く」という意味のpeek
char *peek(struct Stack *stack)
{
  return stack->value;
}

int main(void)
{
  const size_t buf_max_len = 256;
  char buf[buf_max_len];

  // 標準入力から読み込んだ文字列
  char *source = calloc(buf_max_len, sizeof(char));

  // 標準入力を最大255文字ずつ読み込む
  while (fgets(buf, buf_max_len, stdin) != NULL)
  {
    source = realloc(source, (strlen(source) + strlen(buf) + 1) * sizeof(char));
    strcat(source, buf);
  }

  // 文字列を区切るにはstrtokを使う
  // 区切られた文字列を「トークン」と呼ぶからstrtok
  // 今回は空白文字で区切る（スペース、タブ、改行）
  // 最初のstrtokの呼び出しでは対象文字列の初期化を行う。今回はsourceで初期化
  char *tok = strtok(source, " \t\r\n");
  if (tok == NULL)
    return 1; // 入力が空ならエラー

  struct Stack *stack = push(tok, NULL);

  // 2回目以降のstrtokの呼び出しではNULLを渡す
  while ((tok = strtok(NULL, " \t\r\n")) != NULL)
  {
    stack = push(tok, stack);
  }

  // スタックの出力
  printf("[");
  for (struct Stack *current = stack; current != NULL; current = current->next)
  {
    printf("%s", current->value);
    if (current->next)
    {
      printf(" ");
    }
    else
    {
      printf("]\n");
    }
  }
}
