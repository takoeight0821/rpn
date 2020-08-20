#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 次は、fgetsで読み込んだ文字列を繋いで一つの文字列（ソースコード）を作る
// こうしておくと、後々扱いやすい

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
    // sourceの領域を拡張する
    // reallocは確保した領域に第一引数の指す領域をコピーする
    // + 1 はヌル文字の分
    source = realloc(source, (strlen(source) + strlen(buf) + 1) * sizeof(char));

    // sourceの末尾にbufを追加
    strcat(source, buf);

    /* このプログラムの実行時間は極めて短く、ソースコードも極めて小さい（どんなに多く見積もっても1MBには達しないだろう）
     * よって、メモリの開放については考える必要はない。どちらにせよプロセスが終了した時点ですべてのメモリは開放される
     * つまり、23行目を以下のように書く必要はない
     * もちろん、丁寧にfreeしてもかまわない
     *  
     * char *new_source = realloc(source, (strlen(source) + strlen(buf) + 1) * sizeof(char));
     * if (new_source != source) free(source);
     * source = new_source;
     */
  }

  printf("source: %s\n", source);
  printf("length: %lu\n", strlen(source));
}

// > echo 'hoge' | ./rpn
// source: hoge
//
// length: 5 (最後に改行が含まれる)
// > echo 'qwertyuiopasdfghjklzxcvbnmqwertyuiophfiwobqbwyiocqyuoyioqfcbeicoyqwbociquwbefywq' | ./rpn
// source: qwertyuiopasdfghjklzxcvbnmqwertyuiophfiwobqbwyiocqyuoyioqfcbeicoyqwbociquwbefywq
//
// length: 81