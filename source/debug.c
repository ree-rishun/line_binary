#include<stdio.h>
#include<stdlib.h>
#include"debug.h"

// デバッグ用バイナリ表示関数
int binary_print(char *file_name) {

	FILE *file = fopen(file_name, "rb");

	// ファイル存在確認
	if (file == NULL) {
		printf("指定されたファイルは存在しません\n");
		exit(EXIT_FAILURE);
	}

	int binary = 0;
	int cnt = 0;

	// 表示
	while (1) {

		if (cnt % 16 == 0)
			printf("\n%06d ", cnt);

		binary = getc(file);

		if (binary == -1)
			break;

		if (cnt/16 == 10)
			break;

		printf("%c ", binary);
		cnt++;
	}

	printf("\n");

	return 0;
}

// ファイル比較関数
int binary_compare(char *file_name_1, char *file_name_2){

	FILE *file1 = fopen(file_name_1, "rb");
	FILE *file2 = fopen(file_name_2, "rb");

	// ファイル存在確認
	if (file1 == NULL || file2 == NULL) {
		printf("指定されたファイルは存在しません\n");
		exit(EXIT_FAILURE);
	}

	int binary1 = 0;
	int binary2 = 0;
	int diff_flg = 0;

	while (binary1 != -1 && binary2 != -1) {

		binary1 = getc(file1);
		binary2 = getc(file2);

		if (binary1 != binary2) {
			diff_flg = 1;
			break;
		}
	}

	return diff_flg;
}

// bmp パラメータ取得
int bmp_param(char *file_name){
	// ファイル宣言
        FILE *file;  // 変換元ファイル

        // read binary/write binary mode
        file = fopen(file_name, "rb");

        // ファイル存在確認
        if (file == NULL) {
                printf("指定されたファイルは存在しません\n");
                exit(EXIT_FAILURE);
        }

	// 画像形式確認
        if (getc(file) != 'B' || getc(file) != 'M') {
                printf("ファイル形式が違います\n");
                fclose(file);
                exit(EXIT_FAILURE);
        }

        // ファイルサイズを取得
        unsigned int file_size = getc(file) + getc(file) * 256 + getc(file) * 65536 + getc(file) * 4096;
        printf("file size: %d \n", file_size);

        // 位置指定子を画像データ位置情報まで移動
        for (int i = 0; i < 4; i++) {
                getc(file);
        }

        // ファイルの先頭から画像データまでのバイト数を取得
        unsigned int file_data = getc(file) + getc(file) * 256 + getc(file) * 65536 + getc(file) * 4096;

        // 情報ヘッダサイズ
        for (int i = 0; i < 4; i++) {
                getc(file);
        }

        // 画像サイズ取得
        int file_width = getc(file) + getc(file) * 256 + getc(file) * 65536 + getc(file) * 4096;
        int file_height = getc(file) + getc(file) * 256 + getc(file) * 65536 + getc(file) * 4096;

        printf("width: %d px\n", file_width);
	printf("height: %d px\n", file_height);

        // プレーン数
        for (int i = 0; i < 2; i++) {
                getc(file);
        }

        // 色bit数取得
        int color_bit = getc(file) + getc(file) * 256;
        printf("color bit: %d\n", color_bit);

        unsigned int color_num = 1;
        for (int i = 0; i < color_bit; i++) {
                color_num *= 2;
        }
        printf("color num: %d\n", color_num);

        // 圧縮形式
        for (int i = 0; i < 4; i++) {
                getc(file);
        }

        // 画像データサイズ
        unsigned int file_datasize = getc(file) + getc(file) * 256 + getc(file) * 65536 + getc(file) * 4096;
        printf("image data size: %d\n", file_datasize);
        file_datasize / 3;

        // 解像度　縦横
        for (int i = 0; i < 8; i++) {
                getc(file);
        }

        // パレット数取得
        int file_pallet = getc(file) + getc(file) * 256 + getc(file) * 65536 + getc(file) * 4096;
        printf("pallet: %d\n", file_pallet);


        // 重要色数
        for (int i = 0; i < 4; i++) {
                getc(file);
        }

        // close
        fclose(file);

        return 0;
}
