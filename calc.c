#include<stdio.h>
#include<stdlib.h>
#include "calc.h"

// 累乗関数 xのy乗
int calc_power(int x,int y){
	int ans = 1;
	for(int i = 0; i < y; i++){
		ans *= x;
	}
	return ans;
}
