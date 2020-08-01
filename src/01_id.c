#include <stdio.h>
#include <stdbool.h>

// まずはstdinをstdoutにオウム返しするプログラムを作る
// 「文字列を読み込んで、文字列を出力する」プログラムはオウム返しプログラムから始めるといい。

int main(void)
{
  // 256文字のバッファを用意。fgetsで使う
  // バッファの最大長のような定数は、constや#defineで宣言しておくと変えやすくて便利
  const int buf_max_len = 256;
  char buf[buf_max_len];

  // 標準入力を最大255文字ずつ読み込む

  // fgetsは読み込める入力が無いとNULLを返す
  // このwhile文は「読めるだけ読んで、読めなくなったらやめる」という意味になる
  while (fgets(buf, buf_max_len, stdin) != NULL)
  {
    printf("%s", buf);
  }
}

// > echo 'hoge' | ./rpn
// hoge
// > echo とても長い文字列 | ./rpn
// とても長い文字列       バッファオーバーフローしない！
// > echo 'あいうえお' | ./rpn
// あいうえお           日本語もちゃんと扱える！