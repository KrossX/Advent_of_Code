/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <stdio.h>

#define INPUT_SIZE 1024
#include "day02_data.c"

void run(void)
{
	int *pc = input;
	
	while(1) {
		int op = *pc++;
		int n1 = *pc++;
		int n2 = *pc++;
		int n3 = *pc++;
		
		if(op == 99) {
			printf("Program Stopped. Value at 0: %d\n", input[0]);
			break;
		} else if(n1 >= INPUT_SIZE || n2 >= INPUT_SIZE || n3 >= INPUT_SIZE) {
			printf("Error! Overflow. %d %d %d\n", n1, n2, n3);
			break;
		}
		
		//printf("OP: %d, %d %d %d\n", op, n1, n2, n3);

		switch(op) {
		case 1: input[n3] = input[n1] + input[n2]; break;
		case 2: input[n3] = input[n1] * input[n2]; break;
		default: printf("Unknown Opcode: %d\n", op);
		}
	}
}

int main(void)
{
	int x, y;
	
	for(y = 0; y < 100; y++)
	for(x = 0; x < 100; x++) {
		memcpy(input, input_base, INPUT_SIZE);
		
		input[1] = x;
		input[2] = y;

		run();
		
		if(input[0] == 19690720) {
			printf("Noun: %d, Verb: %d, Value: %d\n", x, y, 100 * x + y);
			return 0;
		}
	}

	return 0;
}