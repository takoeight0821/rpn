#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// RPN電卓
// +, -, *, /, p

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

struct Stack *eval(char *tok, struct Stack *stack)
{
  if (strcmp(tok, "+") == 0)
  {
    int y = peek(stack);
    stack = pop(stack);
    int x = peek(stack);
    stack = pop(stack);
    return push(x + y, stack);
  }

  if (strcmp(tok, "-") == 0)
  {
    int y = peek(stack);
    stack = pop(stack);
    int x = peek(stack);
    stack = pop(stack);
    return push(x - y, stack);
  }

  if (strcmp(tok, "*") == 0)
  {
    int y = peek(stack);
    stack = pop(stack);
    int x = peek(stack);
    stack = pop(stack);
    return push(x * y, stack);
  }

  if (strcmp(tok, "/") == 0)
  {
    int y = peek(stack);
    stack = pop(stack);
    int x = peek(stack);
    stack = pop(stack);
    return push(x / y, stack);
  }

  if (strcmp(tok, "p") == 0)
  {
    printf("%d", peek(stack));
    return stack;
  }

  if (strcmp(tok, "d") == 0)
  {
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
    return stack;
  }

  if (atoi(tok))
  {
    return push(atoi(tok), stack);
  }

  fprintf(stderr, "Error: invalid instruction '%s'\n", tok);
  exit(1);
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

  struct Stack *stack = eval(tok, NULL);

  while ((tok = strtok(NULL, " \t\r\n")) != NULL)
  {
    stack = eval(tok, stack);
  }
}
