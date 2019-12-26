/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <stdlib.h>
#include <stdio.h>
#include "day16_data.c"

int pattern[4] = {0,1,0,-1};

void fft(char *data, int length, int offset) {
	int phase = 0;

	while(1) {
		int idx = offset;
		int i, n;

		while(idx < length/2) {
			i = idx; n = 0;
			
			while(i < length) {
				int nn = data[i] - '0';
				int pp = pattern[((i+1)/(idx+1))&3];
				n += nn * pp;
				if(pp == 0) i += idx;
				i++;
			}

			data[idx++] = (n<0?-n:n)%10 + '0';
		}
		
		i = length - 1;
		n = '0';
		
		while(i >= idx) {
			int nn = data[i]-'0' + n-'0';
			n = data[i] = (nn<0?-nn:nn)%10 +'0';
			i--;
		}
		
		phase++;
		
		if(phase == 100)
			break;
	}
}

void run1(void)
{
	fft(input, strlen(input), 0);
	input[8] = 0;
	printf("%s\n", input);
}

void run2(void)
{
	int offset = 5976257;
	int length = strlen(input);
	char *buffer = malloc(length * 10000);
	
	int i;
	for(i = 0; i < 10000; i++)
		memcpy(&buffer[i*length], input, length);
	
	fft(buffer, length * 10000, offset);
	
	buffer[offset+8] = 0;
	printf("%s\n", &buffer[offset]);
}

int main(void)
{
	run2();
	
	return 0;
}