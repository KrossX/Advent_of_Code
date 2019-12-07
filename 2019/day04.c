/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <stdio.h>

//input 193651-649729

int validate1(int range_min, int range_max)
{
	int x, i;
	int counter = 0;
	
	for(x = range_min; x < range_max; x++)
	{
		int div = 100000;
		int has_double = 0;
		int decreased = 0;
		int prev = 0;
		int num = x;
		
		for(i = 0; i < 6; i++) {
			int digit = num / div;

			num -= digit * div;
			div /= 10;

			if(digit == prev) has_double = 1;
			if(digit < prev) decreased = 1;
			
			prev = digit;
		}
		
		if(has_double && !decreased) {
			counter++;
		}
	}
	
	return counter;
}

int validate2(int range_min, int range_max)
{
	int x, i;
	int counter = 0;
	
	for(x = range_min; x < range_max; x++)
	{
		int dcount[10] = {0};
		int digit[6] = {0};
		int div = 100000;
		int has_double = 0;
		int decreased = 0;
		int prev = 0;
		int num = x;
		
		for(i = 0; i < 6; i++) {
			int d = num / div;
			dcount[d]++;

			num -= d * div;
			div /= 10;

			if(d == prev) has_double = 1;
			if(d < prev) decreased = 1;
			
			prev = d;
		}
		
		if(has_double && !decreased) {
			int check_double = 0;
			
			for(i = 0; i < 10; i++)
				if(dcount[i] == 2) check_double = 1;
			
			if(check_double)
				counter++;
		}
	}
	
	return counter;
}


int main(void)
{
	int valid_count;

	valid_count = validate1(193651, 649729);
	printf("Valid passwords found: %d (part1)\n", valid_count);
	
	valid_count = validate2(193651, 649729);
	printf("Valid passwords found: %d (part2)\n", valid_count);
}