#include <stdio.h>
#include <stdlib.h>
#include "binarization.h"
#include "debug.h"
// #include "route.h"

// 変換元bmp画像ファイルパス
#define BMP_FILE "img/image.bmp"
// 変換後bmp画像ファイルパス
#define BOW_FILE "img/mono.bmp"
// 二値化用閾値
#define BDR_LINE 0.5

// メイン関数
int main() {

	//system("raspistill -e bmp -w 720 -h 480 -o image.bmp");
	//binarization(BMP_FILE, BOW_FILE, BDR_LINE);

	//binary_print(BMP_FILE);

	bmp_param(BOW_FILE);

	return 0;

}

