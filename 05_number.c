#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// スタックに積む値を整数にする

struct Stack
{
  int value;          // スタックに積まれた値
  struct Stack *next; // 次の要素へのポインタ
};

// プッシュ
struct Stack *push(int value, struct Stack *stack)
{
  struct Stack *new_stack = malloc(sizeof(struct Stack));
  new_stack->value = value;
  new_stack->next = stack;
  return new_stack;
}

// ポップ
struct Stack *pop(struct Stack *stack)
{
  return stack->next;
}

// 先頭の要素を取得
int peek(struct Stack *stack)
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

  // sourceを空白文字で区切り、スタックに積む
  char *tok = strtok(source, " \t\r\n");
  if (tok == NULL)
    return 1; // 入力が空ならエラー

  struct Stack *stack = push(atoi(tok), NULL);

  while ((tok = strtok(NULL, " \t\r\n")) != NULL)
  {
    // atoiで文字列を整数に変換する
    stack = push(atoi(tok), stack);
  }

  // スタックの出力
  printf("[");
  for (struct Stack *current = stack; current != NULL; current = current->next)
  {
    printf("%d", current->value);
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
