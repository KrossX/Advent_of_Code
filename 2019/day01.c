/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <stdio.h>
#include "day01_data.c"

int function(int in)
{
	return (in / 3) - 2;
}

void test(int in)
{
	printf("Test %d: %d\n", in, function(in));
}

int main(void)
{
	int *number = input;
	int total = 0;
	int total2 = 0;
	
	test(12);
	test(14);
	test(1969);
	test(100756);
	
	while(*number) { 
		int fuel = function(*number++);
		total += fuel;
		total2 += fuel;
		
		while(1) {
			fuel = function(fuel);
			if(fuel > 0) total2 += fuel;
			else break;
		}
	}
	
	printf("Result1: %d, %08X\n", total, total);
	printf("Result2: %d, %08X\n", total2, total2);
	
	return 0;
}