/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <stdio.h>

#define INPUT_SIZE 1024
#include "day05_data.c"

int data_in(void)
{
	int x;
	printf("IN: ");
	scanf("%d", &x);
	return x;
}

int data_out(int x)
{
	printf("OUT: %d\n", x);
}

void run(void)
{
	int pc = 0;
	
	while(1) {
		int op = input[pc+0];
		int n1 = input[pc+1];
		int n2 = input[pc+2];
		int n3 = input[pc+3];
		int m1 = op /   100;
		int m2 = op /  1000;
		int m3 = op / 10000;
		
		op %= 100;
		m1 -= (m1/10) * 10;
		m2 -= (m2/10) * 10;
		m3 -= (m3/10) * 10;
		
		//printf("%3d [%4d, %4d, %4d, %4d, %4d, %4d] ", pc, input[pc+0],input[pc+1],input[pc+2],input[pc+3],input[pc+4],input[pc+5]);
		//printf("OP: %d, %d, %d, %d, %d, %d, %d\n", op, n1, n2, n3, m1, m2, m3);
		
		if(op == 99) {
			printf("Program Stopped. Value at 0: %d\n", input[0]);
			break;
		} else if((op == 1 || op == 2) && (
		          (m1 == 0 && (n1 < 0 || n1 >= INPUT_SIZE)) || 
		          (m2 == 0 && (n2 < 0 || n2 >= INPUT_SIZE)) || 
				  (m3 == 0 && (n3 < 0 || n3 >= INPUT_SIZE)))) {
			printf("Error! Overflow. %d %d %d\n", n1, n2, n3);
		} else if((op == 3 || op == 4) && (
		          (m1 == 0 && (n1 < 0 || n1 >= INPUT_SIZE)))) {
			printf("Error! Overflow. %d\n", n1);
		}

		switch(op) {
		case 1: input[n3] = (m1?n1:input[n1]) + (m2?n2:input[n2]); pc += 4; break;
		case 2: input[n3] = (m1?n1:input[n1]) * (m2?n2:input[n2]); pc += 4; break;
		case 3: input[n1] = data_in(); pc += 2; break;
		case 4: data_out(m1?n1:input[n1]); pc += 2; break;
		case 5: if(m1?n1:input[n1]) pc = m2?n2:input[n2]; else pc += 3; break;
		case 6: if((m1?n1:input[n1]) == 0) pc = m2?n2:input[n2]; else pc += 3; break;
		case 7: input[n3] = (m1?n1:input[n1]) < (m2?n2:input[n2]) ? 1 : 0; pc += 4; break;
		case 8: input[n3] = (m1?n1:input[n1]) == (m2?n2:input[n2]) ? 1 : 0; pc += 4; break;
		default: printf("Unknown Opcode: %d\n", op); return;
		}
	}
}

int main(void)
{
	run();

	return 0;
}