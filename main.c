#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char toAscii(int c);
void toBinary(char* bin, int c);

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
    int c;
    // ファイルから1文字ずつ読み取って表示する
    while ((c = fgetc(binary)) != EOF) {
        // ascii文字に変換
        char ascii;
        ascii = toAscii(c);

        // 2進数に変換
        char bin[9];
        toBinary(bin, c);

        // 行数: 16進数 2進数 ascii文字 と出力
        printf("%08x: %02x %s %c\n", count, c, bin, ascii);

        // カウントアップ
        count++;
    }

    fclose(binary);
}

// ascii文字変換
char toAscii(int c) {
    // 改行の場合は ' '(空白)に変換
    if (c == '\n') {
        return ' ';
    }

    // ascii文字で表せない場合は '.'に変換
    if (isascii(c)) {
        return (char)c;
    } else {
        return '.';
    }
}

// 2進数変換
void toBinary(char* bin, int c) {
    if (sizeof(bin) != 8) {
        printf("sizeof(bin): %ld", sizeof(bin));
        printf("toBinary failed\n");
        exit(1);
    }
    for (int i = 7; i >= 0; i--) {
        bin[7 - i] = (c & (1 << i)) ? '1' : '0';
    }
    bin[8] = '\0';
}
