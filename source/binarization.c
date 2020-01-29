#include<stdio.h>
#include<stdlib.h>
#include "binarization.h"
#include "calc.h"

// 二値化プログラム
int binarization(char *file_name_in, char *file_name_out, unsigned int border_line) {

	// ファイル宣言
	FILE *file_in;	// 変換元ファイル
	FILE *file_out;	// 変換後ファイル

	// read binary/write binary mode
	file_in = fopen(file_name_in, "rb");
	file_out = fopen(file_name_out, "wb");

	// ファイル存在確認
	if (file_in == NULL) {
		printf("指定されたファイルは存在しません\n");
		exit(EXIT_FAILURE);
	}


	// 画像形式確認
	if (getputc() != 'B' || getputc() != 'M') {
		printf("ファイル形式が違います\n");
		fclose(file_in);
		fclose(file_out);
		exit(EXIT_FAILURE);
	}

	// ファイルサイズを取得
	unsigned int file_size = getputc() + getputc() * 256 + getputc() * 65536 + getputc() * 4096;
	printf("file size: %d \n", file_size);

	// 位置指定子を画像データ位置情報まで移動
	for (int i = 0; i < 4; i++) {
		getputc();
	}

	// ファイルの先頭から画像データまでのバイト数を取得
	unsigned int file_data = getputc() + getputc() * 256 + getputc() * 65536 + getputc() * 4096;

	// 情報ヘッダサイズ
	for (int i = 0; i < 4; i++) {
		getputc();
	}

	// 画像サイズ取得
	int file_width = getputc() + getputc() * 256 + getputc() * 65536 + getputc() * 4096;
	int file_height = getputc() + getputc() * 256 + getputc() * 65536 + getputc() * 4096;

	printf("width: %d px\n", file_width);
	printf("height: %d px\n", file_height);

	// プレーン数
	for (int i = 0; i < 2; i++) {
		getputc();
	}

	// 色bit数取得
	int color_bit = getc(file_in) + getc(file_in) * 256;
	printf("color bit: %d\n", color_bit);
	putc(1,file_out);
	putc(0,file_out);

	unsigned int color_num = 1;
	for (int i = 0; i < color_bit; i++) {
		color_num *= 2;
	}
	printf("color num: %d\n", color_num);

	// 圧縮形式
	for (int i = 0; i < 4; i++) {
		getputc();
	}

	// 画像データサイズ
	unsigned int file_datasize = getc(file_in) + getc(file_in) * 256 + getc(file_in) * 65536 + getc(file_in) * 4096;
	printf("image data size: %d\n", file_datasize);
	file_datasize / 3;

	// 解像度　縦横
	for (int i = 0; i < 8; i++) {
		getputc();
	}

	// パレット数取得
	int file_pallet = getc(file_in) + getc(file_in) * 256 + getc(file_in) * 65536 + getc(file_in) * 4096;
	printf("pallet: %d\n", file_pallet);


	// 重要色数
	for (int i = 0; i < 4; i++) {
		getputc();
	}

	// パレットデータ
        putc(0,file_out);
        putc(0,file_out);
        putc(0,file_out);
        putc(0,file_out);

	putc(256,file_out);
        putc(256,file_out);
        putc(256,file_out);
        putc(0,file_out);


	// 画像データ位置まで移動
	for (int i = 0; i < file_data - 54; i++) {
		getputc();
	}

	// 二値化
	int byte_num;
	for (unsigned int i = 0; i < (file_size -  file_data) / 24; i++) {
		byte_num = 0;
		for (int j = 0; j < 7; j++){
			if (getc(file_in) + getc(file_in) + getc(file_in) >= color_num * border_line / 100)	// 白色
				byte_num += calc_power( 2, j);
		}
		putc(byte_num,file_out);
	}

	// close
	fclose(file_in);
	fclose(file_out);

	return 0;
}

/*
// ido形式　二値化プログラム
int binarization_ido(char *file_name_in, char *file_name_out, int border_line) {

	// ファイル宣言
	FILE *file_in;	// 変換元ファイル
	FILE *file_out;	// 変換後ファイル

	// read binary/write binary mode
	file_in = fopen(file_name_in, "rb");
	file_out = fopen(file_name_out, "wb");

	// ファイル存在確認
	if (file_in == NULL) {
		printf("指定されたファイルは存在しません\n");
		exit(EXIT_FAILURE);
	}

	// 画像形式確認
	if (getc(file_in) != 'B' || getc(file_in) != 'M') {
		printf("ファイル形式が違います\n");
		fclose(file_in);
		fclose(file_out);
		exit(EXIT_FAILURE);
	}

	// ImageDataOnly
	putc('I', file_out);
	putc('D', file_out);
	putc('O', file_out);

	// ファイルサイズを取得
	int file_size = getc(file_in) + getc(file_in) * 256 + getc(file_in) * 65536 + getc(file_in) * 4096;
	printf("file size: %d \n", file_size);

	// 位置指定子を画像データ位置情報まで移動
	for (int i = 0; i < 4; i++) {
		getputc();
	}

	// ファイルの先頭から画像データまでのバイト数を取得
	int file_data = getputc() + getputc() * 256 + getputc() * 65536 + getputc() * 4096;

	printf("image data: %d \n", file_data);

	// 情報ヘッダサイズ
	for (int i = 0; i < 4; i++) {
		getputc();
	}

	// 画像サイズ取得
	int file_width = getputc() + getputc() * 256 + getputc() * 65536 + getputc() * 4096;
	int file_height = getputc() + getputc() * 256 + getputc() * 65536 + getputc() * 4096;

	printf("width: %d px\n", file_width);
	printf("height: %d px\n", file_height);

	// プレーン数
	for (int i = 0; i < 2; i++) {
		getputc();
	}

	// 色bit数取得
	int color_bit = getputc() + getputc() * 256;
	printf("color bit: %d\n", color_bit);

	int color_num = 1;
	for (int i = 0; i < color_bit; i++) {
		color_num *= 2;
	}
	printf("color num: %d\n", color_num);

	// 圧縮形式
	for (int i = 0; i < 4; i++) {
		getputc();
	}

	// 画像データサイズ
	int file_datasize = getputc() + getputc() * 256 + getputc() * 65536 + getputc() * 4096;
	printf("image data size: %d\n", file_datasize);

	// 解像度　縦横
	for (int i = 0; i < 8; i++) {
		getputc();
	}

	// パレット数取得
	int file_pallet = getputc() + getputc() * 256 + getputc() * 65536 + getputc() * 4096;
	printf("pallet: %d", file_pallet);

	// 重要色数
	for (int i = 0; i < 4; i++) {
		getputc();
	}

	// 画像データ位置まで移動
	for (int i = 0; i < file_data - 54; i++) {
		getputc();
	}

	// 二値化
	for (int i = 0; i < file_datasize; i++) {
		if (getc(file_in) <= border_line)	// 黒色
			putc(0, file_out);
		else								// 白色
			putc(255, file_out);
	}

	// close
	fclose(file_in);
	fclose(file_out);

	return 0;
}
*/
