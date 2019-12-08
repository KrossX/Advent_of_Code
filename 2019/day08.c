/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <stdlib.h>
#include <stdio.h>

#define WIDTH 25
#define HEIGHT 6

//15000 pixels, 25*6 resolution, 100 layers, 150 pixels per layer

char *input;

void read_input(void)
{
	FILE *file = fopen("day08_data.c", "rb");
	input = malloc(15000);
	fread(input, 1, 15000, file);
	fclose(file);
}

void part1(void)
{
	char *buf;
	int i, j;
	int layer_few0[10] = {999};
	
	read_input();
	buf = input;

	for(i = 0; i < 100; i++) {
		int layer_cur[10] = {0};
		
		for(j = 0; j < 150; j++)
			layer_cur[*buf++ - '0']++;
		
		if(layer_cur[0] < layer_few0[0])
			memcpy(layer_few0, layer_cur, 10 * 4);
	}
	
	printf("Min 0: %d, 1s: %d, 2s: %d, Value: %d\n", 
		layer_few0[0], layer_few0[1], layer_few0[2], layer_few0[1] * layer_few0[2]);
}


int main(void)
{
	char image[150];
	int i, j;
	
	read_input();
	
	for(j = 0; j < 150; j++) {
		char pixel;
		
		for(i = 0; i < 100; i++) {
			char p = input[i*150 + j];
			if(p == '2') continue;
			pixel = p; break;
		}
		
		image[j] = pixel;
	}
	
	for(i = 0; i < 6; i++) {
		for(j = 0; j < 25; j++) {
			switch(image[i*25 + j]) {
			case '0': printf(" "); break;
			case '1': printf("#"); break;
			case '2': printf("+"); break;
			default: printf("."); break;
			}
		}
		printf("\n");
	}

	return 0;
}
