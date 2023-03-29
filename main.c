#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // 引数が1つでなければエラーメッセージ
    if (argc != 2) {
        printf("usage: henrin filename\n");
        return 1;
    }

    // 引数で与えられたバイナリを読み込む
    char* filename = argv[1];
    FILE* binary;
    binary = fopen(filename, "rb");

    if (binary == NULL) {
        printf("%s ファイルを開けません\n", filename);
        exit(1);
    }

    int count;
    char c;
    // ファイルから1文字ずつ読み取って表示する
    while ((c = fgetc(binary)) != EOF) {
        // ascii文字で表せない場合は '.'に変換
        char ascii;
        if (isascii(c)) {
            ascii = c;
        } else {
            ascii = '.';
        }

        // 改行の場合は ' '(空白)に変換
        if (ascii == '\n') {
            ascii = ' ';
        }

        // 2進数に変換
        char bin[9];
        for (int i = 0; i < 8; i++) {
            bin[i] = ((c >> (7 - i)) & 1) ? '1' : '0';
        }
        bin[8] = '\0';

        // 行数: 16進数 2進数  ascii文字 と出力
        printf("%08x: %02x %s %c\n", count, c, bin, ascii);

        // カウントアップ
        count++;
    }

    fclose(binary);
}
