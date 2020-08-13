#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ソースコードを空白区切りに分割する

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

  printf("token: %s\n", tok);

  // 2回目以降のstrtokの呼び出しではNULLを渡す
  while ((tok = strtok(NULL, " \t\r\n")) != NULL)
  {
    printf("token: %s\n", tok);
  }
}
